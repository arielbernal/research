/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "../common/oglTools/simpleglwidget.h"
#include "../common/qtTools/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btnTrain;
    SimpleGLWidget *plot2d;
    QCustomPlot *chartMSE;
    QCustomPlot *chartErrors;
    QPushButton *btnSave;
    QPushButton *btnLoad;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1148, 1053);
        MainWindow->setMinimumSize(QSize(1024, 1024));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnTrain = new QPushButton(centralWidget);
        btnTrain->setObjectName(QStringLiteral("btnTrain"));
        btnTrain->setGeometry(QRect(410, 10, 99, 27));
        plot2d = new SimpleGLWidget(centralWidget);
        plot2d->setObjectName(QStringLiteral("plot2d"));
        plot2d->setGeometry(QRect(10, 10, 391, 391));
        chartMSE = new QCustomPlot(centralWidget);
        chartMSE->setObjectName(QStringLiteral("chartMSE"));
        chartMSE->setGeometry(QRect(10, 410, 391, 381));
        chartErrors = new QCustomPlot(centralWidget);
        chartErrors->setObjectName(QStringLiteral("chartErrors"));
        chartErrors->setGeometry(QRect(410, 410, 391, 381));
        btnSave = new QPushButton(centralWidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(410, 50, 99, 27));
        btnLoad = new QPushButton(centralWidget);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));
        btnLoad->setGeometry(QRect(410, 90, 99, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1148, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addSeparator();
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btnTrain->setText(QApplication::translate("MainWindow", "Train", 0));
        btnSave->setText(QApplication::translate("MainWindow", "Save", 0));
        btnLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
