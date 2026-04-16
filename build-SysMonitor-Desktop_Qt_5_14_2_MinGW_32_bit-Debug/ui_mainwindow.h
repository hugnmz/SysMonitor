/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelCPU;
    QProgressBar *progressBarCPU;
    QLabel *labelRAM;
    QProgressBar *progressBarRAM;
    QLabel *labelIP;
    QSpacerItem *verticalSpacer;
    QLabel *lblIPPublic;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        labelCPU = new QLabel(centralwidget);
        labelCPU->setObjectName(QString::fromUtf8("labelCPU"));

        verticalLayout->addWidget(labelCPU);

        progressBarCPU = new QProgressBar(centralwidget);
        progressBarCPU->setObjectName(QString::fromUtf8("progressBarCPU"));
        progressBarCPU->setValue(0);

        verticalLayout->addWidget(progressBarCPU);

        labelRAM = new QLabel(centralwidget);
        labelRAM->setObjectName(QString::fromUtf8("labelRAM"));

        verticalLayout->addWidget(labelRAM);

        progressBarRAM = new QProgressBar(centralwidget);
        progressBarRAM->setObjectName(QString::fromUtf8("progressBarRAM"));
        progressBarRAM->setValue(0);

        verticalLayout->addWidget(progressBarRAM);

        labelIP = new QLabel(centralwidget);
        labelIP->setObjectName(QString::fromUtf8("labelIP"));
        labelIP->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(labelIP);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lblIPPublic = new QLabel(centralwidget);
        lblIPPublic->setObjectName(QString::fromUtf8("lblIPPublic"));
        lblIPPublic->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(lblIPPublic);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Net System Monitor - Local", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "H\341\273\206 TH\341\273\220NG C\341\273\246A T\303\224I", nullptr));
        labelCPU->setText(QCoreApplication::translate("MainWindow", "S\341\273\255 d\341\273\245ng CPU:", nullptr));
        progressBarCPU->setFormat(QCoreApplication::translate("MainWindow", "%p%", nullptr));
        labelRAM->setText(QCoreApplication::translate("MainWindow", "S\341\273\255 d\341\273\245ng RAM:", nullptr));
        progressBarRAM->setFormat(QCoreApplication::translate("MainWindow", "%p%", nullptr));
        labelIP->setText(QCoreApplication::translate("MainWindow", "IP Local: \304\220ang ki\341\273\203m tra...", nullptr));
        lblIPPublic->setText(QCoreApplication::translate("MainWindow", "IP Public: \304\220ang ki\341\273\203m tra...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
