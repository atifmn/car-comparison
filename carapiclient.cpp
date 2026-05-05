#include "carapiclient.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QtGlobal>

namespace {
double numberFromValue(const QJsonValue &value)
{
    if (value.isDouble()) {
        return value.toDouble();
    }

    if (value.isString()) {
        return value.toString().toDouble();
    }

    return 0.0;
}

int intFromValue(const QJsonValue &value)
{
    return static_cast<int>(numberFromValue(value));
}

QJsonObject objectFromValue(const QJsonValue &value)
{
    return value.isObject() ? value.toObject() : QJsonObject();
}
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
    if (!hasCredentials()) {
        emit errorOccurred("Missing CarAPI credentials. Add CARAPI_TOKEN and CARAPI_SECRET before searching.");
        return;
    }

    m_pendingYear = year;
    m_pendingMake = make.trimmed();
    m_pendingModel = model.trimmed();

    if (!hasJwt()) {
        authenticate();
        return;
    }

    executePendingSearch();
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

        if (reply->error() != QNetworkReply::NoError) {
            const QString errorMessage = QString("CarAPI authentication failed: %1")
                                             .arg(reply->errorString());
            reply->deleteLater();
            emit errorOccurred(errorMessage);
            return;
        }

        const QString jwt = QString::fromUtf8(responseBody).trimmed();

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

void CarApiClient::executePendingSearch()
{
    if (m_pendingYear == 0 || m_pendingMake.isEmpty() || m_pendingModel.isEmpty()) {
        emit errorOccurred("Search request is missing year, make, or model.");
        return;
    }

    QUrl url("https://carapi.app/api/trims");

    const QJsonArray filters = {
        QJsonObject{{"field", "year"}, {"op", "="}, {"val", m_pendingYear}},
        QJsonObject{{"field", "make"}, {"op", "="}, {"val", m_pendingMake}},
        QJsonObject{{"field", "model"}, {"op", "like"}, {"val", m_pendingModel}}
    };

    QUrlQuery query;
    query.addQueryItem("limit", "25");
    query.addQueryItem("json", QString::fromUtf8(QJsonDocument(filters).toJson(QJsonDocument::Compact)));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("accept", "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_jwtToken).toUtf8());

    QNetworkReply *reply = m_networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QByteArray responseBody = reply->readAll();

        if (reply->error() != QNetworkReply::NoError) {
            const QString errorMessage = QString("CarAPI search failed: %1")
                                             .arg(reply->errorString());
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

        for (const QJsonValue &value : dataArray) {
            const QJsonObject trim = value.toObject();
            const QJsonObject body = objectFromValue(trim.value("body"));
            const QJsonObject engine = objectFromValue(trim.value("engine"));
            const QJsonObject mileage = objectFromValue(trim.value("mileage"));

            const QString make = trim.value("make").toString();
            const QString baseModel = trim.value("model").toString();
            const QString trimName = trim.value("trim").toString();
            const QString description = trim.value("description").toString();
            const QString displayModel = !description.isEmpty() ? description
                                      : !trimName.isEmpty() ? trimName
                                      : baseModel;

            const int year = trim.value("year").toInt();
            const double price = numberFromValue(trim.value("msrp"));
            const double mpg = numberFromValue(mileage.value("combined_mpg"));
            const int horsepower = intFromValue(engine.value("horsepower_hp"));
            const int torque = intFromValue(engine.value("torque_ft_lbs"));
            const int weight = intFromValue(body.value("curb_weight"));

            cars.append(Car(make, displayModel, year, price, mpg, horsepower, torque, weight, 0.0));
        }

        reply->deleteLater();

        if (cars.isEmpty()) {
            emit errorOccurred(QString("No CarAPI results were found. HTTP %1.").arg(statusCode));
            return;
        }

        emit carsLoaded(cars);
    });
}
