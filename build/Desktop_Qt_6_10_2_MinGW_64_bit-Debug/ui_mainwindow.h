/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QHBoxLayout *selectorsLayout;
    QGroupBox *leftCarGroupBox;
    QFormLayout *leftFormLayout;
    QLabel *leftTypeLabel;
    QComboBox *leftTypeComboBox;
    QLabel *leftCarLabel;
    QComboBox *leftCarComboBox;
    QGroupBox *rightCarGroupBox;
    QFormLayout *rightFormLayout;
    QLabel *rightTypeLabel;
    QComboBox *rightTypeComboBox;
    QLabel *rightCarLabel;
    QComboBox *rightCarComboBox;
    QPushButton *compareButton;
    QGroupBox *resultsGroupBox;
    QVBoxLayout *resultsLayout;
    QLabel *resultsPlaceholderLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 640);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(centralwidget);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(subtitleLabel);

        selectorsLayout = new QHBoxLayout();
        selectorsLayout->setSpacing(16);
        selectorsLayout->setObjectName("selectorsLayout");
        leftCarGroupBox = new QGroupBox(centralwidget);
        leftCarGroupBox->setObjectName("leftCarGroupBox");
        leftFormLayout = new QFormLayout(leftCarGroupBox);
        leftFormLayout->setObjectName("leftFormLayout");
        leftTypeLabel = new QLabel(leftCarGroupBox);
        leftTypeLabel->setObjectName("leftTypeLabel");

        leftFormLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, leftTypeLabel);

        leftTypeComboBox = new QComboBox(leftCarGroupBox);
        leftTypeComboBox->setObjectName("leftTypeComboBox");

        leftFormLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, leftTypeComboBox);

        leftCarLabel = new QLabel(leftCarGroupBox);
        leftCarLabel->setObjectName("leftCarLabel");

        leftFormLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, leftCarLabel);

        leftCarComboBox = new QComboBox(leftCarGroupBox);
        leftCarComboBox->setObjectName("leftCarComboBox");

        leftFormLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, leftCarComboBox);


        selectorsLayout->addWidget(leftCarGroupBox);

        rightCarGroupBox = new QGroupBox(centralwidget);
        rightCarGroupBox->setObjectName("rightCarGroupBox");
        rightFormLayout = new QFormLayout(rightCarGroupBox);
        rightFormLayout->setObjectName("rightFormLayout");
        rightTypeLabel = new QLabel(rightCarGroupBox);
        rightTypeLabel->setObjectName("rightTypeLabel");

        rightFormLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, rightTypeLabel);

        rightTypeComboBox = new QComboBox(rightCarGroupBox);
        rightTypeComboBox->setObjectName("rightTypeComboBox");

        rightFormLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, rightTypeComboBox);

        rightCarLabel = new QLabel(rightCarGroupBox);
        rightCarLabel->setObjectName("rightCarLabel");

        rightFormLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, rightCarLabel);

        rightCarComboBox = new QComboBox(rightCarGroupBox);
        rightCarComboBox->setObjectName("rightCarComboBox");

        rightFormLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, rightCarComboBox);


        selectorsLayout->addWidget(rightCarGroupBox);


        verticalLayout->addLayout(selectorsLayout);

        compareButton = new QPushButton(centralwidget);
        compareButton->setObjectName("compareButton");
        compareButton->setMinimumSize(QSize(160, 40));

        verticalLayout->addWidget(compareButton);

        resultsGroupBox = new QGroupBox(centralwidget);
        resultsGroupBox->setObjectName("resultsGroupBox");
        resultsLayout = new QVBoxLayout(resultsGroupBox);
        resultsLayout->setObjectName("resultsLayout");
        resultsPlaceholderLabel = new QLabel(resultsGroupBox);
        resultsPlaceholderLabel->setObjectName("resultsPlaceholderLabel");
        resultsPlaceholderLabel->setAlignment(Qt::AlignCenter);

        resultsLayout->addWidget(resultsPlaceholderLabel);


        verticalLayout->addWidget(resultsGroupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Car Comparison Tool", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Compare Two Cars", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("MainWindow", "Select a type and a car on each side to prepare for comparison.", nullptr));
        leftCarGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Car A", nullptr));
        leftTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        leftCarLabel->setText(QCoreApplication::translate("MainWindow", "Car", nullptr));
        rightCarGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Car B", nullptr));
        rightTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        rightCarLabel->setText(QCoreApplication::translate("MainWindow", "Car", nullptr));
        compareButton->setText(QCoreApplication::translate("MainWindow", "Compare", nullptr));
        resultsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Comparison Area", nullptr));
        resultsPlaceholderLabel->setText(QCoreApplication::translate("MainWindow", "Comparison results will appear here once the logic is added.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
