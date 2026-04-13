#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadCars();
    populateCarSelectors();

    connect(ui->compareButton, &QPushButton::clicked,
            this, &MainWindow::onCompareClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCompareClicked()
{
    QString car1Name = ui->leftCarComboBox->currentText();
    QString car2Name = ui->rightCarComboBox->currentText();

    Car car1 = findCar(car1Name);
    Car car2 = findCar(car2Name);

    if (car1.year() == 0 || car2.year() == 0) // If the cars have the year "0", this means correct inputs are not in both boxes and the compare is invalid
    {
        QMessageBox loseMsg(this);

        loseMsg.setWindowTitle("Invalid");
        loseMsg.setText("Please input valid Cars to compare.");

        loseMsg.exec();

        return;
    }

    // Math to be done: horsepower + torque + (1000 / 0-60) + (100,000 / weight)
    double car1Val;
}

void MainWindow::loadCars()
{
    m_cars = {
              Car("BMW", "M340i xDrive Sedan", 2025, 64300.0, 29.0, 386, 398, 3951, 4.1),
              Car("BMW", "1 Series M Coupe", 2011, 47010.0, 21.0, 335, 370, 3296, 4.7),
              Car("Subaru", "Impreza 2.0i Sedan", 2014, 18895.0, 30.0, 148, 145, 2910, 9.4),
              Car("Hyundai", "Sonata SE", 2025, 26900.0, 32.0, 191, 181, 3316, 7.9),
              Car("BMW", "X7 M60i", 2025, 115000.0, 18.0, 523, 553, 5688, 4.5)
    };
}

void MainWindow::populateCarSelectors()
{
    ui->leftCarComboBox->clear();
    ui->rightCarComboBox->clear();

    ui->leftCarComboBox->addItem("Select car", 0);
    ui->rightCarComboBox->addItem("Select car", 0);

    for (int i = 0; i < m_cars.size(); i++) {
        const QString displayName = carDisplayName(m_cars[i]);
        ui->leftCarComboBox->addItem(displayName, i + 1);
        ui->rightCarComboBox->addItem(displayName, i + 1);
    }
}

QString MainWindow::carDisplayName(const Car &car) const
{
    return QString("%1 %2 %3")
        .arg(car.year())
        .arg(car.make(), car.model());
}

Car MainWindow::findCar(QString carName)
{
    for (int i = 0; i < m_cars.size(); i++){
        const QString currCarName = carDisplayName(m_cars[i]);

        if (carName == currCarName){
            return m_cars[i];
        }
    }

    return Car();
}
