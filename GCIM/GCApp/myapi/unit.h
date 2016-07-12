#ifndef UNIT
#define UNIT

#include <stdint.h>
#include <QString>
#include <QDebug>

// 应用程序版本
#define MY_VERSION          0x01000001
#define MY_VERSION_STR      "1.0.0.1"
// 版本检测
#define VERSION_CHECK(a,b,c,d)  ((a << 24) | (b << 16) | (c << 8) | d)

#define FONT_FAMILY "MYingHei_18030_C-Medium"

// 日期定义宏
#define QDATE              (QDateTime::currentDateTime().toString("yyyyMMdd"))
#define DATETIME_FRM1      (QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"))
#define DATETIME_FRM2      (QDateTime::currentDateTime().toString("yyyyMMddhhmmss"))

#define SCREEN_WIDGET 800
#define SCREEN_HEIGHT 480

#define STATUSBAR_HEIGHT 65

#define BUTTON_WIDGET 220
#define BUTTON_HEIGHT 160

// 日志记录
#ifdef SYSTEM_LOG
#define myDebug(x)      (qDebug()    << "Debug "    << __FILE__ << __LINE__ << "]:" << x)
#define myWARNING(x)    (qWarning()  << "Warning "  << __FILE__ << __LINE__ << "]:" << x)
#define myError(x)      (qCritical() << "Error "    << __FILE__ << __LINE__ << "]:" << x)
#define myINFOR(x)      (qInfo()     << "Infor "    << __FILE__ << __LINE__ << "]:" << x)
#else
#define myDebug(x)      (qDebug()     << x)
#define myWARNING(x)    (qWarning()   << x)
#define myError(x)      (qCritical()  << x)
#define myINFOR(x)      (qInfo()      << x)
#endif

// 编码处理
#define GB2312(string)          QTextCodec::codecForName("gb2312")->toUnicode((string))
#define GB2312_CHAR(string)     QTextCodec::codecForName("gb2312")->fromUnicode((string))
#define GBK(string)             QTextCodec::codecForName("GBK")->toUnicode((string))
#define GBK_CHAR(string)        QTextCodec::codecForName("GBK")->fromUnicode((string))
#define GB18030(string)         QTextCodec::codecForName("GB18030")->toUnicode((string))
#define GB18030_CHAR(string)    QTextCodec::codecForName("GB18030")->fromUnicode((string))
#define UTF8(string)            QTextCodec::codecForName("UTF-8")->toUnicode((string))
#define UTF8_CHAR(string)       QTextCodec::codecForName("UTF-8")->fromUnicode((string))


// 播放系统警告提醒声音 add by niyh 20160519
#define WAV_NET_FAILED          "net_failed"        // 数据网络无法连接服务器
#define WAV_NET_OFF             "net_off"           // 网络信号已断开
#define WAV_NET_WARNING         "net_warning"        // 数据网络异常
#define WAV_NET_RECOVERY        "net_recovery"      // 数据网络恢复
#define WAV_GPS_OFF             "gps_off"           // GPS信号断开
#define WAV_GPS_ON              "gps_on"            // GPS信号恢复
#define WAV_SPEED_OVER          "speed_warning"     // 当前车速过快，请控制好车速

// 来电和短信
#define WAV_NEW_MSG             "new_msg"           // 你有新的短消息，请注意查收
#define WAV_MESSAGE             "message"           // 您有网络信息（提示音）
#define WAV_SIP_CALL            "sip_call"          // 你有网络来电（网络电话）
#define WAV_IN_CALL             "in_call"           // 你有普通电话(普通电话)

// 温度告警
#define WAV_HEAD_LEFT_1         "head_left_1"        // 前左1轮，温度过高
#define WAV_HEAD_RIGHT_1        "head_right_1"       // 前右1轮，温度过高
#define WAV_HEAD_LEFT_2         "head_left_2"        // 前左2轮，温度过高
#define WAV_HEAD_RIGHT_2        "head_right_2"       // 前右2轮，温度过高
#define WAV_TAIL_LEFT_1         "tail_left_1"        // 后左1轮，温度过高
#define WAV_TAIL_RIGHT_1        "tail_right_1"       // 后右1轮，温度过高
#define WAV_TAIL_LEFT_2         "tail_left_2"        // 后左2轮，温度过高
#define WAV_TAIL_RIGHT_2        "tail_right_2"       // 后右2轮，温度过高
#define WAV_TAIL_LEFT_3         "tail_left_3"        // 后左2轮，温度过高
#define WAV_TAIL_RIGHT_3        "tail_right_3"       // 后右2轮，温度过高

// WAV组合
#define GET_WAV_FILE(a)         (MyApp::m_strWavPath + QString(a) + ".wav")

// 开关
#define TURN_ON            1
#define TURN_OFF           0

// 桌面page管理
typedef enum {
    PAGE_HOME,
    PAGE_STATUS,
    PAGE_CALL,
    PAGE_SETTING,
    PAGE_VEDIO
} E_WIDGET_PAGE;

// 功能界面
typedef enum {
    WIDGET_STATUS,  // 行车状态
    WIDGET_CALL,    // 主叫中心
    WIDGET_SETTINGS,    // 设置
    WIDGET_VEDIO,       // 视频监控
    WIDGET_COUNT
} E_WIDGETS;

// 消息通知类型
typedef enum {
    NOTIFY_NONE,    // 无通知
    NOTIFY_CALL_UNREAD, // 未接来电
    NOTIFY_CALL_READ, // 已接来电
    NOTIFY_MESSAGE_UNREAD, // 未读短信
    NOTIFY_MESSAGE_READ, // 已读短信

} E_NOTIFY;

// 状态栏通知图标类型设置
typedef enum {
    STATUS_TYPE_CALL,
    STATUS_TYPE_MESSAGE,
    STATUS_TYPE_NETWORK,
    STATUS_TYPE_HANGUP,
    STATUS_TYPE_RECORD,  //录音
} E_STATUS_TYPE;

// SIM status
typedef enum {
    SIM_SYSINFO,
    SIM_NETWORK,
    SIM_SIGNALS,
} E_SIM_STATUS;


// 定义系统按键键值
typedef enum {
    Key_Home            =       0x0100,     // 主页键
    Key_Left            =       0x0101,     // 左移
    Key_Right           =       0x0102,     // 右移
    Key_Ok              =       0x0103,     // 确定
    Key_Other           =       0x0104,     // 其他
} E_KEY;

// 消息类型
typedef enum {
    LOGIN,      // 登录
    LOGOUT,     // 注销
    REPLY,      // 应答
    MESSAGE,    // 短信
    SPEEK,      // 语音
    TEXT_AUDIO, // 文字语言
    BROADCAST,  // 广播
} E_MessageType;


typedef struct  {
    char rld[4];              // riff 标志符号
    int rLen;
    char wld[4];              // 格式类型（wave）
    char fld[4];              // "fmt"

    int fLen;                   // sizeof(wave format matex)

    short wFormatTag;           // 编码格式
    short wChannels;            // 声道数
    int nSamplesPersec ;        // 采样频率
    int nAvgBitsPerSample;      // WAVE文件采样大小
    short wBlockAlign;          // 块对齐
    short wBitsPerSample;       // WAVE文件采样大小

    char dld[4];                // ”data“
    int wSampleLength;          // 音频数据的大小

} s_wavhead_t;


#endif // UNIT

