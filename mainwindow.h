#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "car.h"
#include "carapiclient.h"

#include <QStringList>
#include <QMainWindow>
#include <QVector>

class QComboBox;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onCompareClicked();
    void onSearchClicked();
    void onYearChanged(int year);
    void onMakeChanged(int index);
    void onCarsLoaded(const QVector<Car> &cars);
    void onApiError(const QString &message);

private:
    void applyTheme();
    void loadCars();
    void populateMakeSearch();
    void populateModelSearch();
    void populateSelectorFilters();
    void populateModelFilter(QComboBox *makeComboBox, QComboBox *modelComboBox, const QString &disabledText);
    void populateCarSelector(QComboBox *makeComboBox, QComboBox *modelComboBox, QComboBox *carComboBox);
    void populateCarSelectors();
    QString carDisplayName(const Car &car) const;
    double performanceScore(const Car &car) const;
    void clearCarSelectors();

    Ui::MainWindow *ui;
    CarApiClient m_carApiClient;
    QVector<Car> m_allCars;
    QVector<Car> m_cars;
};
#endif // MAINWINDOW_H
