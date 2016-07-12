#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>

class FileTransfer : public QObject
{
    Q_OBJECT
public:
//    explicit FileTransfer(QObject *parent = 0);
    explicit FileTransfer(QObject *parent = 0);
    ~FileTransfer();

    // 发送文件大小等信息
    void startTransferFile(const QString &fileName);
    bool getConnected() {return m_bConnected;}
    void connectToHost();
signals:

    // 新的语音
    void signalNewAudio(quint8 type, QString strFileName);
private:
    /********** Send and receive files though TCP protocol **************/
    QTcpSocket *tcpSocket;    //
    /************* Receive file *******************/
//    qint64 totalBytes;  //存放总大小信息
    quint64 bytesReceived;  //已收到数据的大小
    quint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
//    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区

    /************* Send file **********************/
    quint16 blockSize;  //存放接收到的信息大小
    QFile *localFile;  //要发送的文件
    quint64 totalBytes;  //数据总大小
    quint64 bytesWritten;  //已经发送数据大小
    quint64 bytesToWrite;   //剩余数据大小
    quint64 loadSize;   //每次发送数据的大小
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据

    // 判断是否连接
    bool m_bConnected;
    // 判断是纯语音还是文字语音
    quint8 m_nAudioType;
public slots:

private slots:
    void sltConnected();
    void sltDisConneceted();

    void displayError(QAbstractSocket::SocketError); // 显示错误
    void updateClientProgress(qint64); //发送文件数据，更新进度条
    // 文件接收
    void updateServerProgress();

private:
    void sendConnected();
};

#endif // FILETRANSFER_H
