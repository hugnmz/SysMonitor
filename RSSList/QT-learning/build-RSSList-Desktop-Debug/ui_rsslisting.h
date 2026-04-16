/********************************************************************************
** Form generated from reading UI file 'rsslisting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RSSLISTING_H
#define UI_RSSLISTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RSSListing
{
public:

    void setupUi(QWidget *RSSListing)
    {
        if (RSSListing->objectName().isEmpty())
            RSSListing->setObjectName(QString::fromUtf8("RSSListing"));
        RSSListing->resize(800, 600);

        retranslateUi(RSSListing);

        QMetaObject::connectSlotsByName(RSSListing);
    } // setupUi

    void retranslateUi(QWidget *RSSListing)
    {
        RSSListing->setWindowTitle(QCoreApplication::translate("RSSListing", "RSSListing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RSSListing: public Ui_RSSListing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RSSLISTING_H
