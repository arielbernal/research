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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../common/qtTools/qcustomplot.h"
#include "oglTools/simpleglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionTrain;
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lbLabel;
    SimpleGLWidget *glDigit;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPrev;
    QLineEdit *edId;
    QPushButton *btnNext;
    QPushButton *btnTest;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *chartMSE;
    QCustomPlot *chartErrors;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1148, 1053);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/SaveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionTrain = new QAction(MainWindow);
        actionTrain->setObjectName(QStringLiteral("actionTrain"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Reboot.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTrain->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 406, 510));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbLabel = new QLabel(widget);
        lbLabel->setObjectName(QStringLiteral("lbLabel"));
        lbLabel->setMaximumSize(QSize(10000, 50));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        lbLabel->setFont(font);
        lbLabel->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightblue;"));
        lbLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbLabel);

        glDigit = new SimpleGLWidget(widget);
        glDigit->setObjectName(QStringLiteral("glDigit"));
        glDigit->setMinimumSize(QSize(400, 400));

        verticalLayout->addWidget(glDigit);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnPrev = new QPushButton(widget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));

        horizontalLayout->addWidget(btnPrev);

        edId = new QLineEdit(widget);
        edId->setObjectName(QStringLiteral("edId"));
        edId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(edId);

        btnNext = new QPushButton(widget);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        horizontalLayout->addWidget(btnNext);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_2);

        btnTest = new QPushButton(widget);
        btnTest->setObjectName(QStringLiteral("btnTest"));

        verticalLayout_4->addWidget(btnTest);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(440, 10, 302, 608));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        chartMSE = new QCustomPlot(widget1);
        chartMSE->setObjectName(QStringLiteral("chartMSE"));
        chartMSE->setMinimumSize(QSize(300, 300));
        chartMSE->setMaximumSize(QSize(300, 300));

        verticalLayout_3->addWidget(chartMSE);

        chartErrors = new QCustomPlot(widget1);
        chartErrors->setObjectName(QStringLiteral("chartErrors"));
        chartErrors->setMinimumSize(QSize(300, 300));
        chartErrors->setMaximumSize(QSize(300, 300));

        verticalLayout_3->addWidget(chartErrors);

        MainWindow->setCentralWidget(centralWidget);
        btnTest->raise();
        chartErrors->raise();
        chartMSE->raise();
        glDigit->raise();
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

        toolBar->addSeparator();
        toolBar->addAction(actionLoad);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionTrain);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
#ifndef QT_NO_TOOLTIP
        actionLoad->setToolTip(QApplication::translate("MainWindow", "Load Weights", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Save Weights", 0));
#endif // QT_NO_TOOLTIP
        actionTrain->setText(QApplication::translate("MainWindow", "Train", 0));
#ifndef QT_NO_TOOLTIP
        actionTrain->setToolTip(QApplication::translate("MainWindow", "Train NN", 0));
#endif // QT_NO_TOOLTIP
        lbLabel->setText(QString());
        btnPrev->setText(QApplication::translate("MainWindow", "<", 0));
        btnNext->setText(QApplication::translate("MainWindow", ">", 0));
        btnTest->setText(QApplication::translate("MainWindow", "Test", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
