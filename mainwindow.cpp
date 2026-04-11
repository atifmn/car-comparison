#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QPushButton>

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
}

void MainWindow::loadCars()
{
    m_cars = {
        Car("BMW", "M340i xDrive Sedan", 2025, 64300.0, 29.0, 386, 398, 4.1),
        Car("BMW", "1 Series M Coupe", 2011, 47010.0, 21.0, 335, 370, 4.7),
        Car("Subaru", "Impreza 2.0i Sedan", 2014, 18895.0, 30.0, 148, 145, 9.4),
        Car("Hyundai", "Sonata SE", 2025, 26900.0, 32.0, 191, 181, 7.9),
        Car("BMW", "X7 M60i", 2025, 115000.0, 18.0, 523, 553, 4.5)
    };
}

void MainWindow::populateCarSelectors()
{
    ui->leftCarComboBox->clear();
    ui->rightCarComboBox->clear();

    ui->leftCarComboBox->addItem("Select car", 0);
    ui->rightCarComboBox->addItem("Select car", 0);

    for (int i = 0; i < m_cars.size(); ++i) {
        const QString displayName = carDisplayName(m_cars[i]);
        ui->leftCarComboBox->addItem(displayName, i + 1);
        ui->rightCarComboBox->addItem(displayName, i + 1);
    }
}

QString MainWindow::carDisplayName(const Car &car) const
{
    return QString("%1 %2 %3")
        .arg(car.year())
        .arg(car.make())
        .arg(car.model());
}
