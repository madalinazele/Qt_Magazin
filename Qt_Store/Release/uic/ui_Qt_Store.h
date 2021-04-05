/********************************************************************************
** Form generated from reading UI file 'Qt_Store.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_STORE_H
#define UI_QT_STORE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_StoreClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_StoreClass)
    {
        if (Qt_StoreClass->objectName().isEmpty())
            Qt_StoreClass->setObjectName(QString::fromUtf8("Qt_StoreClass"));
        Qt_StoreClass->resize(600, 400);
        menuBar = new QMenuBar(Qt_StoreClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Qt_StoreClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_StoreClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Qt_StoreClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Qt_StoreClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Qt_StoreClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Qt_StoreClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Qt_StoreClass->setStatusBar(statusBar);

        retranslateUi(Qt_StoreClass);

        QMetaObject::connectSlotsByName(Qt_StoreClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_StoreClass)
    {
        Qt_StoreClass->setWindowTitle(QCoreApplication::translate("Qt_StoreClass", "Qt_Store", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Qt_StoreClass: public Ui_Qt_StoreClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_STORE_H
