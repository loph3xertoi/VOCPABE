/********************************************************************************
** Form generated from reading UI file 'SS.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SS_H
#define UI_SS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SSClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QLabel *label_IP;

    void setupUi(QWidget *SSClass)
    {
        if (SSClass->objectName().isEmpty())
            SSClass->setObjectName(QString::fromUtf8("SSClass"));
        SSClass->resize(600, 400);
        verticalLayout_2 = new QVBoxLayout(SSClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(SSClass);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        label_IP = new QLabel(SSClass);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));

        verticalLayout->addWidget(label_IP);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SSClass);

        QMetaObject::connectSlotsByName(SSClass);
    } // setupUi

    void retranslateUi(QWidget *SSClass)
    {
        SSClass->setWindowTitle(QCoreApplication::translate("SSClass", "SS", nullptr));
        label_IP->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SSClass: public Ui_SSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SS_H
