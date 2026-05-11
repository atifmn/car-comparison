#include "mainwindow.h"
#include "localcardata.h"
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
    populateMakeSearch();
    clearCarSelectors();

    connect(ui->compareButton, &QPushButton::clicked,
            this, &MainWindow::onCompareClicked);
    connect(ui->searchButton, &QPushButton::clicked,
            this, &MainWindow::onSearchClicked);
    connect(ui->yearSearchSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &MainWindow::onYearChanged);
    connect(ui->makeSearchComboBox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &MainWindow::onMakeChanged);
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

        QSpinBox {
            background-color: #232832;
            border: 1px solid #3f4654;
            border-radius: 8px;
            color: #f4f4f5;
            min-height: 34px;
            padding: 6px 12px;
            selection-background-color: #ff3b30;
        }

        QSpinBox:hover {
            border-color: #ff5a4f;
        }

        QSpinBox:focus {
            border-color: #ff3b30;
        }

        QComboBox:hover {
            border-color: #ff5a4f;
        }

        QComboBox:disabled {
            background-color: #171b22;
            border-color: #2b3039;
            color: #6b7280;
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

    const int leftCarIndex = ui->leftCarComboBox->currentData().toInt();
    const int rightCarIndex = ui->rightCarComboBox->currentData().toInt();

    if (leftBoxIndex == -1 || rightBoxIndex == -1 || leftCarIndex < 0 || rightCarIndex < 0)
    {
        QMessageBox invalidMsg(this);

        invalidMsg.setWindowTitle("Invalid");
        invalidMsg.setText("Please input valid Cars to compare.");

        invalidMsg.exec();

        return;
    }

    Car car1 = m_cars[leftCarIndex];
    Car car2 =  m_cars[rightCarIndex];

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
                                  + "\n0-60: " + QString::number(car1.zeroToSixty()) + " Seconds");
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
    const QString make = ui->makeSearchComboBox->currentText().trimmed();
    const QString model = ui->modelSearchComboBox->currentText().trimmed();
    const bool hasSpecificMake = ui->makeSearchComboBox->currentIndex() > 0;
    const bool hasSpecificModel = ui->modelSearchComboBox->isEnabled() && ui->modelSearchComboBox->currentIndex() > 0;

    // NOTE FOR LATER:
    // This local search flow currently acts as a year/make filter for both compare selectors together.
    // Future improvements:
    // 1. Let users load cars from different brands into Car A and Car B independently
    // 2. Expand the local catalog with many more cars/trims
    // 3. Improve selector consistency so search feels more like a polished compare workflow
    // 4. Revisit API integration later once the local experience is fully solid
    m_cars.clear();

    for (const Car &car : m_allCars) {
        if (car.year() != year) {
            continue;
        }

        if (hasSpecificMake && car.make() != make) {
            continue;
        }

        m_cars.append(car);
    }

    if (m_cars.isEmpty()) {
        clearCarSelectors();
        ui->searchStatusLabel->setText("No local cars matched that search.");
        return;
    }

    populateCarSelectors();

    if (hasSpecificModel) {
        const QString selectedDisplayName = QString("%1 %2 %3").arg(year).arg(make, model);
        int leftIndex = ui->leftCarComboBox->findText(selectedDisplayName);
        if (leftIndex >= 0) {
            ui->leftCarComboBox->setCurrentIndex(leftIndex);
        }
    }

    if (hasSpecificMake) {
        ui->searchStatusLabel->setText(QString("Loaded %1 cars for %2 %3.")
                                           .arg(m_cars.size())
                                           .arg(year)
                                           .arg(make));
    } else {
        ui->searchStatusLabel->setText(QString("Loaded %1 cars for %2.")
                                           .arg(m_cars.size())
                                           .arg(year));
    }
}

void MainWindow::onYearChanged(int year)
{
    m_cars.clear();
    for (const Car &car : m_allCars) {
        if (car.year() == year) {
            m_cars.append(car);
        }
    }

    populateMakeSearch();
    populateCarSelectors();
    ui->searchStatusLabel->setText(QString("Loaded %1 cars for %2. Choose a make to narrow the list.")
                                       .arg(m_cars.size())
                                       .arg(year));
}

void MainWindow::onMakeChanged(int index)
{
    Q_UNUSED(index);
    populateModelSearch();

    const int year = ui->yearSearchSpinBox->value();
    const QString make = ui->makeSearchComboBox->currentText();
    const bool hasSpecificMake = ui->makeSearchComboBox->currentIndex() > 0;

    m_cars.clear();
    for (const Car &car : m_allCars) {
        if (car.year() != year) {
            continue;
        }

        if (hasSpecificMake && car.make() != make) {
            continue;
        }

        m_cars.append(car);
    }

    populateCarSelectors();

    if (hasSpecificMake) {
        ui->searchStatusLabel->setText(QString("Loaded %1 %2 cars for %3. Pick a model to preselect one.")
                                           .arg(m_cars.size())
                                           .arg(make)
                                           .arg(year));
    } else {
        ui->searchStatusLabel->setText(QString("Loaded %1 cars for %2.")
                                           .arg(m_cars.size())
                                           .arg(year));
    }
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
    m_allCars = buildLocalCarCatalog();
    m_cars.clear();
}

void MainWindow::populateMakeSearch()
{
    const int selectedYear = ui->yearSearchSpinBox->value();
    QString previousMake = ui->makeSearchComboBox->currentText();
    QStringList makes;

    for (const Car &car : m_allCars) {
        if (car.year() == selectedYear && !makes.contains(car.make())) {
            makes.append(car.make());
        }
    }

    makes.sort();

    ui->makeSearchComboBox->blockSignals(true);
    ui->makeSearchComboBox->clear();
    ui->makeSearchComboBox->addItem("All makes");
    for (const QString &make : makes) {
        ui->makeSearchComboBox->addItem(make);
    }

    int previousIndex = ui->makeSearchComboBox->findText(previousMake);
    ui->makeSearchComboBox->setCurrentIndex(previousIndex >= 0 ? previousIndex : 0);
    ui->makeSearchComboBox->blockSignals(false);

    populateModelSearch();
}

void MainWindow::populateModelSearch()
{
    const int selectedYear = ui->yearSearchSpinBox->value();
    const QString selectedMake = ui->makeSearchComboBox->currentText();
    QStringList models;

    ui->modelSearchComboBox->blockSignals(true);
    ui->modelSearchComboBox->clear();

    if (ui->makeSearchComboBox->currentIndex() <= 0) {
        ui->modelSearchComboBox->addItem("Select make first");
        ui->modelSearchComboBox->setCurrentIndex(0);
        ui->modelSearchComboBox->setEnabled(false);
        ui->modelSearchComboBox->blockSignals(false);
        return;
    }

    for (const Car &car : m_allCars) {
        if (car.year() == selectedYear && car.make() == selectedMake && !models.contains(car.model())) {
            models.append(car.model());
        }
    }

    models.sort();

    ui->modelSearchComboBox->addItem("All models");
    for (const QString &model : models) {
        ui->modelSearchComboBox->addItem(model);
    }

    ui->modelSearchComboBox->setCurrentIndex(0);
    ui->modelSearchComboBox->setEnabled(true);
    ui->modelSearchComboBox->blockSignals(false);
}

void MainWindow::populateCarSelectors()
{
    clearCarSelectors();

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

void MainWindow::clearCarSelectors()
{
    ui->leftCarComboBox->clear();
    ui->rightCarComboBox->clear();
    ui->leftCarComboBox->addItem("Select car", -1);
    ui->rightCarComboBox->addItem("Select car", -1);
}
