#ifndef CARAPICLIENT_H
#define CARAPICLIENT_H

#include "car.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QVector>

class CarApiClient : public QObject
{
    Q_OBJECT

public:
    explicit CarApiClient(QObject *parent = nullptr);

    bool hasCredentials() const;
    bool hasJwt() const;
    void searchCars(int year, const QString &make, const QString &model);

signals:
    void carsLoaded(const QVector<Car> &cars);
    void errorOccurred(const QString &message);

private:
    QString apiToken() const;
    QString apiSecret() const;
    void authenticate();

    QNetworkAccessManager m_networkManager;
    QString m_jwtToken;
};

#endif // CARAPICLIENT_H
