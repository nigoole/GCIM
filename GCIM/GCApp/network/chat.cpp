#include "chat.h"
#include "global.h"
#include "unit.h"
#include "filetransfer.h"

#include <QDateTime>
#include <QDataStream>

Chat::Chat(QObject *parent) : QObject(parent)
{
    m_bConnected = false;

    m_strName   = "";
    m_nId       = MyApp::m_nUserId;
    m_strPwd    = MyApp::m_strPwd;

    udpSocket   = new QUdpSocket(this);
    // 聊天socket
    tcpImSocket = new QTcpSocket(this);
    // 文件传输
    filetransfer = new FileTransfer(this);

    // 将UdpReader绑定到广播地址的端口，接收发到这个端口的信息
    udpSocket->bind(6655, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(sltReciveMessage()));
    connect(tcpImSocket, SIGNAL(readyRead()), this, SLOT(sltReciveMessage()));
    connect(tcpImSocket, SIGNAL(connected()), this, SLOT(sltIMConnected()));
    connect(tcpImSocket, SIGNAL(disconnected()), this, SLOT(sltDisConneceted()));
    connect(tcpImSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(sltSocketError(QAbstractSocket::SocketError)));

    connect(filetransfer, SIGNAL(signalNewAudio(quint8,QString)), this,  SIGNAL(signalChat(quint8,QString)));
}

Chat::~Chat() {
    m_bConnected = true;

    // 发送下线通知
    sendOffline();
    udpSocket->abort();
    udpSocket->close();
}

// 发送音频文件
void Chat::sendWavFiles(const QString &fileName)
{
    if (filetransfer->getConnected()) {
        filetransfer->startTransferFile(fileName);
    }
    else {
        filetransfer->connectToHost();
        myDebug(fileName << "send failed & server connect failed!");
    }
}

// 发送消息
void Chat::sendMessage(const QString &message) {
    QHostAddress address(MyApp::m_strMsgServer);
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    out << quint8(0x5a)                 // 包头
        << quint8(1)                    // 协议版本号
        << quint8(MESSAGE)              // 数据类型
        << quint8(1)                    // 语音编码类型1： wav
        << quint32(m_nId)               // id编号
        << quint32(message.length())    // 内容长度
        << message                      // 消息内容或文件内容
        << quint8(0x5b);                // 包尾

    qDebug() << "ip_t = " << message;
    udpSocket->writeDatagram(datagram, address, MyApp::m_nUdpRoomPort);
}

/**
 * @brief Chat::connectToHost
 * 连接服务器
 */
void Chat::connectToHost()
{
    m_bConnected = false;

    tcpImSocket->abort();
    tcpImSocket->close();
    tcpImSocket->connectToHost(MyApp::m_strMsgServer, MyApp::m_nTcpMsgPort);

    if (!filetransfer->getConnected()) {
        filetransfer->connectToHost();
    }
}

// 接收服务器消息
void Chat::sltReciveMessage() {
    quint8 type;
    QDataStream in;
    in.setDevice(tcpImSocket);
    in.setVersion(QDataStream::Qt_4_8);

    if (tcpImSocket->bytesAvailable() < 20) return;
    quint8 nTemp = 0;
    // 读取包头
    in >> nTemp;
    if (0x5a != nTemp) {
        myDebug("not server messag!" << nTemp);
    }
    // 读取版本号
    in >> nTemp;
    if (0x01 != nTemp) {
        myDebug("this protocl is not new!" << nTemp);
    }
    // 读取数据类型
    in  >> type;

    switch (type) {
    case LOGIN: {
        quint32 nlen = 0;
        in >> nTemp >> m_nId >> nlen >> m_strName >> nTemp;
    }
        break;
    case LOGOUT: {

    }
        break;
    case MESSAGE:       // 普通文本消息
    case BROADCAST:     // 服务器广播消息
    {
        quint32 nlen = 0;
        QString message;
        quint32 nId;
        in >> nTemp >> nId >> nlen >> message >> nTemp;
        // 100 是服务中心的号码，如果消息不是服务中心的号码，不予处理
        if ("100" != QString::number(nId)) return;

        Q_EMIT signalChat((E_MessageType)type, message);
    }
        break;
        // 语音消息
    case SPEEK:
    {
        quint32 nlen = 0;
        QString message, fileName;
        quint32 nId;
        in >> nTemp >> nId >> nlen >> message >> fileName >> nTemp;
        // 100 是服务中心的号码，如果消息不是服务中心的号码，不予处理
        if ("100" != QString::number(nId)) return;

        // 服务器请求文件下发，如果没连接，连接，如果连接，上报id
        if (!filetransfer->getConnected()) {
            filetransfer->connectToHost();
        }
    }
        break;
        // 文字语音消息
    case TEXT_AUDIO:
    {
        quint32 nlen = 0;
        QString message, fileName;
        quint32 nId;
        in >> nTemp >> nId >> nlen >> message >> fileName >> nTemp;
        // 100 是服务中心的号码，如果消息不是服务中心的号码，不予处理
        if ("100" != QString::number(nId)) return;

        Q_EMIT signalChat(TEXT_AUDIO, fileName + "&&" + message);
    }
        break;
    default:
        break;
    }
}

/**
 * @brief Chat::sltConnected
 */
void Chat::sltIMConnected()
{
    m_bConnected = true;

    // 发送登录信息
    sendLogin();
    myDebug("has connected to IM Server!" << m_nId);
}

// 断线重连
void Chat::sltDisConneceted()
{
    m_bConnected = false;
    myDebug("disconnected IM Server!");
}

// 网络错误
void Chat::sltSocketError(QAbstractSocket::SocketError error)
{
//    myDebug("chat tcp connecet error: " << error);
    Q_UNUSED(error)
}

// 断线后超时重连
void Chat::sltTimerOut()
{
    connectToHost();
}

void Chat::sendLogin()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    // send login success
    out << quint8(0x5a)                 // 包头
        << quint8(1)                    // 协议版本号
        << quint8(LOGIN)                // 数据类型
        << quint8(1)                    // 语音编码类型1： wav
        << m_nId                        // id编号
        << quint32(MyApp::m_strPwd.length())     // 内容长度
        << MyApp::m_strPwd              // 消息内容或文件内容
        << quint8(0x5b);                // 包尾

    tcpImSocket->write(block);
}

// 发送下线通知
void Chat::sendOffline()
{
    if (!m_bConnected) return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    // send login success
    out << quint8(0x5a)                 // 包头
        << quint8(1)                    // 协议版本号
        << quint8(LOGOUT)                // 数据类型
        << quint8(1)                    // 语音编码类型1： wav
        << MyApp::m_nUserId                      // id编号
        << quint32(MyApp::m_strPwd.length())     // 内容长度
        << MyApp::m_strPwd              // 消息内容或文件内容
        << quint8(0x5b);                // 包尾


    tcpImSocket->write(block);
    myDebug("send offline " << m_nId);
}

/**
 * @brief Chat::getConnected
 * @return
 */
bool Chat::getConnected() const
{
    return m_bConnected && filetransfer->getConnected();
}

