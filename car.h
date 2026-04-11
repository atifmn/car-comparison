#ifndef CAR_H
#define CAR_H

#include <QString>

class Car
{
public:
    Car();
    Car(const QString &make,
        const QString &model,
        int year,
        double price,
        double mpg,
        int horsepower,
        int torque,
        double zeroToSixty);

    QString make() const;
    QString model() const;
    int year() const;
    double price() const;
    double mpg() const;
    int horsepower() const;
    int torque() const;
    double zeroToSixty() const;

    void setMake(const QString &make);
    void setModel(const QString &model);
    void setYear(int year);
    void setPrice(double price);
    void setMpg(double mpg);
    void setHorsepower(int horsepower);
    void setTorque(int torque);
    void setZeroToSixty(double zeroToSixty);

private:
    QString m_make;
    QString m_model;
    int m_year;
    double m_price;
    double m_mpg;
    int m_horsepower;
    int m_torque;
    double m_zeroToSixty;
};

#endif // CAR_H
