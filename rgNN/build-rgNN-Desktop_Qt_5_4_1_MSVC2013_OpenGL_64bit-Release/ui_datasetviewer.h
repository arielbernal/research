/********************************************************************************
** Form generated from reading UI file 'datasetviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATASETVIEWER_H
#define UI_DATASETVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "oglTools/simpleglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DatasetViewer
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout;
    QLabel *lbLabel;
    SimpleGLWidget *glDigit;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QFrame *line_2;
    QLineEdit *edIndex;
    QLineEdit *edN;
    QFrame *line;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lbLabel_2;
    QPushButton *btnUpdateStats;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbErrors;
    QSpacerItem *horizontalSpacer;
    QLineEdit *edErrors;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbAccuracy;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edAccuracy;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbMSE;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edMSE;
    QHBoxLayout *horizontalLayout;
    QLabel *lbErrorRate;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *edErrorRate;
    QHBoxLayout *horizontalLayout_18;
    QLabel *lbLabel_3;
    QPushButton *btnUpdateTest;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_11;
    QLineEdit *edSampleId;
    QLineEdit *edSamplesN;
    QHBoxLayout *horizontalLayout_17;
    QLabel *lbResult;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLineEdit *ed0;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QLineEdit *ed1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QLineEdit *ed2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QLineEdit *ed3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *ed4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QLineEdit *ed5;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_7;
    QLineEdit *ed6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_10;
    QLineEdit *ed7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_9;
    QLineEdit *ed8;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_8;
    QLineEdit *ed9;
    QCheckBox *chkDigitGrid;
    QCheckBox *chkAutoTest;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_6;
    QListWidget *listFilter;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_12;
    QLabel *lbAppliedFilter;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *btnApplyFilter;
    QPushButton *btnClearFilter;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DatasetViewer)
    {
        if (DatasetViewer->objectName().isEmpty())
            DatasetViewer->setObjectName(QStringLiteral("DatasetViewer"));
        DatasetViewer->resize(724, 518);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DatasetViewer->sizePolicy().hasHeightForWidth());
        DatasetViewer->setSizePolicy(sizePolicy);
        DatasetViewer->setMaximumSize(QSize(200000, 20000));
        gridLayout_2 = new QGridLayout(DatasetViewer);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbLabel = new QLabel(DatasetViewer);
        lbLabel->setObjectName(QStringLiteral("lbLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbLabel->sizePolicy().hasHeightForWidth());
        lbLabel->setSizePolicy(sizePolicy1);
        lbLabel->setMinimumSize(QSize(400, 0));
        lbLabel->setMaximumSize(QSize(400, 50));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        lbLabel->setFont(font);
        lbLabel->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightgreen;"));
        lbLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbLabel);

        glDigit = new SimpleGLWidget(DatasetViewer);
        glDigit->setObjectName(QStringLiteral("glDigit"));
        sizePolicy1.setHeightForWidth(glDigit->sizePolicy().hasHeightForWidth());
        glDigit->setSizePolicy(sizePolicy1);
        glDigit->setMinimumSize(QSize(400, 400));
        glDigit->setMaximumSize(QSize(400, 400));

        verticalLayout->addWidget(glDigit);


        verticalLayout_8->addLayout(verticalLayout);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        btnFirst = new QPushButton(DatasetViewer);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setMinimumSize(QSize(40, 0));
        btnFirst->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_19->addWidget(btnFirst);

        btnPrev = new QPushButton(DatasetViewer);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setMinimumSize(QSize(40, 0));
        btnPrev->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_19->addWidget(btnPrev);

        line_2 = new QFrame(DatasetViewer);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(line_2);

        edIndex = new QLineEdit(DatasetViewer);
        edIndex->setObjectName(QStringLiteral("edIndex"));
        edIndex->setMinimumSize(QSize(60, 0));
        edIndex->setMaximumSize(QSize(60, 16777215));
        edIndex->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edIndex->setReadOnly(false);

        horizontalLayout_19->addWidget(edIndex);

        edN = new QLineEdit(DatasetViewer);
        edN->setObjectName(QStringLiteral("edN"));
        edN->setMinimumSize(QSize(60, 0));
        edN->setMaximumSize(QSize(60, 16777215));
        edN->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edN->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edN->setReadOnly(true);

        horizontalLayout_19->addWidget(edN);

        line = new QFrame(DatasetViewer);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(line);

        btnNext = new QPushButton(DatasetViewer);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setMinimumSize(QSize(40, 0));
        btnNext->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_19->addWidget(btnNext);

        btnLast = new QPushButton(DatasetViewer);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setMinimumSize(QSize(40, 0));
        btnLast->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_19->addWidget(btnLast);


        verticalLayout_8->addLayout(horizontalLayout_19);


        gridLayout_2->addLayout(verticalLayout_8, 0, 0, 1, 1);

        tabWidget = new QTabWidget(DatasetViewer);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lbLabel_2 = new QLabel(tab);
        lbLabel_2->setObjectName(QStringLiteral("lbLabel_2"));
        lbLabel_2->setMaximumSize(QSize(10000, 50));
        lbLabel_2->setFont(font);
        lbLabel_2->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightblue;"));
        lbLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(lbLabel_2);

        btnUpdateStats = new QPushButton(tab);
        btnUpdateStats->setObjectName(QStringLiteral("btnUpdateStats"));
        sizePolicy1.setHeightForWidth(btnUpdateStats->sizePolicy().hasHeightForWidth());
        btnUpdateStats->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(btnUpdateStats);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lbErrors = new QLabel(tab);
        lbErrors->setObjectName(QStringLiteral("lbErrors"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lbErrors->sizePolicy().hasHeightForWidth());
        lbErrors->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(lbErrors);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        edErrors = new QLineEdit(tab);
        edErrors->setObjectName(QStringLiteral("edErrors"));
        sizePolicy1.setHeightForWidth(edErrors->sizePolicy().hasHeightForWidth());
        edErrors->setSizePolicy(sizePolicy1);
        edErrors->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edErrors->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edErrors->setReadOnly(true);

        horizontalLayout_4->addWidget(edErrors);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbAccuracy = new QLabel(tab);
        lbAccuracy->setObjectName(QStringLiteral("lbAccuracy"));
        sizePolicy2.setHeightForWidth(lbAccuracy->sizePolicy().hasHeightForWidth());
        lbAccuracy->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(lbAccuracy);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        edAccuracy = new QLineEdit(tab);
        edAccuracy->setObjectName(QStringLiteral("edAccuracy"));
        sizePolicy1.setHeightForWidth(edAccuracy->sizePolicy().hasHeightForWidth());
        edAccuracy->setSizePolicy(sizePolicy1);
        edAccuracy->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edAccuracy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edAccuracy->setReadOnly(true);

        horizontalLayout_3->addWidget(edAccuracy);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbMSE = new QLabel(tab);
        lbMSE->setObjectName(QStringLiteral("lbMSE"));
        sizePolicy2.setHeightForWidth(lbMSE->sizePolicy().hasHeightForWidth());
        lbMSE->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(lbMSE);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        edMSE = new QLineEdit(tab);
        edMSE->setObjectName(QStringLiteral("edMSE"));
        sizePolicy1.setHeightForWidth(edMSE->sizePolicy().hasHeightForWidth());
        edMSE->setSizePolicy(sizePolicy1);
        edMSE->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edMSE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edMSE->setReadOnly(true);

        horizontalLayout_2->addWidget(edMSE);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lbErrorRate = new QLabel(tab);
        lbErrorRate->setObjectName(QStringLiteral("lbErrorRate"));
        sizePolicy2.setHeightForWidth(lbErrorRate->sizePolicy().hasHeightForWidth());
        lbErrorRate->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(lbErrorRate);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        edErrorRate = new QLineEdit(tab);
        edErrorRate->setObjectName(QStringLiteral("edErrorRate"));
        sizePolicy1.setHeightForWidth(edErrorRate->sizePolicy().hasHeightForWidth());
        edErrorRate->setSizePolicy(sizePolicy1);
        edErrorRate->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edErrorRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edErrorRate->setReadOnly(true);

        horizontalLayout->addWidget(edErrorRate);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 2);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        lbLabel_3 = new QLabel(tab);
        lbLabel_3->setObjectName(QStringLiteral("lbLabel_3"));
        lbLabel_3->setMaximumSize(QSize(10000, 50));
        lbLabel_3->setFont(font);
        lbLabel_3->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightblue;"));
        lbLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(lbLabel_3);

        btnUpdateTest = new QPushButton(tab);
        btnUpdateTest->setObjectName(QStringLiteral("btnUpdateTest"));
        sizePolicy1.setHeightForWidth(btnUpdateTest->sizePolicy().hasHeightForWidth());
        btnUpdateTest->setSizePolicy(sizePolicy1);

        horizontalLayout_18->addWidget(btnUpdateTest);


        gridLayout->addLayout(horizontalLayout_18, 1, 0, 1, 2);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_20->addWidget(label_11);

        edSampleId = new QLineEdit(tab);
        edSampleId->setObjectName(QStringLiteral("edSampleId"));
        edSampleId->setMinimumSize(QSize(80, 0));
        edSampleId->setMaximumSize(QSize(80, 16777215));
        edSampleId->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edSampleId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edSampleId->setReadOnly(true);

        horizontalLayout_20->addWidget(edSampleId);

        edSamplesN = new QLineEdit(tab);
        edSamplesN->setObjectName(QStringLiteral("edSamplesN"));
        edSamplesN->setMinimumSize(QSize(80, 0));
        edSamplesN->setMaximumSize(QSize(80, 16777215));
        edSamplesN->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        edSamplesN->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edSamplesN->setReadOnly(true);

        horizontalLayout_20->addWidget(edSamplesN);


        gridLayout->addLayout(horizontalLayout_20, 2, 0, 1, 2);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        lbResult = new QLabel(tab);
        lbResult->setObjectName(QStringLiteral("lbResult"));
        lbResult->setMinimumSize(QSize(50, 50));
        lbResult->setMaximumSize(QSize(50, 50));
        lbResult->setFont(font);
        lbResult->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #F0F010;"));
        lbResult->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(lbResult);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_7->addWidget(label);

        ed0 = new QLineEdit(tab);
        ed0->setObjectName(QStringLiteral("ed0"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ed0->sizePolicy().hasHeightForWidth());
        ed0->setSizePolicy(sizePolicy3);
        ed0->setMinimumSize(QSize(80, 25));
        ed0->setMaximumSize(QSize(80, 25));
        ed0->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed0->setReadOnly(true);

        horizontalLayout_7->addWidget(ed0);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_8->addWidget(label_2);

        ed1 = new QLineEdit(tab);
        ed1->setObjectName(QStringLiteral("ed1"));
        sizePolicy3.setHeightForWidth(ed1->sizePolicy().hasHeightForWidth());
        ed1->setSizePolicy(sizePolicy3);
        ed1->setMinimumSize(QSize(80, 25));
        ed1->setMaximumSize(QSize(80, 25));
        ed1->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed1->setReadOnly(true);

        horizontalLayout_8->addWidget(ed1);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_10->addWidget(label_3);

        ed2 = new QLineEdit(tab);
        ed2->setObjectName(QStringLiteral("ed2"));
        sizePolicy3.setHeightForWidth(ed2->sizePolicy().hasHeightForWidth());
        ed2->setSizePolicy(sizePolicy3);
        ed2->setMinimumSize(QSize(80, 25));
        ed2->setMaximumSize(QSize(80, 25));
        ed2->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed2->setReadOnly(true);

        horizontalLayout_10->addWidget(ed2);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        ed3 = new QLineEdit(tab);
        ed3->setObjectName(QStringLiteral("ed3"));
        sizePolicy3.setHeightForWidth(ed3->sizePolicy().hasHeightForWidth());
        ed3->setSizePolicy(sizePolicy3);
        ed3->setMinimumSize(QSize(80, 25));
        ed3->setMaximumSize(QSize(80, 25));
        ed3->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed3->setReadOnly(true);

        horizontalLayout_9->addWidget(ed3);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        ed4 = new QLineEdit(tab);
        ed4->setObjectName(QStringLiteral("ed4"));
        sizePolicy3.setHeightForWidth(ed4->sizePolicy().hasHeightForWidth());
        ed4->setSizePolicy(sizePolicy3);
        ed4->setMinimumSize(QSize(80, 25));
        ed4->setMaximumSize(QSize(80, 25));
        ed4->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed4->setReadOnly(true);

        horizontalLayout_6->addWidget(ed4);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout_16->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_11->addWidget(label_6);

        ed5 = new QLineEdit(tab);
        ed5->setObjectName(QStringLiteral("ed5"));
        sizePolicy3.setHeightForWidth(ed5->sizePolicy().hasHeightForWidth());
        ed5->setSizePolicy(sizePolicy3);
        ed5->setMinimumSize(QSize(80, 25));
        ed5->setMaximumSize(QSize(80, 25));
        ed5->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed5->setReadOnly(true);

        horizontalLayout_11->addWidget(ed5);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_12->addWidget(label_7);

        ed6 = new QLineEdit(tab);
        ed6->setObjectName(QStringLiteral("ed6"));
        sizePolicy3.setHeightForWidth(ed6->sizePolicy().hasHeightForWidth());
        ed6->setSizePolicy(sizePolicy3);
        ed6->setMinimumSize(QSize(80, 25));
        ed6->setMaximumSize(QSize(80, 25));
        ed6->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed6->setReadOnly(true);

        horizontalLayout_12->addWidget(ed6);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_13->addWidget(label_10);

        ed7 = new QLineEdit(tab);
        ed7->setObjectName(QStringLiteral("ed7"));
        sizePolicy3.setHeightForWidth(ed7->sizePolicy().hasHeightForWidth());
        ed7->setSizePolicy(sizePolicy3);
        ed7->setMinimumSize(QSize(80, 25));
        ed7->setMaximumSize(QSize(80, 25));
        ed7->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed7->setReadOnly(true);

        horizontalLayout_13->addWidget(ed7);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_14->addWidget(label_9);

        ed8 = new QLineEdit(tab);
        ed8->setObjectName(QStringLiteral("ed8"));
        sizePolicy3.setHeightForWidth(ed8->sizePolicy().hasHeightForWidth());
        ed8->setSizePolicy(sizePolicy3);
        ed8->setMinimumSize(QSize(80, 25));
        ed8->setMaximumSize(QSize(80, 25));
        ed8->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed8->setReadOnly(true);

        horizontalLayout_14->addWidget(ed8);


        verticalLayout_5->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_15->addWidget(label_8);

        ed9 = new QLineEdit(tab);
        ed9->setObjectName(QStringLiteral("ed9"));
        sizePolicy3.setHeightForWidth(ed9->sizePolicy().hasHeightForWidth());
        ed9->setSizePolicy(sizePolicy3);
        ed9->setMinimumSize(QSize(80, 25));
        ed9->setMaximumSize(QSize(80, 25));
        ed9->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: #E0E0E0;"));
        ed9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed9->setReadOnly(true);

        horizontalLayout_15->addWidget(ed9);


        verticalLayout_5->addLayout(horizontalLayout_15);


        horizontalLayout_16->addLayout(verticalLayout_5);


        horizontalLayout_17->addLayout(horizontalLayout_16);


        gridLayout->addLayout(horizontalLayout_17, 3, 0, 1, 2);

        chkDigitGrid = new QCheckBox(tab);
        chkDigitGrid->setObjectName(QStringLiteral("chkDigitGrid"));
        chkDigitGrid->setChecked(true);

        gridLayout->addWidget(chkDigitGrid, 4, 0, 1, 1);

        chkAutoTest = new QCheckBox(tab);
        chkAutoTest->setObjectName(QStringLiteral("chkAutoTest"));
        chkAutoTest->setChecked(false);

        gridLayout->addWidget(chkAutoTest, 4, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        listFilter = new QListWidget(tab_2);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        new QListWidgetItem(listFilter);
        listFilter->setObjectName(QStringLiteral("listFilter"));
        listFilter->setMinimumSize(QSize(0, 260));

        verticalLayout_6->addWidget(listFilter);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_22->addWidget(label_12);

        lbAppliedFilter = new QLabel(tab_2);
        lbAppliedFilter->setObjectName(QStringLiteral("lbAppliedFilter"));
        lbAppliedFilter->setMinimumSize(QSize(170, 0));
        lbAppliedFilter->setMaximumSize(QSize(10000, 50));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        lbAppliedFilter->setFont(font1);
        lbAppliedFilter->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightblue;"));
        lbAppliedFilter->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_22->addWidget(lbAppliedFilter);


        verticalLayout_6->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        btnApplyFilter = new QPushButton(tab_2);
        btnApplyFilter->setObjectName(QStringLiteral("btnApplyFilter"));

        horizontalLayout_21->addWidget(btnApplyFilter);

        btnClearFilter = new QPushButton(tab_2);
        btnClearFilter->setObjectName(QStringLiteral("btnClearFilter"));

        horizontalLayout_21->addWidget(btnClearFilter);


        verticalLayout_6->addLayout(horizontalLayout_21);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        gridLayout_3->addLayout(verticalLayout_6, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 1, 1, 1);


        retranslateUi(DatasetViewer);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DatasetViewer);
    } // setupUi

    void retranslateUi(QDialog *DatasetViewer)
    {
        DatasetViewer->setWindowTitle(QApplication::translate("DatasetViewer", "Dialog", 0));
        lbLabel->setText(QString());
        btnFirst->setText(QApplication::translate("DatasetViewer", "|<", 0));
        btnPrev->setText(QApplication::translate("DatasetViewer", "<", 0));
        btnNext->setText(QApplication::translate("DatasetViewer", ">", 0));
        btnLast->setText(QApplication::translate("DatasetViewer", ">|", 0));
        lbLabel_2->setText(QApplication::translate("DatasetViewer", "Dataset Statistics", 0));
        btnUpdateStats->setText(QApplication::translate("DatasetViewer", "Update", 0));
        lbErrors->setText(QApplication::translate("DatasetViewer", "Errors", 0));
        lbAccuracy->setText(QApplication::translate("DatasetViewer", "Accuracy", 0));
        lbMSE->setText(QApplication::translate("DatasetViewer", "MSE", 0));
        lbErrorRate->setText(QApplication::translate("DatasetViewer", "Error Rate", 0));
        lbLabel_3->setText(QApplication::translate("DatasetViewer", "Sample Test", 0));
        btnUpdateTest->setText(QApplication::translate("DatasetViewer", "Update", 0));
        label_11->setText(QApplication::translate("DatasetViewer", "Sample ID :", 0));
        lbResult->setText(QString());
        label->setText(QApplication::translate("DatasetViewer", "0", 0));
        label_2->setText(QApplication::translate("DatasetViewer", "1", 0));
        label_3->setText(QApplication::translate("DatasetViewer", "2", 0));
        label_4->setText(QApplication::translate("DatasetViewer", "3", 0));
        label_5->setText(QApplication::translate("DatasetViewer", "4", 0));
        label_6->setText(QApplication::translate("DatasetViewer", "5", 0));
        label_7->setText(QApplication::translate("DatasetViewer", "6", 0));
        label_10->setText(QApplication::translate("DatasetViewer", "7", 0));
        label_9->setText(QApplication::translate("DatasetViewer", "8", 0));
        label_8->setText(QApplication::translate("DatasetViewer", "9", 0));
        chkDigitGrid->setText(QApplication::translate("DatasetViewer", "Digit Grid", 0));
        chkAutoTest->setText(QApplication::translate("DatasetViewer", "AutoTest", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DatasetViewer", "Testing", 0));

        const bool __sortingEnabled = listFilter->isSortingEnabled();
        listFilter->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listFilter->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("DatasetViewer", "0", 0));
        QListWidgetItem *___qlistwidgetitem1 = listFilter->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("DatasetViewer", "1", 0));
        QListWidgetItem *___qlistwidgetitem2 = listFilter->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("DatasetViewer", "2", 0));
        QListWidgetItem *___qlistwidgetitem3 = listFilter->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("DatasetViewer", "3", 0));
        QListWidgetItem *___qlistwidgetitem4 = listFilter->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("DatasetViewer", "4", 0));
        QListWidgetItem *___qlistwidgetitem5 = listFilter->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("DatasetViewer", "5", 0));
        QListWidgetItem *___qlistwidgetitem6 = listFilter->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("DatasetViewer", "6", 0));
        QListWidgetItem *___qlistwidgetitem7 = listFilter->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("DatasetViewer", "7", 0));
        QListWidgetItem *___qlistwidgetitem8 = listFilter->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("DatasetViewer", "8", 0));
        QListWidgetItem *___qlistwidgetitem9 = listFilter->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("DatasetViewer", "9", 0));
        QListWidgetItem *___qlistwidgetitem10 = listFilter->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("DatasetViewer", "Errors", 0));
        listFilter->setSortingEnabled(__sortingEnabled);

        label_12->setText(QApplication::translate("DatasetViewer", "Active Filter:", 0));
        lbAppliedFilter->setText(QApplication::translate("DatasetViewer", "None", 0));
        btnApplyFilter->setText(QApplication::translate("DatasetViewer", "Apply", 0));
        btnClearFilter->setText(QApplication::translate("DatasetViewer", "Clear", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DatasetViewer", "Filter", 0));
    } // retranslateUi

};

namespace Ui {
    class DatasetViewer: public Ui_DatasetViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASETVIEWER_H
