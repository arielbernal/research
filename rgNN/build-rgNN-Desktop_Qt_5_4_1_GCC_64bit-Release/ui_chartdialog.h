/********************************************************************************
** Form generated from reading UI file 'chartdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTDIALOG_H
#define UI_CHARTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ChartDialog
{
public:

    void setupUi(QDialog *ChartDialog)
    {
        if (ChartDialog->objectName().isEmpty())
            ChartDialog->setObjectName(QStringLiteral("ChartDialog"));
        ChartDialog->resize(665, 600);

        retranslateUi(ChartDialog);

        QMetaObject::connectSlotsByName(ChartDialog);
    } // setupUi

    void retranslateUi(QDialog *ChartDialog)
    {
        ChartDialog->setWindowTitle(QApplication::translate("ChartDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ChartDialog: public Ui_ChartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTDIALOG_H
