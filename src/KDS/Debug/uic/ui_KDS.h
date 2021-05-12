/********************************************************************************
** Form generated from reading UI file 'KDS.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KDS_H
#define UI_KDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KDSClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTableView *tableView_2;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QTableView *tableView_3;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_5;
    QTableView *tableView_4;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QTableView *tableView_5;
    QLabel *label_7;

    void setupUi(QWidget *KDSClass)
    {
        if (KDSClass->objectName().isEmpty())
            KDSClass->setObjectName(QString::fromUtf8("KDSClass"));
        KDSClass->resize(733, 555);
        verticalLayout_4 = new QVBoxLayout(KDSClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(KDSClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setPointSize(11);
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(18);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        plainTextEdit = new QPlainTextEdit(tab);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy1);
        plainTextEdit->setBackgroundVisible(false);
        plainTextEdit->setCenterOnScroll(false);

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(138, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2);

        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(tableView);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        verticalLayout_3->addWidget(label_3);

        tableView_2 = new QTableView(tab);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(tableView_2->sizePolicy().hasHeightForWidth());
        tableView_2->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(tableView_2);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_5->setStretch(0, 2);
        verticalLayout_5->setStretch(1, 3);
        verticalLayout_5->setStretch(2, 4);

        verticalLayout_6->addLayout(verticalLayout_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_8 = new QVBoxLayout(tab_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        verticalLayout_7->addWidget(label_4);

        tableView_3 = new QTableView(tab_2);
        tableView_3->setObjectName(QString::fromUtf8("tableView_3"));
        sizePolicy1.setHeightForWidth(tableView_3->sizePolicy().hasHeightForWidth());
        tableView_3->setSizePolicy(sizePolicy1);

        verticalLayout_7->addWidget(tableView_3);


        verticalLayout_8->addLayout(verticalLayout_7);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_10 = new QVBoxLayout(tab_3);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout_9->addWidget(label_5);

        tableView_4 = new QTableView(tab_3);
        tableView_4->setObjectName(QString::fromUtf8("tableView_4"));
        sizePolicy1.setHeightForWidth(tableView_4->sizePolicy().hasHeightForWidth());
        tableView_4->setSizePolicy(sizePolicy1);

        verticalLayout_9->addWidget(tableView_4);


        verticalLayout_10->addLayout(verticalLayout_9);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_12 = new QVBoxLayout(tab_4);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        verticalLayout_11->addWidget(label_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(tab_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_11->addLayout(horizontalLayout_2);

        tableView_5 = new QTableView(tab_4);
        tableView_5->setObjectName(QString::fromUtf8("tableView_5"));
        sizePolicy1.setHeightForWidth(tableView_5->sizePolicy().hasHeightForWidth());
        tableView_5->setSizePolicy(sizePolicy1);
        tableView_5->setDragEnabled(false);
        tableView_5->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableView_5->setShowGrid(true);
        tableView_5->setGridStyle(Qt::CustomDashLine);
        tableView_5->setSortingEnabled(false);

        verticalLayout_11->addWidget(tableView_5);


        verticalLayout_12->addLayout(verticalLayout_11);

        tabWidget->addTab(tab_4, QString());

        verticalLayout_4->addWidget(tabWidget);

        label_7 = new QLabel(KDSClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_4->addWidget(label_7);


        retranslateUi(KDSClass);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(KDSClass);
    } // setupUi

    void retranslateUi(QWidget *KDSClass)
    {
        KDSClass->setWindowTitle(QCoreApplication::translate("KDSClass", "KDS", nullptr));
        label->setText(QCoreApplication::translate("KDSClass", "\350\257\267\350\276\223\345\205\245\347\263\273\347\273\237\345\261\236\346\200\247\345\205\250\351\233\206U(\351\200\227\345\217\267\351\232\224\345\274\200):", nullptr));
        pushButton->setText(QCoreApplication::translate("KDSClass", "\347\241\256\350\256\244", nullptr));
        label_2->setText(QCoreApplication::translate("KDSClass", "\347\263\273\347\273\237\345\217\202\346\225\260(RawParam):", nullptr));
        label_3->setText(QCoreApplication::translate("KDSClass", "\350\256\277\351\227\256\347\255\226\347\225\245\347\237\251\351\230\265\350\241\250(AccessPolicyMatrix):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("KDSClass", "\345\210\235\345\247\213\345\214\226\347\263\273\347\273\237", nullptr));
        label_4->setText(QCoreApplication::translate("KDSClass", "\347\263\273\347\273\237\344\270\255\345\267\262\347\273\217\346\263\250\345\206\214\347\232\204\347\224\250\346\210\267(User):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("KDSClass", "\345\267\262\346\263\250\345\206\214\347\224\250\346\210\267", nullptr));
        label_5->setText(QCoreApplication::translate("KDSClass", "\347\263\273\347\273\237\344\270\255\345\267\262\347\273\217\347\231\273\345\275\225\347\232\204\347\224\250\346\210\267(LoggedUser):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("KDSClass", "\345\267\262\347\231\273\345\275\225\347\224\250\346\210\267", nullptr));
        label_8->setText(QCoreApplication::translate("KDSClass", "\345\234\250\347\254\246\345\220\210\346\235\241\344\273\266\347\232\204\347\224\250\346\210\267\346\211\200\345\234\250\350\241\214\345\217\214\345\207\273\357\274\214\345\234\250\345\274\271\345\207\272\347\232\204\350\276\223\345\205\245\346\241\206\344\270\255\344\270\272\350\257\245\347\224\250\346\210\267\346\214\207\345\256\232\347\224\250\346\210\267\345\261\236\346\200\247\351\233\206S\357\274\201", nullptr));
        label_6->setText(QCoreApplication::translate("KDSClass", "\346\226\260\346\263\250\345\206\214\347\232\204\347\224\250\346\210\267(NewUser):", nullptr));
        pushButton_2->setText(QCoreApplication::translate("KDSClass", "\345\210\240\351\231\244\346\211\200\351\200\211\347\224\250\346\210\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("KDSClass", "\346\226\260\346\263\250\345\206\214\347\224\250\346\210\267", nullptr));
        label_7->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class KDSClass: public Ui_KDSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KDS_H
