#include "filetransfer.h"
#include "global.h"

#include <QDataStream>
#include <QDebug>

FileTransfer::FileTransfer(QObject *parent) :
    QObject(parent)
{
    // 将整个大的文件分成很多小的部分进行发送，每部分为4字节
    loadSize = 4 * 1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    m_nAudioType = 0;

    m_bConnected = false;
    localFile = new QFile(this);

    this->tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(connected()), this, SLOT(sltConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(sltDisConneceted()));
    // 当有数据接收成功时，我们更新进度条
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(updateServerProgress()));
    // 当有数据发送成功时，我们更新进度条
    connect(tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(updateClientProgress(qint64)));
}

FileTransfer::~FileTransfer()
{
}

void FileTransfer::displayError(QAbstractSocket::SocketError)
{
    qDebug() << "tcp socket" << tcpSocket->errorString();
    tcpSocket->close();
}

// 发送文件
void FileTransfer::startTransferFile(const QString &fileName)
{
    // 如果没有连接上，直接返回
    if (!m_bConnected) return;

    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
        myDebug("sned file: open file error!");
        return;
    }

    totalBytes = localFile->size(); // 文件总大小

    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_8);

    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    // 依次写入总大小信息空间，文件名大小信息空间，文件名
    sendOut << quint32(0) << qint64(0) << qint64(0) << currentFileName;

    // 这里的总大小是文件名大小等信息和实际文件大小的总和
    totalBytes += outBlock.size();

    // 返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut.device()->seek(0);
    sendOut << quint32(MyApp::m_nUserId) << totalBytes << qint64((outBlock.size() - sizeof(qint64)*2 - sizeof(quint32)));

    // 发送完头数据后剩余数据的大小
    bytesToWrite = totalBytes - tcpSocket->write(outBlock);

    outBlock.resize(0);
}

void FileTransfer::connectToHost()
{
    tcpSocket->connectToHost(MyApp::m_strMsgServer, MyApp::m_nTcpFilePort);
}

void FileTransfer::sltConnected()
{
    m_bConnected = true;
    myDebug("file socket has connected");
    // 上报自己的id
    sendConnected();
}

void FileTransfer::sltDisConneceted()
{
    m_bConnected = false;
    tcpSocket->abort();
}

void FileTransfer::updateClientProgress(qint64 numBytes)
{
    //已经发送数据的大小
    bytesWritten += (int)numBytes;
    if(bytesToWrite > 0) //如果已经发送了数据
    {
        //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，就发送剩余数据的大小
        outBlock = localFile->read(qMin(bytesToWrite, loadSize));

        //发送完一次数据后还剩余数据的大小
        bytesToWrite -= (int)tcpSocket->write(outBlock);

        //清空发送缓冲区
        outBlock.resize(0);
    }
    else
    {
        //如果没有发送任何数据，则关闭文件
        localFile->close();
    }

    if(bytesWritten >= totalBytes) // 发送完毕
    {
        localFile->close();
        bytesWritten = 0;  // clear fot next send
        totalBytes = 0;
        bytesToWrite = 0;
    }
}

// 更新进度条，实现文件的接收
void FileTransfer::updateServerProgress()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);

    //如果接收到的数据小于等于16个字节，那么是刚开始接收数据，我们保存为头文件信息
    if(bytesReceived <= sizeof(qint64)*2)
    {
        //接收数据总大小信息和文件名大小信息
        if((tcpSocket->bytesAvailable() >= (qint64)sizeof(qint64)*2) && (fileNameSize == 0))
        {
            in >> m_nAudioType >> totalBytes >> fileNameSize;
            bytesReceived += ((sizeof(qint64) * 2) + sizeof(quint8));
            myDebug("wav file recv type" << m_nAudioType);
        }

        //接收文件名，并建立文件
        if((tcpSocket->bytesAvailable() >= (qint64)fileNameSize) && ((qint64)fileNameSize != 0))
        {
            in >> fileName;
            fileName = MyApp::m_strRecordPath + fileName;
            bytesReceived += fileNameSize;

            localFile->setFileName(fileName);

            if(!localFile->open(QFile::WriteOnly | QIODevice::Truncate))
            {
                qDebug() << "writing file error!";
                return;
            }
            myDebug("begin to write to file:" << fileName);
        }
        else
            return;

    }

    //如果接收的数据小于总数据，那么写入文件
    if(bytesReceived < totalBytes)
    {
        bytesReceived += tcpSocket->bytesAvailable();
        inBlock = tcpSocket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    // 接收数据完成时
    if(bytesReceived >= totalBytes)
    {
        localFile->close();
        bytesReceived = 0; // clear for next receive
        totalBytes = 0;
        fileNameSize = 0;
        myDebug("finished to recv file:" << m_nAudioType << fileName);

        // 只有当纯语音的时候才发送
        if (SPEEK == m_nAudioType)
            Q_EMIT signalNewAudio(m_nAudioType, fileName);
    }
}

// 发送链接信息
void FileTransfer::sendConnected()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);

    // send login success
    out << MyApp::m_nUserId << qint64(0) << qint64(0);                      // id编号

    tcpSocket->write(block);
}
