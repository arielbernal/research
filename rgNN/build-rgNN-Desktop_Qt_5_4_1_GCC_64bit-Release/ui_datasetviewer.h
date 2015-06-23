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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "oglTools/simpleglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DatasetViewer
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout;
    QLabel *lbLabel;
    SimpleGLWidget *glDigit;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QLineEdit *edIndex;
    QLineEdit *edSamples;
    QFrame *line;
    QLineEdit *edSampleId;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QVBoxLayout *verticalLayout_7;
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
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_18;
    QLabel *lbLabel_3;
    QPushButton *btnUpdateTest;
    QCheckBox *chkAutoTest;
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

    void setupUi(QDialog *DatasetViewer)
    {
        if (DatasetViewer->objectName().isEmpty())
            DatasetViewer->setObjectName(QStringLiteral("DatasetViewer"));
        DatasetViewer->resize(693, 490);
        gridLayout = new QGridLayout(DatasetViewer);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbLabel = new QLabel(DatasetViewer);
        lbLabel->setObjectName(QStringLiteral("lbLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbLabel->sizePolicy().hasHeightForWidth());
        lbLabel->setSizePolicy(sizePolicy);
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
        sizePolicy.setHeightForWidth(glDigit->sizePolicy().hasHeightForWidth());
        glDigit->setSizePolicy(sizePolicy);
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

        edIndex = new QLineEdit(DatasetViewer);
        edIndex->setObjectName(QStringLiteral("edIndex"));
        edIndex->setMinimumSize(QSize(60, 0));
        edIndex->setMaximumSize(QSize(60, 16777215));
        edIndex->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edIndex->setReadOnly(false);

        horizontalLayout_19->addWidget(edIndex);

        edSamples = new QLineEdit(DatasetViewer);
        edSamples->setObjectName(QStringLiteral("edSamples"));
        edSamples->setMinimumSize(QSize(60, 0));
        edSamples->setMaximumSize(QSize(60, 16777215));
        edSamples->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edSamples->setReadOnly(true);

        horizontalLayout_19->addWidget(edSamples);

        line = new QFrame(DatasetViewer);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(line);

        edSampleId = new QLineEdit(DatasetViewer);
        edSampleId->setObjectName(QStringLiteral("edSampleId"));
        edSampleId->setMinimumSize(QSize(60, 0));
        edSampleId->setMaximumSize(QSize(60, 16777215));
        edSampleId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edSampleId->setReadOnly(true);

        horizontalLayout_19->addWidget(edSampleId);

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


        gridLayout->addLayout(verticalLayout_8, 0, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lbLabel_2 = new QLabel(DatasetViewer);
        lbLabel_2->setObjectName(QStringLiteral("lbLabel_2"));
        lbLabel_2->setMaximumSize(QSize(10000, 50));
        lbLabel_2->setFont(font);
        lbLabel_2->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightblue;"));
        lbLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(lbLabel_2);

        btnUpdateStats = new QPushButton(DatasetViewer);
        btnUpdateStats->setObjectName(QStringLiteral("btnUpdateStats"));
        sizePolicy.setHeightForWidth(btnUpdateStats->sizePolicy().hasHeightForWidth());
        btnUpdateStats->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(btnUpdateStats);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lbErrors = new QLabel(DatasetViewer);
        lbErrors->setObjectName(QStringLiteral("lbErrors"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbErrors->sizePolicy().hasHeightForWidth());
        lbErrors->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(lbErrors);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        edErrors = new QLineEdit(DatasetViewer);
        edErrors->setObjectName(QStringLiteral("edErrors"));
        sizePolicy.setHeightForWidth(edErrors->sizePolicy().hasHeightForWidth());
        edErrors->setSizePolicy(sizePolicy);
        edErrors->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edErrors->setReadOnly(true);

        horizontalLayout_4->addWidget(edErrors);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbAccuracy = new QLabel(DatasetViewer);
        lbAccuracy->setObjectName(QStringLiteral("lbAccuracy"));
        sizePolicy1.setHeightForWidth(lbAccuracy->sizePolicy().hasHeightForWidth());
        lbAccuracy->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lbAccuracy);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        edAccuracy = new QLineEdit(DatasetViewer);
        edAccuracy->setObjectName(QStringLiteral("edAccuracy"));
        sizePolicy.setHeightForWidth(edAccuracy->sizePolicy().hasHeightForWidth());
        edAccuracy->setSizePolicy(sizePolicy);
        edAccuracy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edAccuracy->setReadOnly(true);

        horizontalLayout_3->addWidget(edAccuracy);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbMSE = new QLabel(DatasetViewer);
        lbMSE->setObjectName(QStringLiteral("lbMSE"));
        sizePolicy1.setHeightForWidth(lbMSE->sizePolicy().hasHeightForWidth());
        lbMSE->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lbMSE);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        edMSE = new QLineEdit(DatasetViewer);
        edMSE->setObjectName(QStringLiteral("edMSE"));
        sizePolicy.setHeightForWidth(edMSE->sizePolicy().hasHeightForWidth());
        edMSE->setSizePolicy(sizePolicy);
        edMSE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edMSE->setReadOnly(true);

        horizontalLayout_2->addWidget(edMSE);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lbErrorRate = new QLabel(DatasetViewer);
        lbErrorRate->setObjectName(QStringLiteral("lbErrorRate"));
        sizePolicy1.setHeightForWidth(lbErrorRate->sizePolicy().hasHeightForWidth());
        lbErrorRate->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lbErrorRate);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        edErrorRate = new QLineEdit(DatasetViewer);
        edErrorRate->setObjectName(QStringLiteral("edErrorRate"));
        sizePolicy.setHeightForWidth(edErrorRate->sizePolicy().hasHeightForWidth());
        edErrorRate->setSizePolicy(sizePolicy);
        edErrorRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edErrorRate->setReadOnly(true);

        horizontalLayout->addWidget(edErrorRate);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        lbLabel_3 = new QLabel(DatasetViewer);
        lbLabel_3->setObjectName(QStringLiteral("lbLabel_3"));
        lbLabel_3->setMaximumSize(QSize(10000, 50));
        lbLabel_3->setFont(font);
        lbLabel_3->setStyleSheet(QLatin1String("border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
" background-color: lightblue;"));
        lbLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(lbLabel_3);

        btnUpdateTest = new QPushButton(DatasetViewer);
        btnUpdateTest->setObjectName(QStringLiteral("btnUpdateTest"));
        sizePolicy.setHeightForWidth(btnUpdateTest->sizePolicy().hasHeightForWidth());
        btnUpdateTest->setSizePolicy(sizePolicy);

        horizontalLayout_18->addWidget(btnUpdateTest);


        verticalLayout_6->addLayout(horizontalLayout_18);

        chkAutoTest = new QCheckBox(DatasetViewer);
        chkAutoTest->setObjectName(QStringLiteral("chkAutoTest"));
        chkAutoTest->setChecked(true);

        verticalLayout_6->addWidget(chkAutoTest);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        lbResult = new QLabel(DatasetViewer);
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
        label = new QLabel(DatasetViewer);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_7->addWidget(label);

        ed0 = new QLineEdit(DatasetViewer);
        ed0->setObjectName(QStringLiteral("ed0"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ed0->sizePolicy().hasHeightForWidth());
        ed0->setSizePolicy(sizePolicy2);
        ed0->setMinimumSize(QSize(80, 25));
        ed0->setMaximumSize(QSize(80, 25));
        ed0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed0->setReadOnly(true);

        horizontalLayout_7->addWidget(ed0);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(DatasetViewer);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_8->addWidget(label_2);

        ed1 = new QLineEdit(DatasetViewer);
        ed1->setObjectName(QStringLiteral("ed1"));
        sizePolicy2.setHeightForWidth(ed1->sizePolicy().hasHeightForWidth());
        ed1->setSizePolicy(sizePolicy2);
        ed1->setMinimumSize(QSize(80, 25));
        ed1->setMaximumSize(QSize(80, 25));
        ed1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed1->setReadOnly(true);

        horizontalLayout_8->addWidget(ed1);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(DatasetViewer);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_10->addWidget(label_3);

        ed2 = new QLineEdit(DatasetViewer);
        ed2->setObjectName(QStringLiteral("ed2"));
        sizePolicy2.setHeightForWidth(ed2->sizePolicy().hasHeightForWidth());
        ed2->setSizePolicy(sizePolicy2);
        ed2->setMinimumSize(QSize(80, 25));
        ed2->setMaximumSize(QSize(80, 25));
        ed2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed2->setReadOnly(true);

        horizontalLayout_10->addWidget(ed2);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(DatasetViewer);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        ed3 = new QLineEdit(DatasetViewer);
        ed3->setObjectName(QStringLiteral("ed3"));
        sizePolicy2.setHeightForWidth(ed3->sizePolicy().hasHeightForWidth());
        ed3->setSizePolicy(sizePolicy2);
        ed3->setMinimumSize(QSize(80, 25));
        ed3->setMaximumSize(QSize(80, 25));
        ed3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed3->setReadOnly(true);

        horizontalLayout_9->addWidget(ed3);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(DatasetViewer);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        ed4 = new QLineEdit(DatasetViewer);
        ed4->setObjectName(QStringLiteral("ed4"));
        sizePolicy2.setHeightForWidth(ed4->sizePolicy().hasHeightForWidth());
        ed4->setSizePolicy(sizePolicy2);
        ed4->setMinimumSize(QSize(80, 25));
        ed4->setMaximumSize(QSize(80, 25));
        ed4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed4->setReadOnly(true);

        horizontalLayout_6->addWidget(ed4);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout_16->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_6 = new QLabel(DatasetViewer);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_11->addWidget(label_6);

        ed5 = new QLineEdit(DatasetViewer);
        ed5->setObjectName(QStringLiteral("ed5"));
        sizePolicy2.setHeightForWidth(ed5->sizePolicy().hasHeightForWidth());
        ed5->setSizePolicy(sizePolicy2);
        ed5->setMinimumSize(QSize(80, 25));
        ed5->setMaximumSize(QSize(80, 25));
        ed5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed5->setReadOnly(true);

        horizontalLayout_11->addWidget(ed5);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_7 = new QLabel(DatasetViewer);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_12->addWidget(label_7);

        ed6 = new QLineEdit(DatasetViewer);
        ed6->setObjectName(QStringLiteral("ed6"));
        sizePolicy2.setHeightForWidth(ed6->sizePolicy().hasHeightForWidth());
        ed6->setSizePolicy(sizePolicy2);
        ed6->setMinimumSize(QSize(80, 25));
        ed6->setMaximumSize(QSize(80, 25));
        ed6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed6->setReadOnly(true);

        horizontalLayout_12->addWidget(ed6);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_10 = new QLabel(DatasetViewer);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_13->addWidget(label_10);

        ed7 = new QLineEdit(DatasetViewer);
        ed7->setObjectName(QStringLiteral("ed7"));
        sizePolicy2.setHeightForWidth(ed7->sizePolicy().hasHeightForWidth());
        ed7->setSizePolicy(sizePolicy2);
        ed7->setMinimumSize(QSize(80, 25));
        ed7->setMaximumSize(QSize(80, 25));
        ed7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed7->setReadOnly(true);

        horizontalLayout_13->addWidget(ed7);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_9 = new QLabel(DatasetViewer);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_14->addWidget(label_9);

        ed8 = new QLineEdit(DatasetViewer);
        ed8->setObjectName(QStringLiteral("ed8"));
        sizePolicy2.setHeightForWidth(ed8->sizePolicy().hasHeightForWidth());
        ed8->setSizePolicy(sizePolicy2);
        ed8->setMinimumSize(QSize(80, 25));
        ed8->setMaximumSize(QSize(80, 25));
        ed8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed8->setReadOnly(true);

        horizontalLayout_14->addWidget(ed8);


        verticalLayout_5->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_8 = new QLabel(DatasetViewer);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_15->addWidget(label_8);

        ed9 = new QLineEdit(DatasetViewer);
        ed9->setObjectName(QStringLiteral("ed9"));
        sizePolicy2.setHeightForWidth(ed9->sizePolicy().hasHeightForWidth());
        ed9->setSizePolicy(sizePolicy2);
        ed9->setMinimumSize(QSize(80, 25));
        ed9->setMaximumSize(QSize(80, 25));
        ed9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ed9->setReadOnly(true);

        horizontalLayout_15->addWidget(ed9);


        verticalLayout_5->addLayout(horizontalLayout_15);


        horizontalLayout_16->addLayout(verticalLayout_5);


        horizontalLayout_17->addLayout(horizontalLayout_16);


        verticalLayout_6->addLayout(horizontalLayout_17);


        verticalLayout_7->addLayout(verticalLayout_6);


        gridLayout->addLayout(verticalLayout_7, 0, 1, 1, 1);


        retranslateUi(DatasetViewer);

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
        chkAutoTest->setText(QApplication::translate("DatasetViewer", "AutoTest", 0));
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
    } // retranslateUi

};

namespace Ui {
    class DatasetViewer: public Ui_DatasetViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASETVIEWER_H
