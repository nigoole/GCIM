#ifndef MYAPP_H
#define MYAPP_H

#include <QObject>

class QApplication;

class MyApp
{
public:
    //=======================系统配置部分=========================//
    static QString m_strAppPath;         // 应用程序路径
    static QString m_strDataPath;        // 数据保存路径
    static QString m_strLogPath;         // 日志保存路径
    static QString m_strTestPath;        // 测试保存路径
    static QString m_strDownloadPath;    // 下载目录
    static QString m_strScreenShotPath;  // 截图目录

    static QString m_strWavPath;         // 音频目录   add by niyh 20160519
    static QString m_strRecordPath;      // 录音目录   add by niyh 20160522

    static QString m_strDbPath;          // 数据库目录 add by niyh 20160612
    static QString m_strConfPath;        // 配置目录   add by niyh 20160612

    static QString m_strBackupPath;      // 备份目录   add by niyh 20160612

    static QString m_strIniFile;         // 配置文件

    // 版本信息
    static QString m_strHeadVer;        // 硬件版本
    static QString m_strSoftVer;        // 软件版本

    //=======================APP配置部分=========================//
    // 设备ID编号
    static QString m_strDevId;

    // 数据上传服务器地址和端口
    static QString m_strDataServerAddr;
    static int     m_nDataServerPort;

    // 程序自动升级处理
    static QString m_strUpServerUrl;
    static QString m_strCheckVersion;
    static QString m_strAppName;

    // 系统音量控制
    static int m_nSysVolume;            // 系统音量 dd by niyh 20160526
    static int m_nRecVolume;            // 录音音量 add by niyh 20160526

    // 网络状态检测：升级和上传文件时需要
    static bool m_bNetwork;             // 网络状态监听 add by niyh 20160606

    // smtp服务器地址：目前域名解析不出来，只能手动配置服务器地址 add by niyh 20160612
    static QString m_strSmtpAddr;      // SMTP服务器地址，本项目中采用163的服务器地址

    // 用户信息 add by nyh 20160615
    static quint32 m_nUserId;
    static QString m_strPwd;
    static QString m_strMsgServer;      // 网络服务器地址
    static quint16 m_nUdpRoomPort;      // 服务器聊天室端口
    static quint16 m_nTcpMsgPort;       // 网络短信语音端口
    static quint16 m_nTcpFilePort;      // 文件服务器端口

    //=======================函数功能部分=========================//
    // 初始化
    static void init(QApplication &app);
    // 创建配置文件
    static void creatorSettingFile();
    // 读取/修改配置文件
    static void setSettingFile(const QString &group, const QString &key, const QVariant &value);
    static QVariant getSettingKeyValue(const QString &group, const QString &key, const QVariant &value);
    // 检查目录
    static void checkDirs();
};

#endif // MYAPP_H
