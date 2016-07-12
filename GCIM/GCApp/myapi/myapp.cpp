#include "myapp.h"
#include "unit.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QDebug>

// 应用程序路径
QString MyApp::m_strAppPath     = "./";
// 数据保存路径
QString MyApp::m_strDataPath    = "data";
// 日志保存路径
QString MyApp::m_strLogPath     = "log";
// 测试数据保存路径
QString MyApp::m_strTestPath    = "test";
// 下载目录
QString MyApp::m_strDownloadPath  = "download";
// 截图保存路径
QString MyApp::m_strScreenShotPath  = "screen_shot";
// 音频目录
QString MyApp::m_strWavPath         = "wav_normal";
// 录音目录
QString MyApp::m_strRecordPath      = "record";
// 数据库目录
QString MyApp::m_strDbPath          = "database";
// 配置目录
QString MyApp::m_strConfPath        = "conf";
// 备份目录
QString MyApp::m_strBackupPath      = "backup";

// 配置文件
QString MyApp::m_strIniFile         = "config.ini";

// 硬件版本
QString MyApp::m_strHeadVer         = "2.0.0.0";
// 软件版本
QString MyApp::m_strSoftVer         = MY_VERSION_STR;

// 设备ID
QString MyApp::m_strDevId           = "59909200001";

// 数据上传服务器配置
QString MyApp::m_strDataServerAddr   = "222.180.250.162";
int MyApp::m_nDataServerPort         = 5100;


// 系统升级配置
#ifdef Q_OS_UNIX
QString MyApp::m_strUpServerUrl     = "http://121.40.121.132:9191/apps/linux/vict_app";
#else
QString MyApp::m_strUpServerUrl     = "http://121.40.121.132:9191/apps/win32/vict_app.exe";
#endif
QString MyApp::m_strCheckVersion    = "http://121.40.121.132:9191/vict_version.php";
QString MyApp::m_strAppName         = "vict_app";


// 系统音量
int MyApp::m_nSysVolume             = 127;
int MyApp::m_nRecVolume             = 85;

// SMTP服务器地址
QString MyApp::m_strSmtpAddr        = "220.181.12.12";

#ifdef Q_WS_QWS
bool    MyApp::m_bNetwork           = false;
#else
bool    MyApp::m_bNetwork           = true;
#endif

quint32 MyApp::m_nUserId            = 101;
QString MyApp::m_strPwd             = "123";
QString MyApp::m_strMsgServer       = "183.230.8.172";      // 网络服务器地址
quint16 MyApp::m_nUdpRoomPort       = 60003;                // 服务器聊天室端口
quint16 MyApp::m_nTcpMsgPort        = 60001;                // 网络短信语音端口
quint16 MyApp::m_nTcpFilePort       = 60002;                // 文件服务器端口

// 初始化
void MyApp::init(QApplication &app)
{
    m_strAppPath        = app.applicationDirPath() + "/";
#ifdef Q_OS_UNIX
    if (!m_strAppPath.startsWith("/")) {
        myDebug("m_strAppPath no start with /" << m_strAppPath) ;
        m_strAppPath = "/" + m_strAppPath;
    }
#endif

    m_strDataPath       = m_strAppPath  + "data/";
    m_strLogPath        = m_strDataPath + "log";
    m_strTestPath       = m_strDataPath + "test/";
    m_strDownloadPath   = m_strAppPath  + "download/";
    m_strScreenShotPath = m_strDataPath + "screen_shot/";
    m_strWavPath        = m_strDataPath + "wav_normal/";
    m_strRecordPath     = m_strDataPath + "record/";
    m_strDbPath         = m_strDataPath + "database/";
    m_strBackupPath     = m_strDataPath + "backup/";
    m_strConfPath       = m_strDataPath + "conf/";
    m_strIniFile        = m_strConfPath + "config.ini";

    // 检查目录
    checkDirs();

    // 创建配置文件
    creatorSettingFile();

    // 读取设备编号
    m_strDevId              = getSettingKeyValue("SysConfig", "DeviceId", "59909200001").toString();

    // 数据上传服务器配置
    m_strDataServerAddr      = getSettingKeyValue("DataServer", "IpAddr", "222.180.250.162").toString();
    m_nDataServerPort        = getSettingKeyValue("DataServer", "Port", 5100).toInt();

    // 系统升级配置
    m_strUpServerUrl        = getSettingKeyValue("Version", "AppUrl",
                                                "http://121.40.121.132:9191/apps/vict_app").toString();
    m_strCheckVersion       = getSettingKeyValue("Version", "VerUrl",
                                                 "http://121.40.121.132:9191/vict_version.php").toString();
    m_strAppName            = getSettingKeyValue("Version", "AppName", "vict_app").toString();

    // 音量控制
    m_nSysVolume            = getSettingKeyValue("SysConfig", "SysVolume", 127).toInt();
    m_nRecVolume            = getSettingKeyValue("SysConfig", "RecVolume", 85).toInt();

    // SMTP
    m_strSmtpAddr           = getSettingKeyValue("Server", "SmtpAddr", "220.181.12.12").toString();

    // 读取用户配置
    m_strMsgServer          = getSettingKeyValue("Server", "MsgServer", "183.230.8.172").toString();
    m_nUdpRoomPort          = getSettingKeyValue("Server", "UdpRoom", 43434).toInt();
    m_nTcpMsgPort           = getSettingKeyValue("Server", "MsgProt", 60001).toInt();
    m_nTcpFilePort          = getSettingKeyValue("Server", "FilePort", 60001).toInt();

    m_nUserId               = getSettingKeyValue("MsgUser", "Id", 101).toInt();
    m_strPwd                = getSettingKeyValue("MsgUser", "Passwd", "123").toString();
}

/**
 * @brief MyApp::creatorSettingFile 创建配置文件
 */
void MyApp::creatorSettingFile() {
    // 写入配置文件
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    QString strGroups = settings.childGroups().join("");
    if (!QFile::exists(m_strIniFile) || (strGroups.isEmpty()))
    {
        /*sip通话配置*/
        settings.beginGroup("SipConfig");
        settings.setValue("AutoAnswer", false);
        settings.endGroup();

        /*sip用户设置*/
        settings.beginGroup("SipUser");
        settings.setValue("ServerName", "1000");
        settings.setValue("UserName", "1001");
        settings.setValue("UserPasswd", "1234");
        settings.endGroup();

        /*网络短信用户设置*/
        settings.beginGroup("MsgUser");
        settings.setValue("Id",     m_nUserId);
        settings.setValue("Name",   "Young");
        settings.setValue("Passwd", m_strPwd);
        settings.endGroup();

        /*升级信息*/
        settings.beginGroup("Version");
        settings.setValue("AppUrl", m_strUpServerUrl);
        settings.setValue("VerUrl", m_strCheckVersion);
        settings.setValue("AppName", m_strAppName);
        settings.setValue("Version", m_strSoftVer);
        settings.endGroup();

        /*系统设置*/
        settings.beginGroup("SysConfig");
        settings.setValue("DeviceId", m_strDevId);        /*板卡信息配置*/
        settings.setValue("AlertLanguage", 0);
        settings.setValue("SysVolume", m_nSysVolume);
        settings.setValue("RecVolume", m_nRecVolume);
        settings.endGroup();

        /*服务器设置*/
        settings.beginGroup("Server");
        settings.setValue("SmtpAddr", "220.181.12.12");
        settings.setValue("MsgServer", m_strMsgServer);
        settings.setValue("UdpRoom",   m_nUdpRoomPort);          // 服务器聊天室
        settings.setValue("MsgPort",   m_nTcpMsgPort);          // 服务器下发tcp
        settings.setValue("FilePort",  m_nTcpFilePort);           // 文件传输端口
        settings.endGroup();

        /*服务器设置*/
        settings.beginGroup("DataServer");
        settings.setValue("IpAddr", m_strDataServerAddr);
        settings.setValue("Port", m_nDataServerPort);
        settings.endGroup();
    }
#ifdef Q_WS_QWS
    QProcess::execute("sync");
#endif
}

/**
 * @brief MyApp::setSettingFile 写入配置文件
 * @param group                 组
 * @param key                   key
 * @param value                 值
 */
void MyApp::setSettingFile(const QString &group, const QString &key, const QVariant &value)
{
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.sync();
}

/**
 * @brief MyApp::getSettingKeyValue 读取配置参数
 * @param group
 * @param key
 * @return
 */
QVariant MyApp::getSettingKeyValue(const QString &group, const QString &key, const QVariant &value)
{
    QSettings settings(m_strIniFile, QSettings::IniFormat);
    settings.beginGroup(group);
    return settings.value(key, value);
}

/**
 * @brief MyApp::checkDataDir 检查数据存储目录
 */
void MyApp::checkDirs()
{
    // 数据文件夹
    QDir dir(m_strDataPath);
    if (!dir.exists()) {
        dir.mkdir(m_strDataPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 日志文件夹
    dir.setPath(m_strLogPath);
    if (!dir.exists()) {
        dir.mkdir(m_strLogPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 测试文件夹
    dir.setPath(m_strTestPath);
    if (!dir.exists()) {
        dir.mkdir(m_strTestPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 数据下载文件夹
    dir.setPath(m_strDownloadPath);
    if (!dir.exists()) {
        dir.mkdir(m_strDownloadPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 截图文件夹
    dir.setPath(m_strScreenShotPath);
    if (!dir.exists()) {
        dir.mkdir(m_strScreenShotPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 音频文件夹(普通话版本)
    dir.setPath(m_strWavPath);
    if (!dir.exists()) {
        dir.mkdir(m_strWavPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 音频文件夹(川话版本)
    dir.setPath(m_strDataPath + "wav_local");
    if (!dir.exists()) {
        dir.mkdir(m_strDataPath + "wav_local");
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 录音文件目录
    dir.setPath(m_strRecordPath);
    if (!dir.exists()) {
        dir.mkdir(m_strRecordPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 数据库目录
    dir.setPath(m_strDbPath);
    if (!dir.exists()) {
        dir.mkdir(m_strDbPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 配置文件目录
    dir.setPath(m_strConfPath);
    if (!dir.exists()) {
        dir.mkdir(m_strConfPath);
#ifdef Q_WS_QWS
        QProcess::execute("sync");
#endif
    }

    // 配置文件目录
   dir.setPath(m_strBackupPath);
   if (!dir.exists()) {
       dir.mkdir(m_strBackupPath);
   #ifdef Q_WS_QWS
       QProcess::execute("sync");
   #endif
   }
}
