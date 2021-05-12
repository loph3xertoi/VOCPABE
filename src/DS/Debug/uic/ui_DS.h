/********************************************************************************
** Form generated from reading UI file 'DS.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DS_H
#define UI_DS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DSClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLabel *label_4;

    void setupUi(QWidget *DSClass)
    {
        if (DSClass->objectName().isEmpty())
            DSClass->setObjectName(QString::fromUtf8("DSClass"));
        DSClass->resize(798, 591);
        verticalLayout_4 = new QVBoxLayout(DSClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(DSClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(14);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(DSClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalLayout->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout);

        splitter = new QSplitter(DSClass);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        verticalLayout->addWidget(label);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        verticalLayout_2->addWidget(label_5);

        textBrowser_2 = new QTextBrowser(layoutWidget1);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        verticalLayout_2->addWidget(textBrowser_2);

        splitter->addWidget(layoutWidget1);

        verticalLayout_3->addWidget(splitter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox = new QCheckBox(DSClass);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(DSClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        label_4 = new QLabel(DSClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(DSClass);

        QMetaObject::connectSlotsByName(DSClass);
    } // setupUi

    void retranslateUi(QWidget *DSClass)
    {
        DSClass->setWindowTitle(QCoreApplication::translate("DSClass", "DS", nullptr));
        label_2->setText(QCoreApplication::translate("DSClass", "\350\247\243\345\257\206\346\226\271:", nullptr));
        label_3->setText(QString());
        label->setText(QCoreApplication::translate("DSClass", "\344\273\216\350\247\243\345\257\206\346\226\271\346\224\266\345\210\260\347\232\204\344\277\241\346\201\257:", nullptr));
        label_5->setText(QCoreApplication::translate("DSClass", "\350\247\243\345\257\206\350\277\207\347\250\213:", nullptr));
        checkBox->setText(QCoreApplication::translate("DSClass", "\346\250\241\346\213\237\350\256\241\347\256\227\345\207\272\351\224\231", nullptr));
        pushButton->setText(QCoreApplication::translate("DSClass", "\346\224\271\345\217\230\350\256\241\347\256\227\347\273\223\346\236\234", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DSClass: public Ui_DSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DS_H
