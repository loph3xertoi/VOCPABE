#include "EDClient.h"
#include "LoginForm.h"
#include "ClientSetup.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    QApplication a(argc, argv);
    //QMessageBox::information(nullptr, "warn", "click ok to connect to KDS server");

    EDClient w;//主界面
    LoginForm loginForm;//登录框
    ClientSetup clientSetup("192.168.43.169", "65534");//连接KDS服务器65534，测试连通性
    if (!clientSetup.isConnected)//如果无法连接KDS服务器则退出程序
        return -1;
    clientSetup.clientSocket->close();
    loginForm.show();//显示登录框
    QObject::connect(&loginForm, SIGNAL(showMain()), &w, SLOT(recvLogin()));//登录成功则显示主界面
    QObject::connect(&loginForm, &LoginForm::showLogged, &w, &EDClient::showLoggedUserInfo);//登录成功在主界面显示用户信息
    QObject::connect(&loginForm, &LoginForm::SSMsgCatalogSignal, &w, &EDClient::showSSMsgCatalog);//登录成功在主界面显示用户信息
    //w.show();

    //_CrtDumpMemoryLeaks();
    return a.exec();
}
