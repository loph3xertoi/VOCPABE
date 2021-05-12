#include "DS.h"

DS::DS(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    showServerIpPort();
    ui.pushButton->setDisabled(true);

    connect(Server.tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//�յ�������(���ܷ�)����detectConnect()����
    pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//Ϊpairingָ������

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
    char* ourQStr = (char*)calloc(350, 1);//��ʼ��
    element_snprint(ourQStr, 350, point);//��pointתΪchar*����ourQStr
    return QString(ourQStr);
}

QString DS::preDecry(QString& decryRawQstr)//[K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name|firstPos]
{
    ui.textBrowser->setText("<font color = \"green\">�ӽ��ܷ��յ���ԭʼ��Ϣ:</font>");
    ui.textBrowser->append(decryRawQstr);

    QStringList subList = decryRawQstr.split("|");

    ui.textBrowser->append("<b>���ܷ�ת��˽Կ:</b>");
    ui.textBrowser->append(subList.at(0));

    ui.textBrowser->append("<b>ԭʼ���ĵ�ת������:</b>");
    ui.textBrowser->append(subList.at(1));

    ui.textBrowser->append("<b>subTAPM����:</b>");
    ui.textBrowser->append(subList.at(2));

    ui.label_3->setText(subList.at(3));//���ý��ܷ�����

    QStringList& userSKList = subList.at(0).split(";");//���ܷ�ת����Կ
    QStringList& cipherList = subList.at(1).split(";");//ת������

    QString subTAPM = subList.at(2);//subTAPM����
    int firstPos = subList.at(4).toInt();//firstPosλ��

    int attrNum = userSKList.size() - 2;//��������

    ui.textBrowser_2->setText("<font color = \"green\">���ڽ���...</font>");
    ui.textBrowser_2->append("<font color = \"green\">���ڸ���subTAPM����omegaϵ��...</font>");
    ui.textBrowser_2->repaint();

    QStringList omega = computeOmega(subTAPM);//����subTAPM������Ӧ��omegaϵ������omega�б�
    ui.textBrowser_2->append("<b>omegaϵ��Ϊ:</b>");
    for (QStringList::iterator iter = omega.begin(); iter != omega.end(); iter++)
        ui.textBrowser_2->append(*iter);

    QString ret = actualComp(attrNum, cipherList, userSKList, omega, firstPos);//�������ս������ʾ

    ui.textBrowser_2->append("<font color = \"green\">���ռ�����Ϊ:</font>");
    ui.textBrowser_2->append(ret);

    return ret;
}

void DS::detectConnect()
{
    Server.serverSocket = Server.tcpServer->nextPendingConnection();
    if (!Server.serverSocket)
        QMessageBox::critical(this, tr("����ͨ��"), tr("δ��ȷ��ȡ�ͻ������ӣ�"));

    Server.serverSocket->waitForReadyRead();

    QString decryRawQstr = Server.readData();

    QString deRet = preDecry(decryRawQstr);//���յ����ַ������д�������Ӧ���ܣ��õ����ܺ���ַ���(GT�е�Ԫ��)

    retQstr = deRet;

    if (ui.checkBox->isChecked())//���ѡ����ʾ�������
        ui.pushButton->setDisabled(false);
    else
        Server.writeData(retQstr);

}

void DS::on_pushButton_clicked()
{
    bool ok;
    QString retQstrA = QInputDialog::getMultiLineText(this, "�ı������", "�ı䷵�ظ��ͻ��˵Ĺ���CT[e(g,g)^(s*alpha/z)]�ļ�����:", retQstr, &ok);
    if (ok && !retQstrA.isEmpty())
    {
        Server.writeData(retQstrA);
        //QMessageBox::information(this, "���ͳɹ�", "�ɹ������������͸����ܷ�!");
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
        QStringList metaItemList = (*iterRow).split(" ");//ÿ�е�Ԫ������б�
        if (iterRow == rowList.begin())//��һ��ѭ��ָ��destMatrix�Ĵ�С��Ϊ������ڴ�
        {
            int colNum = (int)metaItemList.size();
            destMatrix.resize(rowNum, colNum);//ָ����С
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
    element_t C_1, K, mole;//moleΪ���ս��ܵķ��Ӳ��ּ�mole = e(C_1, K)
    element_init_G1(C_1, pairing);
    element_init_G1(K, pairing);
    element_init_GT(mole, pairing);

    element_set_str(C_1, cipherList.at(0).toStdString().c_str(), 10);
    element_set_str(K, userSKList.at(0).toStdString().c_str(), 10);

    ui.textBrowser_2->append("<font color = \"green\">���ڼ�����Ӳ���[e(C_1,K)]...</font>");
    ui.textBrowser_2->repaint();
    pairing_apply(mole, C_1, K, pairing);
    ui.textBrowser_2->append("<b>���Ӳ���:</b>");
    ui.textBrowser_2->append(elementToQString(mole));

    ui.textBrowser_2->append("<font color = \"green\">���ڼ����ĸ����...</font>");
    ui.textBrowser_2->append(QString("<b>���ν��ܷ�ĸ����%1������˵õ�</b>").arg(QString::number(attrNum)));
    ui.textBrowser_2->repaint();

    element_t base, index;//base��Ӧe(Ci,L)*e(Di,Kx[i]),index��Ӧomega[i]
    element_init_GT(base, pairing);
    element_init_Zr(index, pairing);

    element_t firstBase, secondBase;//�ֱ��Ӧe(Ci,L)��e(Di,Kx[i])
    element_init_GT(firstBase, pairing);
    element_init_GT(secondBase, pairing);

    element_t Ci, L, Di, Kxi;//Kxi�����i��Kx
    element_init_G1(Ci, pairing);
    element_init_G1(Di, pairing);
    element_init_G1(L, pairing);
    element_init_G1(Kxi, pairing);
    element_set_str(L, userSKList.at(1).toStdString().c_str(), 10);

    element_t subDeno;//��ĸ���
    element_init_GT(subDeno, pairing);

    element_t deno;//��ĸ�����˵õ����շ�ĸdeno
    element_init_GT(deno, pairing);
    element_set1(deno);//��Ϊ��λԪ
    for (int i = 0; i < attrNum; i++)//���μ���ÿ����ĸ���
    {
        element_set_si(index, omega.at(i).toInt());//��ԭomega
        element_set_str(Ci, cipherList.at(2 * (i + firstPos) + 1).toStdString().c_str(), 10);//��ԭCi
        pairing_apply(firstBase, Ci, L, pairing);//����firstBase

        element_set_str(Di, cipherList.at(2 * (i + firstPos) + 2).toStdString().c_str(), 10);//��ԭDi
        element_set_str(Kxi, userSKList.at(i + 2).toStdString().c_str(), 10);//��ԭKxi
        pairing_apply(secondBase, Di, Kxi, pairing);//����secondBase

        element_mul(base, firstBase, secondBase);//�������base

        element_pow_zn(subDeno, base, index);//�����ĸ���
        ui.textBrowser_2->append(QString("<b>��%1����ĸ:</b>").arg(QString::number(i + 1)));
        ui.textBrowser_2->append(elementToQString(subDeno));
        ui.textBrowser_2->repaint();
        element_mul(deno, deno, subDeno);

    }
    ui.textBrowser_2->append("<b>��ĸ����:</b>");
    ui.textBrowser_2->append(elementToQString(deno));

    element_t result;//������ռ�����
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