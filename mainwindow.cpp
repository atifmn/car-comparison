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
    int leftBoxIndex = ui->leftCarComboBox->currentIndex();
    int rightBoxIndex = ui->rightCarComboBox->currentIndex();

    // If any of the selectors are still on index 0, no actual car is selected for both and so the input is invalid for comapring Cars
    if (leftBoxIndex == 0 || rightBoxIndex == 0)
    {
        QMessageBox invalidMsg(this);

        invalidMsg.setWindowTitle("Invalid");
        invalidMsg.setText("Please input valid Cars to compare.");

        invalidMsg.exec();

        return;
    }

    Car car1 = m_cars[leftBoxIndex - 1];
    Car car2 =  m_cars[rightBoxIndex - 1];

    if (car1 == car2)
    {
        QMessageBox equalMsg(this);

        equalMsg.setWindowTitle("Same Car");
        equalMsg.setText("Please input two different Cars to compare.");

        equalMsg.exec();

        return;
    }

    QString car1Name = carDisplayName(car1);
    QString car2Name = carDisplayName(car2);

    // Math to be done: ((1000 / 0-60) * 3.0) + (((horsepower * 1000) / weight) * 2.0) + (((torque * 1000) / weight) * 1.5) + (horsepower * 0.10)
    double car1Val = ((1000.0 / car1.zeroToSixty()) * 3.0) + (((car1.horsepower() * 1000.0) / car1.weight()) * 2.0)
                     + (((car1.torque() * 1000.0) / car1.weight()) * 1.5) + (car1.horsepower() * 0.10);

    double car2Val = ((1000.0 / car2.zeroToSixty()) * 3.0) + (((car2.horsepower() * 1000.0) / car2.weight()) * 2.0)
                     + (((car2.torque() * 1000.0) / car2.weight()) * 1.5) + (car2.horsepower() * 0.10);

    if (car1Val > car2Val){
        ui->resultsLabel->setText(car1Name + " is the winner. Score: " + QString::number(car1Val));
    }
    else {
        ui->resultsLabel->setText(car2Name + " is the winner. Score: " + QString::number(car2Val));
    }
}

void MainWindow::loadCars()
{
    m_cars = {
              Car("BMW", "M340i xDrive Sedan", 2023, 64300.0, 29.0, 382, 369, 3951, 4.0),
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
