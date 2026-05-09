#include "carapiclient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QtGlobal>

namespace {
}

CarApiClient::CarApiClient(QObject *parent)
    : QObject(parent)
{
}

bool CarApiClient::hasCredentials() const
{
    return !apiToken().isEmpty() && !apiSecret().isEmpty();
}

bool CarApiClient::hasJwt() const
{
    return !m_jwtToken.trimmed().isEmpty();
}

void CarApiClient::searchCars(int year, const QString &make, const QString &model)
{
    m_pendingYear = year;
    m_pendingMake = make.trimmed();
    m_pendingModel = model.trimmed();

    // NOTE FOR LATER:
    // CarAPI auth is working, but the free-plan search endpoints have been inconsistent in practice:
    // - /api/trims returned 403
    // - /api/models with json filters returned DeprecatedException
    // - the suggested replacement path from the response did not resolve cleanly
    //
    // Best options when resuming:
    // 1. Verify the exact live-search endpoints allowed by the current CarAPI subscription, OR
    // 2. Switch to a different vehicle API, OR
    // 3. Replace API search temporarily with a local JSON dataset so the app can be finished cleanly
    //
    // For now, leave this search path simple and revisit provider choice before spending more time here.
    // The free CarAPI dataset is easier to access through models-level endpoints,
    // so use the public/free search flow here instead of paid trim/spec requests.
    executePendingSearch(false);
}

QString CarApiClient::apiToken() const
{
    return qEnvironmentVariable("CARAPI_TOKEN");
}

QString CarApiClient::apiSecret() const
{
    return qEnvironmentVariable("CARAPI_SECRET");
}

void CarApiClient::authenticate()
{
    QNetworkRequest request(QUrl("https://carapi.app/api/auth/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("accept", "text/plain");

    const QJsonObject payload = {
        {"api_token", apiToken()},
        {"api_secret", apiSecret()}
    };

    QNetworkReply *reply = m_networkManager.post(request, QJsonDocument(payload).toJson(QJsonDocument::Compact));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QByteArray responseBody = reply->readAll();
        const QString responseText = QString::fromUtf8(responseBody).trimmed();

        if (reply->error() != QNetworkReply::NoError) {
            QString errorMessage = QString("CarAPI authentication failed: %1")
                                       .arg(reply->errorString());

            if (!responseText.isEmpty()) {
                errorMessage += QString(" | Response: %1").arg(responseText);
            }

            reply->deleteLater();
            emit errorOccurred(errorMessage);
            return;
        }

        const QString jwt = responseText;

        if (jwt.isEmpty()) {
            reply->deleteLater();
            emit errorOccurred(QString("CarAPI authentication returned an empty JWT. HTTP %1.").arg(statusCode));
            return;
        }

        m_jwtToken = jwt;

        reply->deleteLater();
        executePendingSearch();
    });
}

void CarApiClient::executePendingSearch(bool useAuthorizationHeader)
{
    if (m_pendingYear == 0 || m_pendingMake.isEmpty() || m_pendingModel.isEmpty()) {
        emit errorOccurred("Search request is missing year, make, or model.");
        return;
    }

    QUrl url("https://carapi.app/vapi/models/v2");

    QUrlQuery query;
    query.addQueryItem("year", QString::number(m_pendingYear));
    query.addQueryItem("make", m_pendingMake);
    query.addQueryItem("limit", "250");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("accept", "application/json");

    if (useAuthorizationHeader && hasJwt()) {
        request.setRawHeader("Authorization", QString("Bearer %1").arg(m_jwtToken).toUtf8());
    }

    QNetworkReply *reply = m_networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, useAuthorizationHeader]() {
        const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QByteArray responseBody = reply->readAll();
        const QString responseText = QString::fromUtf8(responseBody).trimmed();

        if (reply->error() != QNetworkReply::NoError) {
            if (statusCode == 403 && useAuthorizationHeader) {
                reply->deleteLater();
                emit errorOccurred("JWT search was rejected with HTTP 403. Retrying with free dataset access...");
                executePendingSearch(false);
                return;
            }

            QString errorMessage = QString("CarAPI search failed: %1")
                                       .arg(reply->errorString());

            if (!responseText.isEmpty()) {
                errorMessage += QString(" | Response: %1").arg(responseText);
            }

            reply->deleteLater();
            emit errorOccurred(errorMessage);
            return;
        }

        const QJsonDocument doc = QJsonDocument::fromJson(responseBody);
        QJsonArray dataArray;

        if (doc.isObject()) {
            dataArray = doc.object().value("data").toArray();
        } else if (doc.isArray()) {
            dataArray = doc.array();
        }

        QVector<Car> cars;
        cars.reserve(dataArray.size());
        const QString requestedModel = m_pendingModel.toLower();

        for (const QJsonValue &value : dataArray) {
            const QJsonObject modelObj = value.toObject();
            const QString make = modelObj.value("make").toString();
            const QString modelName = !modelObj.value("name").toString().isEmpty()
                                      ? modelObj.value("name").toString()
                                      : modelObj.value("model").toString();
            const int year = modelObj.value("year").toInt();

            if (!modelName.toLower().contains(requestedModel)) {
                continue;
            }

            // Models-level search does not provide full performance specs on the free dataset,
            // so load the car shell now and fill performance data later when we support a deeper lookup.
            cars.append(Car(make, modelName, year, 0.0, 0.0, 0, 0, 0, 0.0));
        }

        reply->deleteLater();

        if (cars.isEmpty()) {
            emit errorOccurred(QString("No CarAPI results were found. HTTP %1.").arg(statusCode));
            return;
        }

        emit carsLoaded(cars);
    });
}
