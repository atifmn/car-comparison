#include "car.h"

Car::Car()
    : m_year(0)
    , m_price(0.0)
    , m_mpg(0.0)
    , m_horsepower(0)
    , m_torque(0)
    , m_zeroToSixty(0.0)
{
}

Car::Car(const QString &make,
         const QString &model,
         int year,
         double price,
         double mpg,
         int horsepower,
         int torque,
         double zeroToSixty)
    : m_make(make)
    , m_model(model)
    , m_year(year)
    , m_price(price)
    , m_mpg(mpg)
    , m_horsepower(horsepower)
    , m_torque(torque)
    , m_zeroToSixty(zeroToSixty)
{
}

QString Car::make() const
{
    return m_make;
}

QString Car::model() const
{
    return m_model;
}

int Car::year() const
{
    return m_year;
}

double Car::price() const
{
    return m_price;
}

double Car::mpg() const
{
    return m_mpg;
}

int Car::horsepower() const
{
    return m_horsepower;
}

int Car::torque() const
{
    return m_torque;
}

double Car::zeroToSixty() const
{
    return m_zeroToSixty;
}

void Car::setMake(const QString &make)
{
    m_make = make;
}

void Car::setModel(const QString &model)
{
    m_model = model;
}

void Car::setYear(int year)
{
    m_year = year;
}

void Car::setPrice(double price)
{
    m_price = price;
}

void Car::setMpg(double mpg)
{
    m_mpg = mpg;
}

void Car::setHorsepower(int horsepower)
{
    m_horsepower = horsepower;
}

void Car::setTorque(int torque)
{
    m_torque = torque;
}

void Car::setZeroToSixty(double zeroToSixty)
{
    m_zeroToSixty = zeroToSixty;
}
