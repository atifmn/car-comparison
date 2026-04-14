#include "carapiclient.h"

#include <QtGlobal>

CarApiClient::CarApiClient(QObject *parent)
    : QObject(parent)
{
}

bool CarApiClient::hasCredentials() const
{
    return !apiToken().isEmpty() && !apiSecret().isEmpty();
}

void CarApiClient::searchCars(int year, const QString &make, const QString &model)
{
    Q_UNUSED(year);
    Q_UNUSED(make);
    Q_UNUSED(model);

    emit errorOccurred("CarAPI search is not implemented yet.");
}

QString CarApiClient::apiToken() const
{
    return qEnvironmentVariable("CARAPI_TOKEN");
}

QString CarApiClient::apiSecret() const
{
    return qEnvironmentVariable("CARAPI_SECRET");
}
