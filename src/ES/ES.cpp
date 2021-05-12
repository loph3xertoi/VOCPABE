#include "ES.h"

ES::ES(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.pushButton->setDisabled(true);//���øı��������ť������
    
    pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//Ϊpairingָ������
    showServerIpPort();
    connect(Server.tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//EDClient���ͼ���CiD��i����ʱִ��readData����������ܵ�������

}

ES::~ES()
{
}

void ES::showServerIpPort()
{
    ui.label_6->setText(tr("The server is running on %1: %2").arg(Server.ipAddress.toString()).arg(QString::number(Server.tcpServer->serverPort())));
}

void ES::on_pushButton_clicked()
{
    bool ok;
    QString retQstrA = QInputDialog::getMultiLineText(this, "�ı������", "�ı䷵�ظ��ͻ��˵Ĺ���CiDi�ļ�����:", retQstr, &ok);
    if (ok && !retQstrA.isEmpty())
    {
        Server.writeData(retQstrA);
        //QMessageBox::information(this, "���ͳɹ�", "�ɹ������������͸����ܷ�!");
    }
}

void ES::detectConnect()
{
    //QMessageBox::information(this, "daw", "encryption!");

    Server.serverSocket = Server.tcpServer->nextPendingConnection();
    if (!Server.serverSocket)
        QMessageBox::critical(this, tr("����ͨ��"), tr("δ��ȷ��ȡ�ͻ������ӣ�"));

    connect(Server.serverSocket, &QIODevice::readyRead, this, &ES::computeCiDi);//�����ݵ���������ݲ���������
//connect(serverSocket, &QAbstractSocket::errorOccurred, this, &ServerSetup::displayError);//�����ӡ
//connect(Server.serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnect()));//����˶Ͽ�����

}

void ES::computeCiDi()
{
    retQstr.clear();//ÿ�μ����µ�ֵʱ���
    
    QString CiDiParamQstr = Server.readData();
    //qDebug() << "CiDiParamQstr = " << CiDiParamQstr;

    QStringList powerParam = CiDiParamQstr.split("|");
    //qDebug() << powerParam;
    
    ui.label_5->setText(powerParam.last());//��ʾ����������
    powerParam.removeLast();//ȥ����������
    //qDebug() << powerParam;

    element_t g;
    element_init_G1(g, pairing);
    element_set_str(g, powerParam.last().toStdString().c_str(), 10);
    ui.label_4->setText(powerParam.last());//��ʾ����Ԫg
    powerParam.removeLast();//ȥ��g
    //qDebug() << powerParam;
    ui.textBrowser->clear();
    ui.textBrowser_2->clear();
    for (QStringList::iterator iter = powerParam.begin(); iter != powerParam.end(); iter++)//������CiDi�Ĳ���w1��d2��ʾ��textBrowser
    {
        QStringList subParamList = (*iter).split(";");
        int indexA = std::distance(powerParam.begin(), iter);
        //int indexB = std::distance(subParamList.begin(), iter);

        //[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2]
        ui.textBrowser->append(QString("<font color=\"#008000\"><b>����C%1��һ������Ҫ�Ĳ���:</b></font>").arg(QString::number(indexA + 1)));

        ui.textBrowser->append("w1:");
        ui.textBrowser->append(subParamList.at(0));
        ui.textBrowser->append("<b>c1:</b>");
        ui.textBrowser->append(subParamList.at(1));
        ui.textBrowser->append("<b>u_x1:</b>");
        ui.textBrowser->append(subParamList.at(2));
        ui.textBrowser->append("<b>A_c1_B:</b>");
        ui.textBrowser->append(subParamList.at(3));
        ui.textBrowser->append("<b>d1:</b>");
        ui.textBrowser->append(subParamList.at(4));
        ui.textBrowser->append("<b>w2:</b>");
        ui.textBrowser->append(subParamList.at(5));
        ui.textBrowser->append("<b>c2:</b>");
        ui.textBrowser->append(subParamList.at(6));
        ui.textBrowser->append("<b>u_x2:</b>");
        ui.textBrowser->append(subParamList.at(7));
        ui.textBrowser->append("<b>C_c2_D:</b>");
        ui.textBrowser->append(subParamList.at(8));
        ui.textBrowser->append("<b>d2:</b>");
        ui.textBrowser->append(subParamList.at(9));

        ui.textBrowser->append(QString("<font color=\"#008000\"><b>����C%1�ڶ�������Ҫ�Ĳ���:</b></font>").arg(QString::number(indexA + 1)));

        ui.textBrowser->append("<b>w1:</b>");
        ui.textBrowser->append(subParamList.at(10));
        ui.textBrowser->append("<b>c1:</b>");
        ui.textBrowser->append(subParamList.at(11));
        ui.textBrowser->append("<b>u_x1:</b>");
        ui.textBrowser->append(subParamList.at(12));
        ui.textBrowser->append("<b>A_c1_B:</b>");
        ui.textBrowser->append(subParamList.at(13));
        ui.textBrowser->append("<b>d1:</b>");
        ui.textBrowser->append(subParamList.at(14));
        ui.textBrowser->append("<b>w2:</b>");
        ui.textBrowser->append(subParamList.at(15));
        ui.textBrowser->append("<b>c2:</b>");
        ui.textBrowser->append(subParamList.at(16));
        ui.textBrowser->append("<b>u_x2:</b>");
        ui.textBrowser->append(subParamList.at(17));
        ui.textBrowser->append("<b>C_c2_D:</b>");
        ui.textBrowser->append(subParamList.at(18));
        ui.textBrowser->append("<b>d2:</b>");
        ui.textBrowser->append(subParamList.at(19));

        ui.textBrowser->append(QString("<font color=\"#008000\"><b>����D%1��Ҫ�Ĳ���:</b></font>").arg(QString::number(indexA + 1)));

        ui.textBrowser->append("<b>w1:</b>");
        ui.textBrowser->append(subParamList.at(20));
        ui.textBrowser->append("<b>c1:</b>");
        ui.textBrowser->append(subParamList.at(21));
        ui.textBrowser->append("<b>u_x1:</b>");
        ui.textBrowser->append(subParamList.at(22));
        ui.textBrowser->append("<b>A_c1_B:</b>");
        ui.textBrowser->append(subParamList.at(23));
        ui.textBrowser->append("<b>d1:</b>");
        ui.textBrowser->append(subParamList.at(24));
        ui.textBrowser->append("<b>w2:</b>");
        ui.textBrowser->append(subParamList.at(25));
        ui.textBrowser->append("<b>c2:</b>");
        ui.textBrowser->append(subParamList.at(26));
        ui.textBrowser->append("<b>u_x2:</b>");
        ui.textBrowser->append(subParamList.at(27));
        ui.textBrowser->append("<b>C_c2_D:</b>");
        ui.textBrowser->append(subParamList.at(28));
        ui.textBrowser->append("<b>d2:</b>");
        ui.textBrowser->append(subParamList.at(29));

    }


    element_t c1, w1, d1, u_x1, c2, w2, d2, u_x2, A_Index, B_Index;
    element_init_Zr(c1, pairing);
    element_init_Zr(c2, pairing);
    element_init_Zr(d1, pairing);
    element_init_Zr(d2, pairing);
    element_init_Zr(A_Index, pairing);//A*c1-B
    element_init_Zr(B_Index, pairing);//C*c2-D
    element_init_G1(w1, pairing);
    element_init_G1(w2, pairing);
    element_init_G1(u_x1, pairing);
    element_init_G1(u_x2, pairing);
    element_t powerTemp;//�洢ָ������Ľ��
    element_init_G1(powerTemp, pairing);

    QStringList completedResult;//������ɷ��ؼ��ܷ����б�[w1_c1;u_x1_d1;w2_c2;u_x2_d2;g_A_Index;g_B_Index|...|...]
    for (QStringList::iterator iter = powerParam.begin(); iter != powerParam.end(); iter++)
    {
        QStringList subPower = (*iter).split(";");//3��[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2]��ʽ���ַ���

        for (int i = 0; i < 3; i++)
        {
            if (i == 0)//Ci��һ���ֹ�6��������
                ui.textBrowser_2->append("<font color = \"#008000\"><b>" + QString("C%1��һ���ּ�����:").arg(QString::number(std::distance(powerParam.begin(), iter) + 1)) + "</b></font>");
            else if(i == 1)//Ci�ڶ�����
                ui.textBrowser_2->append("<font color = \"#008000\"><b>" + QString("C%1�ڶ����ּ�����:").arg(QString::number(std::distance(powerParam.begin(), iter) + 1)) + "</b></font>");
            else//Di
                ui.textBrowser_2->append("<font color = \"#008000\"><b>" + QString("D%1������:").arg(QString::number(std::distance(powerParam.begin(), iter) + 1)) + "</b></font>");

            completedResult.clear();
            element_set_str(w1, subPower.at(0 + 10 * i).toStdString().c_str(), 10);
            element_set_str(c1, subPower.at(1 + 10 * i).toStdString().c_str(), 10);
            element_set_str(u_x1, subPower.at(2 + 10 * i).toStdString().c_str(), 10);
            element_set_str(A_Index, subPower.at(3 + 10 * i).toStdString().c_str(), 10);
            element_set_str(d1, subPower.at(4 + 10 * i).toStdString().c_str(), 10);
            element_set_str(w2, subPower.at(5 + 10 * i).toStdString().c_str(), 10);
            element_set_str(c2, subPower.at(6 + 10 * i).toStdString().c_str(), 10);
            element_set_str(u_x2, subPower.at(7 + 10 * i).toStdString().c_str(), 10);
            element_set_str(B_Index, subPower.at(8 + 10 * i).toStdString().c_str(), 10);
            element_set_str(d2, subPower.at(9 + 10 * i).toStdString().c_str(), 10);

            element_pow_zn(powerTemp, w1, c1);
            ui.textBrowser_2->append("<b>w1^c1:</b>");
            ui.textBrowser_2->append(elementToQString(powerTemp));
            completedResult.append(elementToQString(powerTemp));

            element_pow_zn(powerTemp, u_x1, d1);
            ui.textBrowser_2->append("<b>u^(d1*x1):</b>");
            ui.textBrowser_2->append(elementToQString(powerTemp));
            completedResult.append(elementToQString(powerTemp));

            element_pow_zn(powerTemp, w2, c2);
            ui.textBrowser_2->append("<b>w2^c2:</b>");
            ui.textBrowser_2->append(elementToQString(powerTemp));
            completedResult.append(elementToQString(powerTemp));

            element_pow_zn(powerTemp, u_x2, d2);
            ui.textBrowser_2->append("<b>u^(d2*x2):</b>");
            ui.textBrowser_2->append(elementToQString(powerTemp));
            completedResult.append(elementToQString(powerTemp));

            element_pow_zn(powerTemp, g, A_Index);
            ui.textBrowser_2->append("<b>g^(A*c1-B):</b>");
            ui.textBrowser_2->append(elementToQString(powerTemp));
            completedResult.append(elementToQString(powerTemp));

            element_pow_zn(powerTemp, g, B_Index);
            ui.textBrowser_2->append("<b>g^(C*c2-D):</b>");
            ui.textBrowser_2->append(elementToQString(powerTemp));
            completedResult.append(elementToQString(powerTemp));

            retQstr += completedResult.join(";");
            if(iter != powerParam.end() - 1 || i != 2)
                retQstr += "|";
        }
    }
    
    if (ui.checkBox->isChecked())//���ѡ����ʾ�������
        ui.pushButton->setDisabled(false);
    else
        Server.writeData(retQstr);

    element_clear(g);
    element_clear(c1);
    element_clear(w1);
    element_clear(d1);
    element_clear(u_x1);
    element_clear(c2);
    element_clear(w2);
    element_clear(d2);
    element_clear(u_x2);
    element_clear(A_Index);
    element_clear(B_Index);
    element_clear(powerTemp);
}

QString ES::elementToQString(element_t point)
{
    char* ourQStr = (char*)calloc(350, 1);//��ʼ��
    element_snprint(ourQStr, 350, point);//��pointתΪchar*����ourQStr
    return QString(ourQStr);
}
