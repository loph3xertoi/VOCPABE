/********************************************************************************
** Form generated from reading UI file 'LoginForm.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginFormClass
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSplitter *splitter;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *LoginFormClass)
    {
        if (LoginFormClass->objectName().isEmpty())
            LoginFormClass->setObjectName(QString::fromUtf8("LoginFormClass"));
        LoginFormClass->setEnabled(true);
        LoginFormClass->resize(324, 393);
        LoginFormClass->setMinimumSize(QSize(324, 393));
        LoginFormClass->setMaximumSize(QSize(324, 393));
        lineEdit = new QLineEdit(LoginFormClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 60, 151, 31));
        lineEdit_2 = new QLineEdit(LoginFormClass);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 110, 151, 31));
        pushButton_2 = new QPushButton(LoginFormClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(191, 190, 91, 31));
        QFont font;
        font.setPointSize(14);
        pushButton_2->setFont(font);
        pushButton = new QPushButton(LoginFormClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 190, 91, 31));
        pushButton->setFont(font);
        splitter = new QSplitter(LoginFormClass);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(40, 60, 72, 81));
        splitter->setOrientation(Qt::Vertical);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(false);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        splitter->addWidget(label);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font2;
        font2.setPointSize(18);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);
        splitter->addWidget(label_2);

        retranslateUi(LoginFormClass);

        QMetaObject::connectSlotsByName(LoginFormClass);
    } // setupUi

    void retranslateUi(QWidget *LoginFormClass)
    {
        LoginFormClass->setWindowTitle(QCoreApplication::translate("EDClientClass", "EDClient", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EDClientClass", "\347\231\273\345\275\225", nullptr));
        pushButton->setText(QCoreApplication::translate("EDClientClass", "\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("EDClientClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("EDClientClass", "\345\257\206  \347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginFormClass: public Ui_LoginFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
