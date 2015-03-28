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
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionLight;
    QAction *actionCamera;
    QAction *actionCuboid;
    QAction *actionSphere;
    QAction *actionCapsule;
    QAction *actionCylinder;
    QAction *actionPlane;
    QAction *actionWavefront;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    GLWidget *glScene;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuObjects;
    QMenu *menu3D_Objects;
    QStatusBar *statusBar;
    QDockWidget *dockHierarchy;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QDockWidget *dockInspector;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(793, 697);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionLight = new QAction(MainWindow);
        actionLight->setObjectName(QStringLiteral("actionLight"));
        actionCamera = new QAction(MainWindow);
        actionCamera->setObjectName(QStringLiteral("actionCamera"));
        actionCuboid = new QAction(MainWindow);
        actionCuboid->setObjectName(QStringLiteral("actionCuboid"));
        actionSphere = new QAction(MainWindow);
        actionSphere->setObjectName(QStringLiteral("actionSphere"));
        actionCapsule = new QAction(MainWindow);
        actionCapsule->setObjectName(QStringLiteral("actionCapsule"));
        actionCylinder = new QAction(MainWindow);
        actionCylinder->setObjectName(QStringLiteral("actionCylinder"));
        actionPlane = new QAction(MainWindow);
        actionPlane->setObjectName(QStringLiteral("actionPlane"));
        actionWavefront = new QAction(MainWindow);
        actionWavefront->setObjectName(QStringLiteral("actionWavefront"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setStyleSheet(QLatin1String("background-color: #AAAAAA;\n"
"border: 1px solid #777777;\n"
"border-radius: 8px;"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        glScene = new GLWidget(centralWidget);
        glScene->setObjectName(QStringLiteral("glScene"));
        glScene->setStyleSheet(QStringLiteral("border-radius: 8px;"));

        gridLayout_3->addWidget(glScene, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 793, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuObjects = new QMenu(menuBar);
        menuObjects->setObjectName(QStringLiteral("menuObjects"));
        menu3D_Objects = new QMenu(menuObjects);
        menu3D_Objects->setObjectName(QStringLiteral("menu3D_Objects"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockHierarchy = new QDockWidget(MainWindow);
        dockHierarchy->setObjectName(QStringLiteral("dockHierarchy"));
        dockHierarchy->setMaximumSize(QSize(524287, 200));
        dockHierarchy->setStyleSheet(QLatin1String("QDockWidget{\n"
"font-family: \"Roboto Lt\";\n"
"font-size: 12px;\n"
"font: bold;\n"
"color:#D5C147;\n"
"}\n"
"\n"
" QDockWidget::title {\n"
"text-align: left;\n"
"background-color: #666666;\n"
"border: 1px solid #999999;\n"
"border-top-right-radius: 8px;\n"
"border-top-left-radius: 8px;\n"
"border-bottom: 1px solid #222222;\n"
"}"));
        dockHierarchy->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidgetContents->setStyleSheet(QLatin1String("QWidget {\n"
"border: 1px solid #777777;\n"
"border-top: none;\n"
"background-color: #AAAAAA;\n"
"border-bottom-right-radius: 8px;\n"
"border-bottom-left-radius: 8px;\n"
"}\n"
""));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeWidget = new QTreeWidget(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setStyleSheet(QLatin1String("border: 0;\n"
"color:#000000\n"
"\n"
"\n"
""));
        treeWidget->header()->setVisible(false);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        dockHierarchy->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockHierarchy);
        dockInspector = new QDockWidget(MainWindow);
        dockInspector->setObjectName(QStringLiteral("dockInspector"));
        dockInspector->setStyleSheet(QLatin1String("QDockWidget{\n"
"font-family: \"Roboto Lt\";\n"
"font-size: 12px;\n"
"font: bold;\n"
"color:#D5C147;\n"
"}\n"
"\n"
" QDockWidget::title {\n"
"text-align: left;\n"
"background-color: #666666;\n"
"border: 1px solid #777777;\n"
"border-top-right-radius: 8px;\n"
"border-top-left-radius: 8px;\n"
"border-bottom: 1px solid #222222;\n"
"}"));
        dockInspector->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidgetContents_2->setStyleSheet(QLatin1String("QWidget {\n"
"border: 1px solid #777777;\n"
"border-top: none;\n"
"background-color: #aaaaaa;\n"
"border-bottom-right-radius: 8px;\n"
"border-bottom-left-radius: 8px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        dockInspector->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockInspector);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuObjects->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuObjects->addAction(menu3D_Objects->menuAction());
        menuObjects->addAction(actionLight);
        menuObjects->addAction(actionCamera);
        menu3D_Objects->addAction(actionCuboid);
        menu3D_Objects->addAction(actionSphere);
        menu3D_Objects->addAction(actionCapsule);
        menu3D_Objects->addAction(actionCylinder);
        menu3D_Objects->addAction(actionPlane);
        menu3D_Objects->addAction(actionWavefront);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionLight->setText(QApplication::translate("MainWindow", "Light", 0));
        actionCamera->setText(QApplication::translate("MainWindow", "Camera", 0));
        actionCuboid->setText(QApplication::translate("MainWindow", "Cuboid", 0));
        actionSphere->setText(QApplication::translate("MainWindow", "Sphere", 0));
        actionCapsule->setText(QApplication::translate("MainWindow", "Capsule", 0));
        actionCylinder->setText(QApplication::translate("MainWindow", "Cylinder", 0));
        actionPlane->setText(QApplication::translate("MainWindow", "Plane", 0));
        actionWavefront->setText(QApplication::translate("MainWindow", "Wavefront", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuObjects->setTitle(QApplication::translate("MainWindow", "Objects", 0));
        menu3D_Objects->setTitle(QApplication::translate("MainWindow", "3D Objects", 0));
        dockHierarchy->setWindowTitle(QApplication::translate("MainWindow", "Hierarchy", 0));
        dockInspector->setWindowTitle(QApplication::translate("MainWindow", "Inspector", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
