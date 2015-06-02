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
#include "oglTools/simpleglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lbLabel;
    SimpleGLWidget *glDigit;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPrev;
    QLineEdit *edId;
    QPushButton *btnNext;
    QPushButton *btnTrain;
    SimpleGLWidget *plot2d;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1148, 1053);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 404, 475));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
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

        btnTrain = new QPushButton(centralWidget);
        btnTrain->setObjectName(QStringLiteral("btnTrain"));
        btnTrain->setGeometry(QRect(460, 10, 99, 27));
        plot2d = new SimpleGLWidget(centralWidget);
        plot2d->setObjectName(QStringLiteral("plot2d"));
        plot2d->setGeometry(QRect(450, 60, 391, 391));
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

        toolBar->addSeparator();
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lbLabel->setText(QString());
        btnPrev->setText(QApplication::translate("MainWindow", "<", 0));
        btnNext->setText(QApplication::translate("MainWindow", ">", 0));
        btnTrain->setText(QApplication::translate("MainWindow", "Train", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
