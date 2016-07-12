#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTimer>

class FileTransfer;

class Chat : public QObject
{
    Q_OBJECT

public:
    explicit Chat(QObject *parent = 0);
    ~Chat();

    void sendWavFiles(const QString &fileName);
    void sendMessage(const QString &message);

    void connectToHost();
    bool getConnected() const;

signals:
    void signalChat(quint8 type, QString message);

public slots:

private slots:
    void sltReciveMessage(); // 接受信息
    void sltIMConnected();
    void sltDisConneceted();
    void sltSocketError(QAbstractSocket::SocketError error);
    void sltTimerOut();
private:
    QUdpSocket *UdpSender;
    QUdpSocket *udpSocket;
    QTcpSocket *tcpImSocket;
    QTcpSocket *tcpFileSocket;

    // 文件传输scoket
    FileTransfer *filetransfer;

    bool m_bConnected;
    // 用户信息
    QString m_strName;
    quint32 m_nId;
    QString m_strPwd;

    // 发送登录信息
    void sendLogin();
    // 发送下线通知
    void sendOffline();
};

#endif // CHAT_H
