/********************************************************************************
** Form generated from reading UI file 'EDClient.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDCLIENT_H
#define UI_EDCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EDClientClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_browse;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QPlainTextEdit *plainTextEdit_2;
    QFrame *line;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_submitE;
    QTextBrowser *textBrowser_show;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_17;
    QSplitter *splitter_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_11;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_down;
    QSplitter *splitter_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_16;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_12;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser_3;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *label_name;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *label_passwd;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLabel *label_S;
    QSplitter *splitter;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_9;
    QTextBrowser *textBrowser_PK;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_5;
    QTextBrowser *textBrowser_SK;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_6;
    QTextBrowser *textBrowser_cookie;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_10;
    QTextBrowser *textBrowser_blind;

    void setupUi(QWidget *EDClientClass)
    {
        if (EDClientClass->objectName().isEmpty())
            EDClientClass->setObjectName(QString::fromUtf8("EDClientClass"));
        EDClientClass->setEnabled(true);
        EDClientClass->resize(710, 623);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EDClientClass->sizePolicy().hasHeightForWidth());
        EDClientClass->setSizePolicy(sizePolicy);
        EDClientClass->setMinimumSize(QSize(0, 0));
        EDClientClass->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(EDClientClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(EDClientClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy1);
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(18);
        label_4->setFont(font);

        horizontalLayout->addWidget(label_4);

        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);

        pushButton_browse = new QPushButton(tab);
        pushButton_browse->setObjectName(QString::fromUtf8("pushButton_browse"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_browse->sizePolicy().hasHeightForWidth());
        pushButton_browse->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(pushButton_browse);


        verticalLayout_3->addLayout(horizontalLayout);

        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy4);
        textBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_3->addWidget(textBrowser);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        horizontalLayout_2->addWidget(label_8);

        plainTextEdit_2 = new QPlainTextEdit(tab);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        horizontalLayout_2->addWidget(plainTextEdit_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy5);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        verticalLayout_4->setStretch(0, 5);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout_5->addWidget(label_2);

        plainTextEdit = new QPlainTextEdit(tab);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_5->addWidget(plainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_submitE = new QPushButton(tab);
        pushButton_submitE->setObjectName(QString::fromUtf8("pushButton_submitE"));
        sizePolicy3.setHeightForWidth(pushButton_submitE->sizePolicy().hasHeightForWidth());
        pushButton_submitE->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(pushButton_submitE);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_6->addLayout(verticalLayout_5);

        textBrowser_show = new QTextBrowser(tab);
        textBrowser_show->setObjectName(QString::fromUtf8("textBrowser_show"));
        sizePolicy.setHeightForWidth(textBrowser_show->sizePolicy().hasHeightForWidth());
        textBrowser_show->setSizePolicy(sizePolicy);
        textBrowser_show->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_6->addWidget(textBrowser_show);

        verticalLayout_6->setStretch(0, 5);
        verticalLayout_6->setStretch(1, 1);
        verticalLayout_6->setStretch(2, 7);

        verticalLayout_7->addLayout(verticalLayout_6);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setContextMenuPolicy(Qt::DefaultContextMenu);
        verticalLayout_17 = new QVBoxLayout(tab_2);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setSizeConstraint(QLayout::SetNoConstraint);
        splitter_3 = new QSplitter(tab_2);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(splitter_3->sizePolicy().hasHeightForWidth());
        splitter_3->setSizePolicy(sizePolicy6);
        splitter_3->setOrientation(Qt::Vertical);
        splitter_3->setOpaqueResize(true);
        splitter_3->setChildrenCollapsible(true);
        layoutWidget = new QWidget(splitter_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_14 = new QVBoxLayout(layoutWidget);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font1;
        font1.setPointSize(14);
        label_11->setFont(font1);

        verticalLayout_13->addWidget(label_11);

        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->horizontalHeader()->setDefaultSectionSize(160);

        verticalLayout_13->addWidget(tableWidget);


        verticalLayout_14->addLayout(verticalLayout_13);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_8->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        pushButton_down = new QPushButton(layoutWidget);
        pushButton_down->setObjectName(QString::fromUtf8("pushButton_down"));

        horizontalLayout_8->addWidget(pushButton_down);


        verticalLayout_14->addLayout(horizontalLayout_8);

        splitter_3->addWidget(layoutWidget);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_16 = new QVBoxLayout(layoutWidget1);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        verticalLayout_15->addWidget(label_12);

        textBrowser_2 = new QTextBrowser(layoutWidget1);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setFrameShadow(QFrame::Sunken);
        textBrowser_2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_15->addWidget(textBrowser_2);


        verticalLayout_16->addLayout(verticalLayout_15);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_9->addWidget(pushButton_2);


        verticalLayout_16->addLayout(horizontalLayout_9);

        splitter_2->addWidget(layoutWidget1);
        textBrowser_3 = new QTextBrowser(splitter_2);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        textBrowser_3->setTabStopDistance(80.000000000000000);
        splitter_2->addWidget(textBrowser_3);
        splitter_3->addWidget(splitter_2);

        verticalLayout_17->addWidget(splitter_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        sizePolicy1.setHeightForWidth(tab_3->sizePolicy().hasHeightForWidth());
        tab_3->setSizePolicy(sizePolicy1);
        horizontalLayout_7 = new QHBoxLayout(tab_3);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(tab_3);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy7);
        label->setFont(font1);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        label_name = new QLabel(tab_3);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_name->sizePolicy().hasHeightForWidth());
        label_name->setSizePolicy(sizePolicy8);
        label_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_name);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy7.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy7);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_3);

        label_passwd = new QLabel(tab_3);
        label_passwd->setObjectName(QString::fromUtf8("label_passwd"));
        sizePolicy8.setHeightForWidth(label_passwd->sizePolicy().hasHeightForWidth());
        label_passwd->setSizePolicy(sizePolicy8);

        horizontalLayout_5->addWidget(label_passwd);

        horizontalLayout_5->setStretch(1, 4);

        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy7.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy7);
        label_7->setFont(font1);

        horizontalLayout_6->addWidget(label_7);

        label_S = new QLabel(tab_3);
        label_S->setObjectName(QString::fromUtf8("label_S"));
        sizePolicy8.setHeightForWidth(label_S->sizePolicy().hasHeightForWidth());
        label_S->setSizePolicy(sizePolicy8);

        horizontalLayout_6->addWidget(label_S);

        horizontalLayout_6->setStretch(1, 4);

        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_12->addLayout(verticalLayout_2);

        splitter = new QSplitter(tab_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setLineWidth(1);
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(0);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        verticalLayout_8 = new QVBoxLayout(layoutWidget2);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy7.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy7);
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_8->addWidget(label_9);

        textBrowser_PK = new QTextBrowser(layoutWidget2);
        textBrowser_PK->setObjectName(QString::fromUtf8("textBrowser_PK"));
        textBrowser_PK->setEnabled(true);
        sizePolicy5.setHeightForWidth(textBrowser_PK->sizePolicy().hasHeightForWidth());
        textBrowser_PK->setSizePolicy(sizePolicy5);
        textBrowser_PK->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_8->addWidget(textBrowser_PK);

        splitter->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(splitter);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        verticalLayout_9 = new QVBoxLayout(layoutWidget3);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy7.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy7);
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_9->addWidget(label_5);

        textBrowser_SK = new QTextBrowser(layoutWidget3);
        textBrowser_SK->setObjectName(QString::fromUtf8("textBrowser_SK"));
        sizePolicy5.setHeightForWidth(textBrowser_SK->sizePolicy().hasHeightForWidth());
        textBrowser_SK->setSizePolicy(sizePolicy5);
        textBrowser_SK->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_9->addWidget(textBrowser_SK);

        splitter->addWidget(layoutWidget3);
        layoutWidget4 = new QWidget(splitter);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        verticalLayout_10 = new QVBoxLayout(layoutWidget4);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy7.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy7);
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_10->addWidget(label_6);

        textBrowser_cookie = new QTextBrowser(layoutWidget4);
        textBrowser_cookie->setObjectName(QString::fromUtf8("textBrowser_cookie"));
        sizePolicy5.setHeightForWidth(textBrowser_cookie->sizePolicy().hasHeightForWidth());
        textBrowser_cookie->setSizePolicy(sizePolicy5);
        textBrowser_cookie->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_10->addWidget(textBrowser_cookie);

        splitter->addWidget(layoutWidget4);
        layoutWidget5 = new QWidget(splitter);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        verticalLayout_11 = new QVBoxLayout(layoutWidget5);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy7.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy7);
        label_10->setFont(font1);

        verticalLayout_11->addWidget(label_10);

        textBrowser_blind = new QTextBrowser(layoutWidget5);
        textBrowser_blind->setObjectName(QString::fromUtf8("textBrowser_blind"));
        sizePolicy4.setHeightForWidth(textBrowser_blind->sizePolicy().hasHeightForWidth());
        textBrowser_blind->setSizePolicy(sizePolicy4);
        textBrowser_blind->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_11->addWidget(textBrowser_blind);

        splitter->addWidget(layoutWidget5);

        verticalLayout_12->addWidget(splitter);


        horizontalLayout_7->addLayout(verticalLayout_12);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(EDClientClass);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(EDClientClass);
    } // setupUi

    void retranslateUi(QWidget *EDClientClass)
    {
        EDClientClass->setWindowTitle(QCoreApplication::translate("EDClientClass", "EDClient", nullptr));
        label_4->setText(QCoreApplication::translate("EDClientClass", "\351\234\200\350\246\201\345\212\240\345\257\206\347\232\204\346\226\207\344\273\266(txt):", nullptr));
        pushButton_browse->setText(QCoreApplication::translate("EDClientClass", "\346\265\217\350\247\210", nullptr));
        label_8->setText(QCoreApplication::translate("EDClientClass", "\350\257\267\350\276\223\345\205\245\346\226\207\344\273\266\346\217\217\350\277\260:", nullptr));
        label_2->setText(QCoreApplication::translate("EDClientClass", "\350\257\267\350\276\223\345\205\245\350\256\277\351\227\256\347\255\226\347\225\245(\",\"\344\273\243\350\241\250\344\270\216    \";\"\344\273\243\350\241\250\346\210\226):", nullptr));
        pushButton_submitE->setText(QCoreApplication::translate("EDClientClass", "\347\241\256\345\256\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EDClientClass", "\345\212\240\345\257\206", nullptr));
        label_11->setText(QCoreApplication::translate("EDClientClass", "SS\347\253\257\345\255\230\345\202\250\347\232\204\346\266\210\346\201\257:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EDClientClass", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EDClientClass", "\344\270\212\344\274\240\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EDClientClass", "\346\226\207\344\273\266\346\217\217\350\277\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EDClientClass", "MUID", nullptr));
        pushButton->setText(QCoreApplication::translate("EDClientClass", "\346\233\264\346\226\260\346\266\210\346\201\257\347\233\256\345\275\225", nullptr));
        pushButton_down->setText(QCoreApplication::translate("EDClientClass", "\344\270\213\350\275\275", nullptr));
        label_12->setText(QCoreApplication::translate("EDClientClass", "\346\202\250\350\246\201\350\247\243\345\257\206\347\232\204\346\226\207\344\273\266:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EDClientClass", "\347\241\256\345\256\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EDClientClass", "\350\247\243\345\257\206", nullptr));
        label->setText(QCoreApplication::translate("EDClientClass", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_name->setText(QString());
        label_3->setText(QCoreApplication::translate("EDClientClass", "\345\257\206\347\240\201:", nullptr));
        label_passwd->setText(QString());
        label_7->setText(QCoreApplication::translate("EDClientClass", "\347\224\250\346\210\267\345\261\236\346\200\247\351\233\206(S):", nullptr));
        label_S->setText(QString());
        label_9->setText(QCoreApplication::translate("EDClientClass", "\347\263\273\347\273\237\345\217\202\346\225\260PK:[g,e(g,g)^alpha,g^a,hx]", nullptr));
        label_5->setText(QCoreApplication::translate("EDClientClass", "\347\247\201\351\222\245SK[z,K,L,Kx]:", nullptr));
        label_6->setText(QCoreApplication::translate("EDClientClass", "cookie:", nullptr));
        label_10->setText(QCoreApplication::translate("EDClientClass", "4\344\270\252\351\232\217\346\234\272\347\233\262\345\214\226\345\257\271:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("EDClientClass", "\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EDClientClass: public Ui_EDClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDCLIENT_H
