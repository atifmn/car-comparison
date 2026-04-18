#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "car.h"
#include "carapiclient.h"

#include <QMainWindow>
#include <QVector>

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
    void onCarsLoaded(const QVector<Car> &cars);
    void onApiError(const QString &message);

private:
    void applyTheme();
    void loadCars();
    void populateCarSelectors();
    QString carDisplayName(const Car &car) const;
    double performanceScore(const Car &car) const;

    Ui::MainWindow *ui;
    CarApiClient m_carApiClient;
    QVector<Car> m_cars;
};
#endif // MAINWINDOW_H
