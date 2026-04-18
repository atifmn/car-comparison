#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    applyTheme();
    loadCars();
    populateCarSelectors();

    connect(ui->compareButton, &QPushButton::clicked,
            this, &MainWindow::onCompareClicked);
    connect(ui->searchButton, &QPushButton::clicked,
            this, &MainWindow::onSearchClicked);
    connect(&m_carApiClient, &CarApiClient::carsLoaded,
            this, &MainWindow::onCarsLoaded);
    connect(&m_carApiClient, &CarApiClient::errorOccurred,
            this, &MainWindow::onApiError);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::applyTheme()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #101114;
        }

        QWidget#centralwidget {
            background-color: #101114;
            color: #f4f4f5;
            font-family: "Segoe UI";
            font-size: 14px;
        }

        QLabel {
            color: #f4f4f5;
        }

        QLabel#titleLabel {
            color: #ffffff;
            font-size: 30px;
            font-weight: 800;
            letter-spacing: 1px;
            padding-top: 8px;
        }

        QLabel#subtitleLabel {
            color: #a1a1aa;
            font-size: 14px;
            padding-bottom: 8px;
        }

        QGroupBox {
            background-color: #1a1d22;
            border: 1px solid #343a46;
            border-radius: 14px;
            color: #f4f4f5;
            font-size: 15px;
            font-weight: 700;
            margin-top: 18px;
            padding: 18px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top left;
            left: 18px;
            padding: 0 8px;
            color: #ff5a4f;
            background-color: #101114;
        }

        QComboBox {
            background-color: #232832;
            border: 1px solid #3f4654;
            border-radius: 8px;
            color: #f4f4f5;
            min-height: 34px;
            padding: 6px 12px;
        }

        QLineEdit, QSpinBox {
            background-color: #232832;
            border: 1px solid #3f4654;
            border-radius: 8px;
            color: #f4f4f5;
            min-height: 34px;
            padding: 6px 12px;
            selection-background-color: #ff3b30;
        }

        QLineEdit:hover, QSpinBox:hover {
            border-color: #ff5a4f;
        }

        QLineEdit:focus, QSpinBox:focus {
            border-color: #ff3b30;
        }

        QComboBox:hover {
            border-color: #ff5a4f;
        }

        QComboBox::drop-down {
            border: none;
            width: 28px;
        }

        QComboBox QAbstractItemView {
            background-color: #232832;
            border: 1px solid #3f4654;
            color: #f4f4f5;
            selection-background-color: #ff3b30;
            selection-color: #ffffff;
        }

        QPushButton#compareButton {
            background-color: #ff3b30;
            border: none;
            border-radius: 10px;
            color: #ffffff;
            font-size: 15px;
            font-weight: 800;
            letter-spacing: 1px;
            min-height: 46px;
            padding: 10px 24px;
        }

        QPushButton#searchButton {
            background-color: #232832;
            border: 1px solid #ff3b30;
            border-radius: 10px;
            color: #ffffff;
            font-size: 14px;
            font-weight: 700;
            min-height: 38px;
            padding: 8px 18px;
        }

        QPushButton#searchButton:hover {
            background-color: #ff3b30;
        }

        QLabel#searchStatusLabel {
            color: #a1a1aa;
            font-size: 13px;
            padding-top: 4px;
        }

        QPushButton#compareButton:hover {
            background-color: #ff5a4f;
        }

        QPushButton#compareButton:pressed {
            background-color: #d92d25;
        }

        QLabel#resultsLabel {
            background-color: #232832;
            border: 1px solid #343a46;
            border-radius: 10px;
            color: #f4f4f5;
            font-size: 14px;
            min-height: 120px;
            padding: 18px;
        }

        QMenuBar, QStatusBar {
            background-color: #101114;
            color: #a1a1aa;
        }

        QMessageBox {
            background-color: #1a1d22;
            color: #f4f4f5;
        }

        QMessageBox QLabel {
            color: #f4f4f5;
        }

        QMessageBox QPushButton {
            background-color: #ff3b30;
            border: none;
            border-radius: 6px;
            color: #ffffff;
            min-width: 72px;
            padding: 6px 14px;
        }

        QMessageBox QPushButton:hover {
            background-color: #ff5a4f;
        }
    )");
}

void MainWindow::onCompareClicked()
{
    int leftBoxIndex = ui->leftCarComboBox->currentIndex();
    int rightBoxIndex = ui->rightCarComboBox->currentIndex();

    // // If any of the selectors are still on index 0, no actual car is selected for both and so the input is invalid for comapring Cars
    if (leftBoxIndex == -1 || rightBoxIndex == -1)
    {
        QMessageBox invalidMsg(this);

        invalidMsg.setWindowTitle("Invalid");
        invalidMsg.setText("Please input valid Cars to compare.");

        invalidMsg.exec();

        return;
    }

    Car car1 = m_cars[leftBoxIndex];
    Car car2 =  m_cars[rightBoxIndex];

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

    double car1Val = performanceScore(car1);
    double car2Val = performanceScore(car2);

    if (car1Val > car2Val){
        ui->resultsLabel->setText(car1Name + " is the winner.\nScore: " + QString::number(car1Val)
                                  + "\n\nHorsePower: " + QString::number(car1.horsepower()) + "\nTorque: " + QString::number(car1.torque())
                                  + + "\n0-60: " + QString::number(car1.zeroToSixty()) + " Seconds");
    }
    else if (car1Val < car2Val) {
        ui->resultsLabel->setText(car2Name + " is the winner.\nScore: " + QString::number(car2Val)
                                  + "\n\nHorsePower: " + QString::number(car2.horsepower()) + "\nTorque: " + QString::number(car2.torque())
                                  + "\n0-60: " + QString::number(car2.zeroToSixty()) + " Seconds");
    }
    else {
        ui->resultsLabel->setText("These cars are both tied. Value: " + QString::number(car1Val));
    }
}

void MainWindow::onSearchClicked()
{
    const int year = ui->yearSearchSpinBox->value();
    const QString make = ui->makeSearchLineEdit->text().trimmed();
    const QString model = ui->modelSearchLineEdit->text().trimmed();

    if (make.isEmpty() || model.isEmpty()) {
        ui->searchStatusLabel->setText("Enter both a make and model before searching.");
        return;
    }

    if (!m_carApiClient.hasCredentials()) {
        ui->searchStatusLabel->setText("Missing CarAPI credentials. Add CARAPI_TOKEN and CARAPI_SECRET to the run environment before searching.");
        return;
    }

    ui->searchStatusLabel->setText(QString("Searching for %1 %2 %3...")
                                       .arg(year)
                                       .arg(make, model));

    m_carApiClient.searchCars(year, make, model);
}

void MainWindow::onCarsLoaded(const QVector<Car> &cars)
{
    if (cars.isEmpty()) {
        ui->searchStatusLabel->setText("No cars were found for that search.");
        return;
    }

    m_cars = cars;
    populateCarSelectors();

    ui->searchStatusLabel->setText(QString("Loaded %1 cars from the API results.").arg(cars.size()));
}

void MainWindow::onApiError(const QString &message)
{
    ui->searchStatusLabel->setText(message);
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

    // ui->leftCarComboBox->addItem("Select car", 0);
    // ui->rightCarComboBox->addItem("Select car", 0);

    for (int i = 0; i < m_cars.size(); i++) {
        const QString displayName = carDisplayName(m_cars[i]);
        ui->leftCarComboBox->addItem(displayName, i);
        ui->rightCarComboBox->addItem(displayName, i);
    }
}

QString MainWindow::carDisplayName(const Car &car) const
{
    return QString("%1 %2 %3")
        .arg(car.year())
        .arg(car.make(), car.model());
}

double MainWindow::performanceScore(const Car &car) const
{
    // Math: ((1000 / 0-60) * 3.0) + (((horsepower * 1000) / weight) * 2.0) + (((torque * 1000) / weight) * 1.5) + (horsepower * 0.10)
    return ((1000.0 / car.zeroToSixty()) * 3.0)
           + (((car.horsepower() * 1000.0) / car.weight()) * 2.0)
           + (((car.torque() * 1000.0) / car.weight()) * 1.5)
           + (car.horsepower() * 0.10);
}
