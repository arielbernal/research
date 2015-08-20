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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfiguration;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionExit;
    QAction *actionCameraOn;
    QAction *actionCameraOff;
    QWidget *centralWidget;
    QProgressBar *motorLeftF;
    QProgressBar *motorRightF;
    QProgressBar *motorRightB;
    QProgressBar *motorLeftB;
    QPushButton *btnStartCapture;
    QPushButton *btnStopCapture;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1148, 1053);
        actionConfiguration = new QAction(MainWindow);
        actionConfiguration->setObjectName(QStringLiteral("actionConfiguration"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfiguration->setIcon(icon);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/bulbOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon1);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/bulbOn.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Shutdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionCameraOn = new QAction(MainWindow);
        actionCameraOn->setObjectName(QStringLiteral("actionCameraOn"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QStringLiteral(":/icons/camera.png"), QSize(), QIcon::Normal, QIcon::On);
        actionCameraOn->setIcon(icon4);
        actionCameraOff = new QAction(MainWindow);
        actionCameraOff->setObjectName(QStringLiteral("actionCameraOff"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/camera_red.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCameraOff->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        motorLeftF = new QProgressBar(centralWidget);
        motorLeftF->setObjectName(QStringLiteral("motorLeftF"));
        motorLeftF->setGeometry(QRect(50, 50, 31, 211));
        motorLeftF->setValue(24);
        motorLeftF->setOrientation(Qt::Vertical);
        motorLeftF->setInvertedAppearance(false);
        motorLeftF->setTextDirection(QProgressBar::TopToBottom);
        motorRightF = new QProgressBar(centralWidget);
        motorRightF->setObjectName(QStringLiteral("motorRightF"));
        motorRightF->setGeometry(QRect(220, 50, 31, 211));
        motorRightF->setValue(24);
        motorRightF->setOrientation(Qt::Vertical);
        motorRightF->setInvertedAppearance(false);
        motorRightF->setTextDirection(QProgressBar::TopToBottom);
        motorRightB = new QProgressBar(centralWidget);
        motorRightB->setObjectName(QStringLiteral("motorRightB"));
        motorRightB->setGeometry(QRect(220, 290, 31, 211));
        motorRightB->setValue(24);
        motorRightB->setOrientation(Qt::Vertical);
        motorRightB->setInvertedAppearance(true);
        motorRightB->setTextDirection(QProgressBar::TopToBottom);
        motorLeftB = new QProgressBar(centralWidget);
        motorLeftB->setObjectName(QStringLiteral("motorLeftB"));
        motorLeftB->setGeometry(QRect(50, 290, 31, 211));
        motorLeftB->setValue(24);
        motorLeftB->setOrientation(Qt::Vertical);
        motorLeftB->setInvertedAppearance(true);
        motorLeftB->setTextDirection(QProgressBar::TopToBottom);
        btnStartCapture = new QPushButton(centralWidget);
        btnStartCapture->setObjectName(QStringLiteral("btnStartCapture"));
        btnStartCapture->setGeometry(QRect(408, 250, 131, 27));
        btnStopCapture = new QPushButton(centralWidget);
        btnStopCapture->setObjectName(QStringLiteral("btnStopCapture"));
        btnStopCapture->setGeometry(QRect(560, 250, 131, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1148, 25));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionConnect);
        toolBar->addAction(actionDisconnect);
        toolBar->addAction(actionConfiguration);
        toolBar->addSeparator();
        toolBar->addAction(actionCameraOn);
        toolBar->addAction(actionCameraOff);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionConfiguration->setText(QApplication::translate("MainWindow", "Configuration", 0));
#ifndef QT_NO_TOOLTIP
        actionConfiguration->setToolTip(QApplication::translate("MainWindow", "Configuration", 0));
#endif // QT_NO_TOOLTIP
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect", 0));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "Exit", 0));
#endif // QT_NO_TOOLTIP
        actionCameraOn->setText(QApplication::translate("MainWindow", "Camera On", 0));
#ifndef QT_NO_TOOLTIP
        actionCameraOn->setToolTip(QApplication::translate("MainWindow", "Activate Camera", 0));
#endif // QT_NO_TOOLTIP
        actionCameraOn->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0));
        actionCameraOff->setText(QApplication::translate("MainWindow", "Camera Off", 0));
#ifndef QT_NO_TOOLTIP
        actionCameraOff->setToolTip(QApplication::translate("MainWindow", "Turn Camera Off", 0));
#endif // QT_NO_TOOLTIP
        btnStartCapture->setText(QApplication::translate("MainWindow", "Start Capture", 0));
        btnStopCapture->setText(QApplication::translate("MainWindow", "Stop Capture", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H