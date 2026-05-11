#include "localcardata.h"

namespace {
struct CarTemplate
{
    const char *make;
    const char *model;
    double price;
    double mpg;
    int horsepower;
    int torque;
    int weight;
    double zeroToSixty;
};
}

QVector<Car> buildLocalCarCatalog()
{
    static const CarTemplate templates[] = {
        {"Toyota", "Corolla LE", 19800.0, 34.0, 132, 128, 2840, 8.5},
        {"Toyota", "Camry SE", 24200.0, 32.0, 203, 184, 3310, 7.6},
        {"Toyota", "RAV4 XLE", 26900.0, 30.0, 203, 184, 3490, 8.0},
        {"Toyota", "Supra 3.0", 49900.0, 26.0, 335, 365, 3397, 4.1},
        {"Honda", "Civic EX", 21500.0, 36.0, 174, 162, 2877, 7.7},
        {"Honda", "Accord Sport", 26700.0, 33.0, 192, 192, 3230, 7.1},
        {"Honda", "CR-V EX", 27800.0, 31.0, 190, 179, 3337, 7.9},
        {"BMW", "330i Sedan", 41400.0, 30.0, 255, 295, 3519, 5.6},
        {"BMW", "M340i xDrive Sedan", 54300.0, 27.0, 382, 369, 3873, 4.1},
        {"BMW", "X3 M40i", 56800.0, 23.0, 382, 365, 4360, 4.4},
        {"Hyundai", "Elantra Limited", 22400.0, 35.0, 147, 132, 2868, 8.4},
        {"Hyundai", "Sonata SEL", 25600.0, 31.0, 191, 181, 3235, 7.6},
        {"Hyundai", "Veloster N", 27900.0, 25.0, 275, 260, 3106, 5.1},
        {"Subaru", "Impreza Premium", 21900.0, 31.0, 152, 145, 3020, 8.9},
        {"Subaru", "WRX Premium", 29800.0, 23.0, 268, 258, 3389, 5.5},
        {"Subaru", "Outback Limited", 32700.0, 29.0, 182, 176, 3634, 8.0},
        {"Ford", "Mustang EcoBoost", 27900.0, 25.0, 310, 350, 3532, 5.2},
        {"Ford", "Explorer ST", 54700.0, 21.0, 400, 415, 4701, 5.2},
        {"Ford", "F-150 XLT 4x4", 36500.0, 22.0, 325, 400, 4690, 6.1}
    };

    QVector<Car> cars;
    cars.reserve(114);

    for (int year = 2015; year <= 2020; ++year) {
        const int offset = year - 2015;

        for (const CarTemplate &carTemplate : templates) {
            const double price = carTemplate.price + (offset * 750.0);
            const double mpg = carTemplate.mpg + ((offset % 3) * 0.5);
            const int horsepower = carTemplate.horsepower + (offset / 2);
            const int torque = carTemplate.torque + (offset / 2);
            const int weight = carTemplate.weight + ((offset % 2) * 12);
            double zeroToSixty = carTemplate.zeroToSixty - (offset * 0.05);

            if (zeroToSixty < 3.5) {
                zeroToSixty = 3.5;
            }

            cars.append(Car(carTemplate.make,
                            carTemplate.model,
                            year,
                            price,
                            mpg,
                            horsepower,
                            torque,
                            weight,
                            zeroToSixty));
        }
    }

    return cars;
}
