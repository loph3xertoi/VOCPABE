#include "EDClient.h"
#include "LoginForm.h"
#include "ClientSetup.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    QApplication a(argc, argv);
    //QMessageBox::information(nullptr, "warn", "click ok to connect to KDS server");

    EDClient w;//������
    LoginForm loginForm;//��¼��
    ClientSetup clientSetup("192.168.43.169", "65534");//����KDS������65534��������ͨ��
    if (!clientSetup.isConnected)//����޷�����KDS���������˳�����
        return -1;
    clientSetup.clientSocket->close();
    loginForm.show();//��ʾ��¼��
    QObject::connect(&loginForm, SIGNAL(showMain()), &w, SLOT(recvLogin()));//��¼�ɹ�����ʾ������
    QObject::connect(&loginForm, &LoginForm::showLogged, &w, &EDClient::showLoggedUserInfo);//��¼�ɹ�����������ʾ�û���Ϣ
    QObject::connect(&loginForm, &LoginForm::SSMsgCatalogSignal, &w, &EDClient::showSSMsgCatalog);//��¼�ɹ�����������ʾ�û���Ϣ
    //w.show();

    //_CrtDumpMemoryLeaks();
    return a.exec();
}
