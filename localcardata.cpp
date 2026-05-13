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
        {"Toyota", "GR86 Premium", 28700.0, 24.0, 228, 184, 2811, 6.1},
        {"Toyota", "Highlander XLE", 38500.0, 24.0, 295, 263, 4185, 7.2},
        {"Honda", "Civic EX", 21500.0, 36.0, 174, 162, 2877, 7.7},
        {"Honda", "Accord Sport", 26700.0, 33.0, 192, 192, 3230, 7.1},
        {"Honda", "CR-V EX", 27800.0, 31.0, 190, 179, 3337, 7.9},
        {"Honda", "Civic Type R", 36900.0, 25.0, 306, 295, 3121, 5.0},
        {"Honda", "Pilot EX-L", 36500.0, 22.0, 280, 262, 4036, 6.9},
        {"Honda", "Passport TrailSport", 43200.0, 21.0, 280, 262, 4221, 6.8},
        {"BMW", "330i Sedan", 41400.0, 30.0, 255, 295, 3519, 5.6},
        {"BMW", "M340i xDrive Sedan", 54300.0, 27.0, 382, 369, 3873, 4.1},
        {"BMW", "X3 M40i", 56800.0, 23.0, 382, 365, 4360, 4.4},
        {"BMW", "540i Sedan", 59800.0, 28.0, 335, 332, 3840, 4.8},
        {"BMW", "M440i xDrive Coupe", 61200.0, 26.0, 382, 369, 3880, 4.3},
        {"BMW", "X5 xDrive40i", 65700.0, 24.0, 335, 330, 4863, 5.3},
        {"Hyundai", "Elantra Limited", 22400.0, 35.0, 147, 132, 2868, 8.4},
        {"Hyundai", "Sonata SEL", 25600.0, 31.0, 191, 181, 3235, 7.6},
        {"Hyundai", "Veloster N", 27900.0, 25.0, 275, 260, 3106, 5.1},
        {"Hyundai", "Kona N", 34900.0, 23.0, 276, 289, 3334, 5.3},
        {"Hyundai", "Tucson SEL", 27100.0, 29.0, 187, 178, 3413, 8.3},
        {"Hyundai", "Santa Fe Limited", 39700.0, 25.0, 277, 311, 3982, 6.3},
        {"Subaru", "Impreza Premium", 21900.0, 31.0, 152, 145, 3020, 8.9},
        {"Subaru", "WRX Premium", 29800.0, 23.0, 268, 258, 3389, 5.5},
        {"Subaru", "Outback Limited", 32700.0, 29.0, 182, 176, 3634, 8.0},
        {"Subaru", "BRZ Limited", 28900.0, 25.0, 228, 184, 2815, 6.0},
        {"Subaru", "Forester Sport", 30500.0, 29.0, 182, 176, 3449, 8.2},
        {"Subaru", "Ascent Touring", 46100.0, 23.0, 260, 277, 4603, 6.9},
        {"Ford", "Mustang EcoBoost", 27900.0, 25.0, 310, 350, 3532, 5.2},
        {"Ford", "Explorer ST", 54700.0, 21.0, 400, 415, 4701, 5.2},
        {"Ford", "F-150 XLT 4x4", 36500.0, 22.0, 325, 400, 4690, 6.1},
        {"Ford", "Edge ST", 43900.0, 24.0, 335, 380, 4346, 5.7},
        {"Ford", "Bronco Badlands", 42700.0, 20.0, 330, 415, 4768, 6.3},
        {"Ford", "Escape ST-Line", 31400.0, 28.0, 250, 280, 3561, 6.8},
        {"Chevrolet", "Malibu RS", 25400.0, 32.0, 160, 184, 3159, 7.8},
        {"Chevrolet", "Camaro LT1", 38200.0, 20.0, 455, 455, 3650, 4.1},
        {"Chevrolet", "Blazer RS", 43200.0, 23.0, 308, 270, 4253, 6.5},
        {"Chevrolet", "Silverado RST", 45700.0, 20.0, 355, 383, 4950, 6.0},
        {"Chevrolet", "Corvette Stingray", 59900.0, 22.0, 490, 465, 3535, 3.8},
        {"Nissan", "Sentra SR", 22100.0, 34.0, 149, 146, 3084, 8.7},
        {"Nissan", "Altima SR", 27300.0, 32.0, 188, 180, 3212, 7.6},
        {"Nissan", "Maxima SR", 43800.0, 24.0, 300, 261, 3672, 5.7},
        {"Nissan", "370Z Sport", 30700.0, 22.0, 332, 270, 3333, 5.0},
        {"Nissan", "Rogue SL", 32100.0, 31.0, 181, 181, 3538, 8.0},
        {"Mazda", "Mazda3 Premium", 28200.0, 31.0, 191, 186, 3143, 7.1},
        {"Mazda", "Mazda6 Touring", 27900.0, 29.0, 187, 186, 3443, 7.5},
        {"Mazda", "CX-5 Grand Touring", 32900.0, 27.0, 227, 310, 3728, 6.6},
        {"Mazda", "CX-9 Signature", 46100.0, 23.0, 250, 320, 4409, 7.1},
        {"Mazda", "MX-5 Miata Club", 30200.0, 29.0, 181, 151, 2341, 5.7},
        {"Audi", "A4 Premium", 39900.0, 29.0, 201, 236, 3582, 6.3},
        {"Audi", "S4 Premium Plus", 51200.0, 24.0, 349, 369, 3847, 4.4},
        {"Audi", "A5 Coupe", 45600.0, 28.0, 261, 273, 3748, 5.3},
        {"Audi", "Q5 Premium", 44500.0, 25.0, 261, 273, 4090, 5.7},
        {"Audi", "RS5 Coupe", 75400.0, 21.0, 444, 442, 3926, 3.8},
        {"Kia", "Forte GT", 24800.0, 31.0, 201, 195, 3015, 6.8},
        {"Kia", "K5 GT-Line", 28700.0, 31.0, 180, 195, 3228, 7.4},
        {"Kia", "Stinger GT", 40900.0, 21.0, 368, 376, 4034, 4.7},
        {"Kia", "Telluride SX", 45100.0, 22.0, 291, 262, 4482, 7.0},
        {"Kia", "Sportage X-Pro", 36500.0, 24.0, 187, 178, 3690, 8.1},
        {"Volkswagen", "Jetta GLI", 28700.0, 30.0, 228, 258, 3223, 6.1},
        {"Volkswagen", "GTI SE", 33200.0, 28.0, 241, 273, 3147, 5.9},
        {"Volkswagen", "Golf R", 44800.0, 26.0, 315, 295, 3471, 4.7},
        {"Volkswagen", "Atlas SEL", 43800.0, 22.0, 276, 266, 4550, 7.2},
        {"Volkswagen", "Tiguan SEL", 36000.0, 25.0, 184, 221, 3856, 8.1},
        {"Mercedes-Benz", "C300 Sedan", 42300.0, 28.0, 255, 273, 3649, 5.9},
        {"Mercedes-Benz", "AMG C43 Sedan", 58400.0, 24.0, 385, 384, 3905, 4.6},
        {"Mercedes-Benz", "E350 Sedan", 54950.0, 27.0, 255, 273, 3891, 6.0},
        {"Mercedes-Benz", "GLC 300", 45600.0, 25.0, 255, 273, 4079, 6.1},
        {"Mercedes-Benz", "GLE 450", 63700.0, 23.0, 362, 369, 5052, 5.5}
    };

    QVector<Car> cars;
    constexpr int yearCount = 6;
    const int templateCount = sizeof(templates) / sizeof(templates[0]);
    cars.reserve(templateCount * yearCount);

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
