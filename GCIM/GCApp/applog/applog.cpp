#include "applog.h"
#include "myapp.h"
#include "unit.h"
#include "date.h"

#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDateTime>
#include <QDate>
#include <QDebug>

QFile *logFile = new QFile;
QString logFileName;

// 文件管理：只保留最近10天日志
void logFileManager(int last) {
    QString strOldDate = Date::getBeforDays(last);
    QString fileName = MyApp::m_strLogPath + MyApp::m_strAppName;
    fileName.append("_Log_");
    fileName.append(strOldDate);
    fileName.append(".txt");

    // 删除旧文件
    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }
}

//输出所有打印调试信息到日志文件
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
void Log(QtMsgType type, const char *msg)
{
    QString content;

    switch (type) {
    case QtDebugMsg:
        content = QString("%1").arg(msg);
        break;

    case QtWarningMsg:
        content = QString("%1").arg(msg);
        break;

    case QtCriticalMsg:
        content = QString("%1").arg(msg);
        break;

    case QtFatalMsg:
        content = QString("%1").arg(msg);
        break;
    }

    if (content.startsWith("libpng")) {
        return;
    }

    //方法改进:之前每次输出日志都打开文件,改成只有当日期改变时才新建和打开文件
    QString fileName = QString("%1/%2_Log_%3.txt")
            .arg(MyApp::m_strLogPath)
            .arg(MyApp::m_strAppName)
            .arg(QDATE);

    if (fileName != logFileName) {
        // 日志文件管理
        logFileManager(10);
        // 创建新的日志文件
        logFileName = fileName;

        if (logFile->isOpen()) {
            logFile->close();
        }

        logFile->setFileName(logFileName);
        logFile->open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    }

    QTextStream logStream(logFile);
    logStream << "[" << DATETIME_FRM1 << "]" << content << endl;
}
#else
void Log(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    QString content;

    switch (type) {
    case QtDebugMsg:
        content = QString("%1").arg(msg);
        break;

    case QtWarningMsg:
        content = QString("%1").arg(msg);
        break;

    case QtCriticalMsg:
        content = QString("%1").arg(msg);
        break;

    case QtFatalMsg:
        content = QString("%1").arg(msg);
        break;
    default:
        content = QString("%1").arg(msg);
        break;
    }

    if (content.startsWith("libpng")) {
        return;
    }

    //方法改进:之前每次输出日志都打开文件,改成只有当日期改变时才新建和打开文件
    QString fileName = QString("%1/%2_Log_%3.txt")
            .arg(MyApp::m_strLogPath)
            .arg(MyApp::m_strAppName)
            .arg(QDATE);

    if (fileName != logFileName) {
        // 日志文件管理
        logFileManager(10);
        // 创建新的日志文件
        logFileName = fileName;

        if (logFile->isOpen()) {
            logFile->close();
        }

        logFile->setFileName(logFileName);
        logFile->open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    }

    QTextStream logStream(logFile);
    logStream << "[" << DATETIME_FRM1 << "]" << content << endl;
}
#endif

AppLog *AppLog::self = 0;
AppLog::AppLog(QObject *parent) : QObject(parent)
{
}

// 安装日志钩子,输出调试信息到文件,便于调试
void AppLog::Start()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    qInstallMsgHandler(Log);
#else
    qInstallMessageHandler(Log);
#endif
}

// 卸载日志钩子
void AppLog::Stop()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    qInstallMsgHandler(0);
#else
    qInstallMessageHandler(0);
#endif
}

