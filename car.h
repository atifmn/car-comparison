#ifndef CAR_H
#define CAR_H

#include <QString>

class CarType;

class Car
{
public:
    Car();

private:
    QString m_name;
    CarType *m_type;
};

#endif // CAR_H
