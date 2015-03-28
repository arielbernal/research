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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    GLWidget *glScene;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(614, 557);
        MainWindow->setStyleSheet(QStringLiteral("background-color: #222222;"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMaximumSize(QSize(973, 757));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        glScene = new GLWidget(centralWidget);
        glScene->setObjectName(QStringLiteral("glScene"));
        glScene->setAutoFillBackground(false);

        verticalLayout->addWidget(glScene);

        MainWindow->setCentralWidget(centralWidget);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setMinimumSize(QSize(274, 232));
        QFont font;
        font.setFamily(QStringLiteral("Roboto Lt"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        dockWidget->setFont(font);
        dockWidget->setStyleSheet(QLatin1String("QDockWidget{\n"
"font-family: \"Roboto Lt\";\n"
"font-size: 12px;\n"
"font: bold;\n"
"color:#D5C147;\n"
"}\n"
" QDockWidget::title {\n"
"text-align: left;\n"
"background-color: #333333;\n"
"border: 1px solid #999999;\n"
"border-top-right-radius: 8px;\n"
"border-top-left-radius: 8px;\n"
"border-bottom: 1px solid #222222;\n"
"}\n"
"\n"
"\n"
""));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidgetContents->setStyleSheet(QLatin1String("QWidget {\n"
"border: 1px solid #999999;\n"
"border-top: none;\n"
"background-color: #333333;\n"
"border-bottom-right-radius: 8px;\n"
"border-bottom-left-radius: 8px;\n"
"}\n"
""));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        treeWidget = new QTreeWidget(dockWidgetContents);
        new QTreeWidgetItem(treeWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMinimumSize(QSize(0, 0));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setStyleSheet(QLatin1String("border: 0;\n"
"color:#AAAA77\n"
"\n"
"\n"
""));
        treeWidget->setDragEnabled(true);
        treeWidget->setDragDropOverwriteMode(false);
        treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
        treeWidget->setDefaultDropAction(Qt::MoveAction);
        treeWidget->setHeaderHidden(true);
        treeWidget->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "rgQt", 0));
        dockWidget->setWindowTitle(QApplication::translate("MainWindow", "Hierarchy", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "1", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "testing", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
