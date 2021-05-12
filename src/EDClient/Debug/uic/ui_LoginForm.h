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
    QLineEdit *lineEdit_user;
    QLineEdit *lineEdit_pwd;
    QPushButton *pushButton_login;
    QPushButton *pushButton_register;
    QSplitter *splitter;
    QLabel *label_user;
    QLabel *label_pwd;
    QLabel *label_prompt;

    void setupUi(QWidget *LoginFormClass)
    {
        if (LoginFormClass->objectName().isEmpty())
            LoginFormClass->setObjectName(QString::fromUtf8("LoginFormClass"));
        LoginFormClass->setEnabled(true);
        LoginFormClass->resize(324, 393);
        LoginFormClass->setMinimumSize(QSize(324, 393));
        LoginFormClass->setMaximumSize(QSize(324, 393));
        lineEdit_user = new QLineEdit(LoginFormClass);
        lineEdit_user->setObjectName(QString::fromUtf8("lineEdit_user"));
        lineEdit_user->setGeometry(QRect(130, 60, 151, 31));
        lineEdit_pwd = new QLineEdit(LoginFormClass);
        lineEdit_pwd->setObjectName(QString::fromUtf8("lineEdit_pwd"));
        lineEdit_pwd->setGeometry(QRect(130, 110, 151, 31));
        pushButton_login = new QPushButton(LoginFormClass);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(191, 190, 91, 31));
        QFont font;
        font.setFamilies(QStringList{QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(14);
        pushButton_login->setFont(font);
        pushButton_register = new QPushButton(LoginFormClass);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(40, 190, 91, 31));
        pushButton_register->setFont(font);
        splitter = new QSplitter(LoginFormClass);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(40, 60, 72, 81));
        splitter->setOrientation(Qt::Vertical);
        label_user = new QLabel(splitter);
        label_user->setObjectName(QString::fromUtf8("label_user"));
        QFont font1;
        font1.setFamilies(QStringList{QString::fromUtf8("\345\256\213\344\275\223")});
        font1.setPointSize(18);
        font1.setBold(false);
        label_user->setFont(font1);
        label_user->setAlignment(Qt::AlignCenter);
        splitter->addWidget(label_user);
        label_pwd = new QLabel(splitter);
        label_pwd->setObjectName(QString::fromUtf8("label_pwd"));
        QFont font2;
        font2.setFamilies(QStringList{QString::fromUtf8("\345\256\213\344\275\223")});
        font2.setPointSize(18);
        label_pwd->setFont(font2);
        label_pwd->setAlignment(Qt::AlignCenter);
        splitter->addWidget(label_pwd);
        label_prompt = new QLabel(LoginFormClass);
        label_prompt->setObjectName(QString::fromUtf8("label_prompt"));
        label_prompt->setGeometry(QRect(40, 140, 241, 31));

        retranslateUi(LoginFormClass);

        QMetaObject::connectSlotsByName(LoginFormClass);
    } // setupUi

    void retranslateUi(QWidget *LoginFormClass)
    {
        LoginFormClass->setWindowTitle(QCoreApplication::translate("LoginFormClass", "EDClient", nullptr));
        pushButton_login->setText(QCoreApplication::translate("LoginFormClass", "\347\231\273\345\275\225", nullptr));
        pushButton_register->setText(QCoreApplication::translate("LoginFormClass", "\346\263\250\345\206\214", nullptr));
        label_user->setText(QCoreApplication::translate("LoginFormClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_pwd->setText(QCoreApplication::translate("LoginFormClass", "\345\257\206  \347\240\201", nullptr));
        label_prompt->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginFormClass: public Ui_LoginFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
