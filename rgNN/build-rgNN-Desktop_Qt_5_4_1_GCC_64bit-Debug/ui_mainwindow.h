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
    QAction *actionStartTraining;
    QAction *actionStopTraining;
    QWidget *centralWidget;
    QWidget *layoutWidget;
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
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *chartMSE;
    QCustomPlot *chartErrors;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnStatTraining;
    QPushButton *btnStatTest;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnErrPrev;
    QPushButton *btnErrNext;
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
        actionStartTraining = new QAction(MainWindow);
        actionStartTraining->setObjectName(QStringLiteral("actionStartTraining"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStartTraining->setIcon(icon2);
        actionStopTraining = new QAction(MainWindow);
        actionStopTraining->setObjectName(QStringLiteral("actionStopTraining"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStopTraining->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 406, 510));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
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
        lbLabel = new QLabel(layoutWidget);
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

        glDigit = new SimpleGLWidget(layoutWidget);
        glDigit->setObjectName(QStringLiteral("glDigit"));
        glDigit->setMinimumSize(QSize(400, 400));

        verticalLayout->addWidget(glDigit);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnPrev = new QPushButton(layoutWidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));

        horizontalLayout->addWidget(btnPrev);

        edId = new QLineEdit(layoutWidget);
        edId->setObjectName(QStringLiteral("edId"));
        edId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(edId);

        btnNext = new QPushButton(layoutWidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        horizontalLayout->addWidget(btnNext);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_2);

        btnTest = new QPushButton(layoutWidget);
        btnTest->setObjectName(QStringLiteral("btnTest"));

        verticalLayout_4->addWidget(btnTest);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(440, 10, 302, 608));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        chartMSE = new QCustomPlot(layoutWidget1);
        chartMSE->setObjectName(QStringLiteral("chartMSE"));
        chartMSE->setMinimumSize(QSize(300, 300));
        chartMSE->setMaximumSize(QSize(300, 300));

        verticalLayout_3->addWidget(chartMSE);

        chartErrors = new QCustomPlot(layoutWidget1);
        chartErrors->setObjectName(QStringLiteral("chartErrors"));
        chartErrors->setMinimumSize(QSize(300, 300));
        chartErrors->setMaximumSize(QSize(300, 300));

        verticalLayout_3->addWidget(chartErrors);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(60, 570, 295, 64));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        btnStatTraining = new QPushButton(widget);
        btnStatTraining->setObjectName(QStringLiteral("btnStatTraining"));

        verticalLayout_5->addWidget(btnStatTraining);

        btnStatTest = new QPushButton(widget);
        btnStatTest->setObjectName(QStringLiteral("btnStatTest"));

        verticalLayout_5->addWidget(btnStatTest);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnErrPrev = new QPushButton(widget);
        btnErrPrev->setObjectName(QStringLiteral("btnErrPrev"));

        horizontalLayout_2->addWidget(btnErrPrev);

        btnErrNext = new QPushButton(widget);
        btnErrNext->setObjectName(QStringLiteral("btnErrNext"));

        horizontalLayout_2->addWidget(btnErrNext);


        verticalLayout_6->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_6);

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

        toolBar->addAction(actionLoad);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionStartTraining);
        toolBar->addAction(actionStopTraining);
        toolBar->addSeparator();

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
        actionStartTraining->setText(QApplication::translate("MainWindow", "StartTraining", 0));
        actionStopTraining->setText(QApplication::translate("MainWindow", "StopTraining", 0));
        lbLabel->setText(QString());
        btnPrev->setText(QApplication::translate("MainWindow", "<", 0));
        btnNext->setText(QApplication::translate("MainWindow", ">", 0));
        btnTest->setText(QApplication::translate("MainWindow", "Test", 0));
        btnStatTraining->setText(QApplication::translate("MainWindow", "Stat Training", 0));
        btnStatTest->setText(QApplication::translate("MainWindow", "Stat Test", 0));
        label->setText(QApplication::translate("MainWindow", "Errors", 0));
        btnErrPrev->setText(QApplication::translate("MainWindow", "<", 0));
        btnErrNext->setText(QApplication::translate("MainWindow", ">", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
