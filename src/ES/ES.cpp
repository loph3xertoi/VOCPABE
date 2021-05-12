#include "ES.h"

ES::ES(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.pushButton->setDisabled(true);//设置改变计算结果按钮不可用
    
    pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//为pairing指定类型
    showServerIpPort();
    connect(Server.tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//EDClient发送计算CiD的i参数时执行readData函数处理接受到的数据

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
    QString retQstrA = QInputDialog::getMultiLineText(this, "改变计算结果", "改变返回给客户端的关于CiDi的计算结果:", retQstr, &ok);
    if (ok && !retQstrA.isEmpty())
    {
        Server.writeData(retQstrA);
        //QMessageBox::information(this, "发送成功", "成功将计算结果发送给加密方!");
    }
}

void ES::detectConnect()
{
    //QMessageBox::information(this, "daw", "encryption!");

    Server.serverSocket = Server.tcpServer->nextPendingConnection();
    if (!Server.serverSocket)
        QMessageBox::critical(this, tr("网络通信"), tr("未正确获取客户端连接！"));

    connect(Server.serverSocket, &QIODevice::readyRead, this, &ES::computeCiDi);//有数据到达则读数据并处理数据
//connect(serverSocket, &QAbstractSocket::errorOccurred, this, &ServerSetup::displayError);//错误打印
//connect(Server.serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnect()));//服务端断开连接

}

void ES::computeCiDi()
{
    retQstr.clear();//每次计算新的值时清空
    
    QString CiDiParamQstr = Server.readData();
    //qDebug() << "CiDiParamQstr = " << CiDiParamQstr;

    QStringList powerParam = CiDiParamQstr.split("|");
    //qDebug() << powerParam;
    
    ui.label_5->setText(powerParam.last());//显示加密者名字
    powerParam.removeLast();//去掉最后的名字
    //qDebug() << powerParam;

    element_t g;
    element_init_G1(g, pairing);
    element_set_str(g, powerParam.last().toStdString().c_str(), 10);
    ui.label_4->setText(powerParam.last());//显示生成元g
    powerParam.removeLast();//去掉g
    //qDebug() << powerParam;
    ui.textBrowser->clear();
    ui.textBrowser_2->clear();
    for (QStringList::iterator iter = powerParam.begin(); iter != powerParam.end(); iter++)//将计算CiDi的参数w1到d2显示在textBrowser
    {
        QStringList subParamList = (*iter).split(";");
        int indexA = std::distance(powerParam.begin(), iter);
        //int indexB = std::distance(subParamList.begin(), iter);

        //[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2]
        ui.textBrowser->append(QString("<font color=\"#008000\"><b>计算C%1第一部分需要的参数:</b></font>").arg(QString::number(indexA + 1)));

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

        ui.textBrowser->append(QString("<font color=\"#008000\"><b>计算C%1第二部分需要的参数:</b></font>").arg(QString::number(indexA + 1)));

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

        ui.textBrowser->append(QString("<font color=\"#008000\"><b>计算D%1需要的参数:</b></font>").arg(QString::number(indexA + 1)));

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
    element_t powerTemp;//存储指数运算的结果
    element_init_G1(powerTemp, pairing);

    QStringList completedResult;//计算完成返回加密方的列表[w1_c1;u_x1_d1;w2_c2;u_x2_d2;g_A_Index;g_B_Index|...|...]
    for (QStringList::iterator iter = powerParam.begin(); iter != powerParam.end(); iter++)
    {
        QStringList subPower = (*iter).split(";");//3个[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2]格式的字符串

        for (int i = 0; i < 3; i++)
        {
            if (i == 0)//Ci第一部分共6个计算结果
                ui.textBrowser_2->append("<font color = \"#008000\"><b>" + QString("C%1第一部分计算结果:").arg(QString::number(std::distance(powerParam.begin(), iter) + 1)) + "</b></font>");
            else if(i == 1)//Ci第二部分
                ui.textBrowser_2->append("<font color = \"#008000\"><b>" + QString("C%1第二部分计算结果:").arg(QString::number(std::distance(powerParam.begin(), iter) + 1)) + "</b></font>");
            else//Di
                ui.textBrowser_2->append("<font color = \"#008000\"><b>" + QString("D%1计算结果:").arg(QString::number(std::distance(powerParam.begin(), iter) + 1)) + "</b></font>");

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
    
    if (ui.checkBox->isChecked())//如果选择演示计算出错
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
    char* ourQStr = (char*)calloc(350, 1);//初始化
    element_snprint(ourQStr, 350, point);//将point转为char*存入ourQStr
    return QString(ourQStr);
}
