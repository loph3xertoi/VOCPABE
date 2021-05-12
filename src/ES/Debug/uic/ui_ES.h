/********************************************************************************
** Form generated from reading UI file 'ES.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ES_H
#define UI_ES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ESClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QTextBrowser *textBrowser;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLabel *label_6;

    void setupUi(QWidget *ESClass)
    {
        if (ESClass->objectName().isEmpty())
            ESClass->setObjectName(QString::fromUtf8("ESClass"));
        ESClass->resize(586, 488);
        verticalLayout_4 = new QVBoxLayout(ESClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ESClass);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_5 = new QLabel(ESClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        horizontalLayout->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ESClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        label_4 = new QLabel(ESClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        horizontalLayout_2->addWidget(label_4);

        horizontalLayout_2->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(ESClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        textBrowser = new QTextBrowser(ESClass);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_7 = new QLabel(ESClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        verticalLayout_2->addWidget(label_7);

        textBrowser_2 = new QTextBrowser(ESClass);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        verticalLayout_2->addWidget(textBrowser_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox = new QCheckBox(ESClass);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_3->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(ESClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_3);

        label_6 = new QLabel(ESClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_3->addWidget(label_6);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(ESClass);

        QMetaObject::connectSlotsByName(ESClass);
    } // setupUi

    void retranslateUi(QWidget *ESClass)
    {
        ESClass->setWindowTitle(QCoreApplication::translate("ESClass", "ES", nullptr));
        label->setText(QCoreApplication::translate("ESClass", "\345\212\240\345\257\206\346\226\271:", nullptr));
        label_5->setText(QString());
        label_2->setText(QCoreApplication::translate("ESClass", "G1\347\224\237\346\210\220\345\205\203g:", nullptr));
        label_4->setText(QString());
        label_3->setText(QCoreApplication::translate("ESClass", "\344\273\216\345\212\240\345\257\206\346\226\271\346\224\266\345\210\260\347\232\204\350\256\241\347\256\227CiDi\347\232\204\345\217\202\346\225\260:", nullptr));
        label_7->setText(QCoreApplication::translate("ESClass", "\350\256\241\347\256\227\345\256\214\346\210\220\347\232\204\347\273\223\346\236\234:", nullptr));
        checkBox->setText(QCoreApplication::translate("ESClass", "\346\250\241\346\213\237\350\256\241\347\256\227\345\207\272\351\224\231", nullptr));
        pushButton->setText(QCoreApplication::translate("ESClass", "\346\224\271\345\217\230\350\256\241\347\256\227\347\273\223\346\236\234", nullptr));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ESClass: public Ui_ESClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ES_H
