#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "car.h"

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

private:
    void loadCars();
    void populateCarSelectors();
    QString carDisplayName(const Car &car) const;
    Car findCar(QString carName);

    Ui::MainWindow *ui;
    QVector<Car> m_cars;
};
#endif // MAINWINDOW_H
