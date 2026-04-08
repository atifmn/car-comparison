#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
