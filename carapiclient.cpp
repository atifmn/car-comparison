#include "carapiclient.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include <QtGlobal>

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
    Q_UNUSED(year);
    Q_UNUSED(make);
    Q_UNUSED(model);

    if (!hasCredentials()) {
        emit errorOccurred("Missing CarAPI credentials. Add CARAPI_TOKEN and CARAPI_SECRET before searching.");
        return;
    }

    if (!hasJwt()) {
        authenticate();
        return;
    }

    emit errorOccurred("Authenticated with CarAPI. The actual vehicle search request is the next step.");
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
        emit errorOccurred("CarAPI authentication succeeded. JWT cached in memory; vehicle search request is the next step.");
    });
}
