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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfiguration;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionExit;
    QWidget *centralWidget;
    QTextBrowser *textConsole;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *btnRead;
    QPushButton *pushButton_2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSlider *sldHL;
    QLineEdit *edHL;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sldHH;
    QLineEdit *edHH;
    QHBoxLayout *horizontalLayout_4;
    QSlider *sldSL;
    QLineEdit *edSL;
    QHBoxLayout *horizontalLayout_5;
    QSlider *sldSH;
    QLineEdit *edSH;
    QHBoxLayout *horizontalLayout_6;
    QSlider *sldVL;
    QLineEdit *edVL;
    QHBoxLayout *horizontalLayout_7;
    QSlider *sldVH;
    QLineEdit *edVH;
    GLWidget *glScene;
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
        actionConfiguration->setCheckable(true);
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textConsole = new QTextBrowser(centralWidget);
        textConsole->setObjectName(QStringLiteral("textConsole"));
        textConsole->setGeometry(QRect(-40, -290, 176, 341));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        btnRead = new QPushButton(widget);
        btnRead->setObjectName(QStringLiteral("btnRead"));

        horizontalLayout->addWidget(btnRead);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(11, 10, 1226, 962));
        horizontalLayout_8 = new QHBoxLayout(widget1);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sldHL = new QSlider(widget1);
        sldHL->setObjectName(QStringLiteral("sldHL"));
        sldHL->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sldHL);

        edHL = new QLineEdit(widget1);
        edHL->setObjectName(QStringLiteral("edHL"));

        horizontalLayout_2->addWidget(edHL);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        sldHH = new QSlider(widget1);
        sldHH->setObjectName(QStringLiteral("sldHH"));
        sldHH->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(sldHH);

        edHH = new QLineEdit(widget1);
        edHH->setObjectName(QStringLiteral("edHH"));

        horizontalLayout_3->addWidget(edHH);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        sldSL = new QSlider(widget1);
        sldSL->setObjectName(QStringLiteral("sldSL"));
        sldSL->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(sldSL);

        edSL = new QLineEdit(widget1);
        edSL->setObjectName(QStringLiteral("edSL"));

        horizontalLayout_4->addWidget(edSL);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        sldSH = new QSlider(widget1);
        sldSH->setObjectName(QStringLiteral("sldSH"));
        sldSH->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(sldSH);

        edSH = new QLineEdit(widget1);
        edSH->setObjectName(QStringLiteral("edSH"));

        horizontalLayout_5->addWidget(edSH);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        sldVL = new QSlider(widget1);
        sldVL->setObjectName(QStringLiteral("sldVL"));
        sldVL->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(sldVL);

        edVL = new QLineEdit(widget1);
        edVL->setObjectName(QStringLiteral("edVL"));

        horizontalLayout_6->addWidget(edVL);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        sldVH = new QSlider(widget1);
        sldVH->setObjectName(QStringLiteral("sldVH"));
        sldVH->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(sldVH);

        edVH = new QLineEdit(widget1);
        edVH->setObjectName(QStringLiteral("edVH"));

        horizontalLayout_7->addWidget(edVH);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_8->addLayout(verticalLayout_3);

        glScene = new GLWidget(widget1);
        glScene->setObjectName(QStringLiteral("glScene"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glScene->sizePolicy().hasHeightForWidth());
        glScene->setSizePolicy(sizePolicy);
        glScene->setMinimumSize(QSize(960, 960));
        glScene->setMaximumSize(QSize(960, 960));

        horizontalLayout_8->addWidget(glScene);

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

        toolBar->addAction(actionConnect);
        toolBar->addAction(actionDisconnect);
        toolBar->addAction(actionConfiguration);
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
        pushButton->setText(QApplication::translate("MainWindow", "Send 1", 0));
        btnRead->setText(QApplication::translate("MainWindow", "Read", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Send 2", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
