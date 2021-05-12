#include "DS.h"

DS::DS(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    showServerIpPort();
    ui.pushButton->setDisabled(true);

    connect(Server.tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//收到新连接(解密方)调用detectConnect()函数
    pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//为pairing指定类型

}

DS::~DS()
{
}

void DS::showServerIpPort()
{
    ui.label_4->setText(tr("The server is running on %1: %2").arg(Server.ipAddress.toString()).arg(QString::number(Server.tcpServer->serverPort())));
}

QString DS::elementToQString(element_t point)
{
    char* ourQStr = (char*)calloc(350, 1);//初始化
    element_snprint(ourQStr, 350, point);//将point转为char*存入ourQStr
    return QString(ourQStr);
}

QString DS::preDecry(QString& decryRawQstr)//[K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name|firstPos]
{
    ui.textBrowser->setText("<font color = \"green\">从解密方收到的原始消息:</font>");
    ui.textBrowser->append(decryRawQstr);

    QStringList subList = decryRawQstr.split("|");

    ui.textBrowser->append("<b>解密方转换私钥:</b>");
    ui.textBrowser->append(subList.at(0));

    ui.textBrowser->append("<b>原始密文的转换密文:</b>");
    ui.textBrowser->append(subList.at(1));

    ui.textBrowser->append("<b>subTAPM矩阵:</b>");
    ui.textBrowser->append(subList.at(2));

    ui.label_3->setText(subList.at(3));//设置解密方名字

    QStringList& userSKList = subList.at(0).split(";");//解密方转换密钥
    QStringList& cipherList = subList.at(1).split(";");//转换密文

    QString subTAPM = subList.at(2);//subTAPM矩阵
    int firstPos = subList.at(4).toInt();//firstPos位置

    int attrNum = userSKList.size() - 2;//属性数量

    ui.textBrowser_2->setText("<font color = \"green\">正在解密...</font>");
    ui.textBrowser_2->append("<font color = \"green\">正在根据subTAPM计算omega系数...</font>");
    ui.textBrowser_2->repaint();

    QStringList omega = computeOmega(subTAPM);//根据subTAPM计算相应的omega系数存入omega列表
    ui.textBrowser_2->append("<b>omega系数为:</b>");
    for (QStringList::iterator iter = omega.begin(); iter != omega.end(); iter++)
        ui.textBrowser_2->append(*iter);

    QString ret = actualComp(attrNum, cipherList, userSKList, omega, firstPos);//计算最终结果并显示

    ui.textBrowser_2->append("<font color = \"green\">最终计算结果为:</font>");
    ui.textBrowser_2->append(ret);

    return ret;
}

void DS::detectConnect()
{
    Server.serverSocket = Server.tcpServer->nextPendingConnection();
    if (!Server.serverSocket)
        QMessageBox::critical(this, tr("网络通信"), tr("未正确获取客户端连接！"));

    Server.serverSocket->waitForReadyRead();

    QString decryRawQstr = Server.readData();

    QString deRet = preDecry(decryRawQstr);//对收到的字符串进行处理并作相应解密，得到解密后的字符串(GT中的元素)

    retQstr = deRet;

    if (ui.checkBox->isChecked())//如果选择演示计算出错
        ui.pushButton->setDisabled(false);
    else
        Server.writeData(retQstr);

}

void DS::on_pushButton_clicked()
{
    bool ok;
    QString retQstrA = QInputDialog::getMultiLineText(this, "改变计算结果", "改变返回给客户端的关于CT[e(g,g)^(s*alpha/z)]的计算结果:", retQstr, &ok);
    if (ok && !retQstrA.isEmpty())
    {
        Server.writeData(retQstrA);
        //QMessageBox::information(this, "发送成功", "成功将计算结果发送给解密方!");
    }
}

void DS::changeResult(QString& retQstr)
{
}

QStringList DS::computeOmega(QString& subTAPM)
{
    QStringList omegaList;
    
    Eigen::MatrixXd subTAPMatrix = toMatrix(subTAPM);
    Eigen::Index row = subTAPMatrix.rows();
    Eigen::Index col = subTAPMatrix.cols();
    Eigen::MatrixXd resultMatrix = Eigen::MatrixXd::Zero(row, 1);
    resultMatrix(0, 0) = 1;
    //std::cout << resultMatrix << std::endl;
    Eigen::MatrixXd solve;
    solve = subTAPMatrix.colPivHouseholderQr().solve(resultMatrix);

    for (int i = 0; i < col; i++)
        omegaList.append(QString::number(solve(i, 0)));

    return omegaList;
}

Eigen::MatrixXd DS::toMatrix(QString matrixQstr)
{
    Eigen::MatrixXd destMatrix;
    QStringList rowList = matrixQstr.split("\n");
    int rowNum = (int)rowList.size();

    for (QStringList::iterator iterRow = rowList.begin(); iterRow != rowList.end(); iterRow++) {
        QStringList metaItemList = (*iterRow).split(" ");//每行的元素组成列表
        if (iterRow == rowList.begin())//第一次循环指定destMatrix的大小，为其分配内存
        {
            int colNum = (int)metaItemList.size();
            destMatrix.resize(rowNum, colNum);//指定大小
        }
        for (QStringList::iterator iterCol = metaItemList.begin(); iterCol != metaItemList.end(); iterCol++)
            destMatrix(std::distance(rowList.begin(), iterRow), std::distance(metaItemList.begin(), iterCol)) = (*iterCol).toInt();
    }
    //std::cout << destMatrix << std::endl;
    return destMatrix;
}

QString DS::MatrixToQString(Eigen::MatrixXd& APM)
{
    std::stringstream ssAPM;
    ssAPM << APM;
    QString APMatrix = QString::fromStdString(ssAPM.str());
    ssAPM.str("");

    return APMatrix;
}

QString DS::actualComp(const int& attrNum, const QStringList& cipherList, const QStringList& userSKList, const QStringList& omega, const int& firstPos)
{
    element_t C_1, K, mole;//mole为最终解密的分子部分即mole = e(C_1, K)
    element_init_G1(C_1, pairing);
    element_init_G1(K, pairing);
    element_init_GT(mole, pairing);

    element_set_str(C_1, cipherList.at(0).toStdString().c_str(), 10);
    element_set_str(K, userSKList.at(0).toStdString().c_str(), 10);

    ui.textBrowser_2->append("<font color = \"green\">正在计算分子部分[e(C_1,K)]...</font>");
    ui.textBrowser_2->repaint();
    pairing_apply(mole, C_1, K, pairing);
    ui.textBrowser_2->append("<b>分子部分:</b>");
    ui.textBrowser_2->append(elementToQString(mole));

    ui.textBrowser_2->append("<font color = \"green\">正在计算分母部分...</font>");
    ui.textBrowser_2->append(QString("<b>本次解密分母共由%1部分相乘得到</b>").arg(QString::number(attrNum)));
    ui.textBrowser_2->repaint();

    element_t base, index;//base对应e(Ci,L)*e(Di,Kx[i]),index对应omega[i]
    element_init_GT(base, pairing);
    element_init_Zr(index, pairing);

    element_t firstBase, secondBase;//分别对应e(Ci,L)和e(Di,Kx[i])
    element_init_GT(firstBase, pairing);
    element_init_GT(secondBase, pairing);

    element_t Ci, L, Di, Kxi;//Kxi代表第i个Kx
    element_init_G1(Ci, pairing);
    element_init_G1(Di, pairing);
    element_init_G1(L, pairing);
    element_init_G1(Kxi, pairing);
    element_set_str(L, userSKList.at(1).toStdString().c_str(), 10);

    element_t subDeno;//分母组分
    element_init_GT(subDeno, pairing);

    element_t deno;//分母组分相乘得到最终分母deno
    element_init_GT(deno, pairing);
    element_set1(deno);//设为单位元
    for (int i = 0; i < attrNum; i++)//依次计算每个分母组成
    {
        element_set_si(index, omega.at(i).toInt());//还原omega
        element_set_str(Ci, cipherList.at(2 * (i + firstPos) + 1).toStdString().c_str(), 10);//还原Ci
        pairing_apply(firstBase, Ci, L, pairing);//计算firstBase

        element_set_str(Di, cipherList.at(2 * (i + firstPos) + 2).toStdString().c_str(), 10);//还原Di
        element_set_str(Kxi, userSKList.at(i + 2).toStdString().c_str(), 10);//还原Kxi
        pairing_apply(secondBase, Di, Kxi, pairing);//计算secondBase

        element_mul(base, firstBase, secondBase);//计算底数base

        element_pow_zn(subDeno, base, index);//计算分母组成
        ui.textBrowser_2->append(QString("<b>第%1个分母:</b>").arg(QString::number(i + 1)));
        ui.textBrowser_2->append(elementToQString(subDeno));
        ui.textBrowser_2->repaint();
        element_mul(deno, deno, subDeno);

    }
    ui.textBrowser_2->append("<b>分母部分:</b>");
    ui.textBrowser_2->append(elementToQString(deno));

    element_t result;//存放最终计算结果
    element_init_GT(result, pairing);
    element_div(result, mole, deno);
    QString deResult = elementToQString(result);


    element_clear(C_1);
    element_clear(K);
    element_clear(mole);
    element_clear(base);
    element_clear(index);
    element_clear(firstBase);
    element_clear(secondBase);
    element_clear(Ci);
    element_clear(L);
    element_clear(Di);
    element_clear(Kxi);
    element_clear(subDeno);
    element_clear(deno);
    element_clear(result);


    return deResult;
}