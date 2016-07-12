#ifndef GLOBAL
#define GLOBAL

#include <stdlib.h>
#include <string>
#include <stdio.h>
#ifdef Q_OS_UNIX
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include <QDesktopWidget>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>
#include <QAbstractButton>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTime>
#include <QProcess>
#include <QDir>
#include <QApplication>
#include <QStyleFactory>
#include <QInputDialog>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QStyle>
#include <QDateTime>
#include <QDebug>
#include <QStyleFactory>

#include "myapp.h"
#include "frmmessagebox.h"
#include "unit.h"

#ifdef Q_OS_WIN32
#include <windows.h>
#endif
#include <QSound>


class myHelper {

public:


    //设置编码为UTF8
    static void SetUTF8Code()
    {
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec=QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //窗体居中，并且只有关闭按钮，不能调整大小
    static void FormOnlyCloseInCenter(QWidget *frm)
    {
        //设置窗体居中
        QDesktopWidget desktop;
        int screenX=desktop.availableGeometry().width();
        int screenY=desktop.availableGeometry().height()-40;
        int frmX=frm->width();
        int frmY=frm->height();
        QPoint movePoint(screenX/2-frmX/2,screenY/2-frmY/2);
        frm->move(movePoint);

        //设置窗体不能调整大小
        frm->setFixedSize(frmX,frmY);

        //设置窗体只有最小化按钮
        frm->setWindowFlags(Qt::WindowCloseButtonHint);
    }

    //窗体居中显示
    static void FormInCenter(QWidget *frm)
    {
        int screenX = qApp->desktop()->availableGeometry().width();
        int screenY = qApp->desktop()->availableGeometry().height()-60;
        int wndX = frm->width();
        int wndY = frm->height();
        QPoint movePoint((screenX-wndX)/2,(screenY-wndY)/2);
        frm->move(movePoint);
    }

    //窗体没有最大化按钮
    static void FormNoMaxButton(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowMinimizeButtonHint);
    }

    //窗体只有关闭按钮
    static void FormOnlyCloseButton(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowCloseButtonHint);
    }

    //窗体不能改变大小
    static void FormNotResize(QWidget *frm)
    {
        frm->setFixedSize(frm->width(),frm->height());
    }

    // 设置样式
    static void setStyle(const QString &style) {
        QFile file(":/qss/images/qss/" + style + ".css");
        file.open(QIODevice::ReadOnly);
        qApp->setStyleSheet(file.readAll());
        file.close();
    }

    //16进制字符串转字节数组
    static QByteArray HexStrToByteArray(QString str)
    {
        QByteArray senddata;
        int hexdata,lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len/2);
        char lstr,hstr;
        for(int i=0; i<len; )
        {
            hstr=str[i].toLatin1();
            if(hstr == ' ')
            {
                i++;
                continue;
            }
            i++;
            if(i >= len)
                break;
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
                break;
            else
                hexdata = hexdata*16+lowhexdata;
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }

    // 转换16进制数据为字符型
    static char ConvertHexChar(char ch)
    {
        if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return (-1);
    }

    //字节数组转16进制字符串
    static QString ByteArrayToHexStr(QByteArray data)
    {
        QString temp="";
        QString hex=data.toHex();
        for (int i=0;i<hex.length();i=i+2)
        {
            temp+=hex.mid(i,2);
        }
        return temp.trimmed().toUpper();
    }

    //16进制字符串转10进制
    static int StrHexToDecimal(QString strHex)
    {
        bool ok;
        return strHex.toInt(&ok,16);
    }

    //10进制字符串转10进制
    static int StrDecimalToDecimal(QString strDecimal)
    {
        bool ok;
        return strDecimal.toInt(&ok,10);
    }

    //2进制字符串转10进制
    static int StrBinToDecimal(QString strBin)
    {
        bool ok;
        return strBin.toInt(&ok,2);
    }

    //16进制字符串转2进制字符串
    static QString StrHexToStrBin(QString strHex)
    {
        uchar decimal=StrHexToDecimal(strHex);
        QString bin=QString::number(decimal,2);

        uchar len=bin.length();
        if (len<8)
        {
            for (int i=0;i<8-len;i++)
            {
                bin="0"+bin;
            }
        }

        return bin;
    }

    //10进制转2进制字符串一个字节
    static QString DecimalToStrBin1(int decimal)
    {
        QString bin=QString::number(decimal,2);

        uchar len=bin.length();
        if (len<=8)
        {
            for (int i=0;i<8-len;i++)
            {
                bin="0"+bin;
            }
        }

        return bin;
    }

    //10进制转2进制字符串两个字节
    static QString DecimalToStrBin2(int decimal)
    {
        QString bin=QString::number(decimal,2);

        uchar len=bin.length();
        if (len<=16)
        {
            for (int i=0;i<16-len;i++)
            {
                bin="0"+bin;
            }
        }

        return bin;
    }


    // 根据距离计算485温度偏差值采集值
    static double ConvertTempAtOffer(const int &nInterval, const int &nTemperature)
    {
        double nTempRet = 0.0;
        double dblOffer = 1.0;

        switch (nInterval) {
        case 1:{
            if (nTemperature <= 100) dblOffer = 1.0;
            if (100 < nTemperature && nTemperature <= 200) dblOffer = 0.975;
            if (200 < nTemperature && nTemperature <= 300) dblOffer = 0.966667;
        }
            break;
        case 2:{
            if (nTemperature <= 100) dblOffer = 0.96;
            if (100 < nTemperature && nTemperature <= 200) dblOffer = 0.94;
            if (200 < nTemperature && nTemperature <= 300) dblOffer = 0.93333;
        }
            break;
        case 3:{
            if (nTemperature <= 100) dblOffer = 0.86;
            if (100 < nTemperature && nTemperature <= 200) dblOffer = 0.885;
            if (200 < nTemperature && nTemperature <= 300) dblOffer = 0.836667;
        }
            break;
        case 4:{
            if (nTemperature <= 100) dblOffer = 0.82;
            if (100 < nTemperature && nTemperature <= 200) dblOffer = 0.77;
            if (200 < nTemperature && nTemperature <= 300) dblOffer = 0.74333;
        }
            break;
        case 5:{
            if (nTemperature <= 100) dblOffer = 0.76;
            if (100 < nTemperature && nTemperature <= 200) dblOffer = 0.66;
            if (200 < nTemperature && nTemperature <= 300) dblOffer = 0.666667;
        }
            break;
        default:
            break;
        }

        return nTempRet / dblOffer ;
    }

    //延时
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    //判断是否是IP地址
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }

    //显示信息框,仅确定按钮
    static void ShowMessageBoxInfo(QString info)
    {
        frmMessageBox *msg = new frmMessageBox;
        FormInCenter(msg);
        msg->SetMessage(info, 0);
        msg->exec();
    }

    //显示错误框,仅确定按钮
    static void ShowMessageBoxError(QString info)
    {
        frmMessageBox *msg = new frmMessageBox;
        msg->SetMessage(info, 2);
        msg->exec();
    }

    //显示询问框,确定和取消按钮
    static int ShowMessageBoxQuesion(QString info)
    {
        frmMessageBox *msg = new frmMessageBox;
        FormInCenter(msg);
        msg->SetMessage(info, 1);
        return msg->exec();
    }

    //显示标准输入框
    static QString ShowInputBox(QWidget *frm,QString info)
    {
        bool ok;
        return QInputDialog::getText(frm,"提示",info,QLineEdit::Password,"",&ok);
    }

    //计算校验码
    static uchar GetCheckCode(uchar data[],uchar len)
    {
        uchar temp = 0;

        for (uchar i = 0; i < len; i++)
        {
            temp += data[i];
        }

        return temp % 256;
    }

    //计算485采集校验和
    static QString Get485CheckCode(const QString &address)
    {
        int nTmp = StrHexToDecimal("31");
        nTmp += StrHexToDecimal(address);
        nTmp += StrHexToDecimal("01");
        return QString::number(nTmp, 16);
    }

    //将溢出的char转为正确的uchar
    static uchar GetUChar(uchar data)
    {
        uchar temp;
        if (data > 127)
        {
            temp = data + 256;
        }
        else
        {
            temp = data;
        }
        return temp;
    }

    //获取当前路径
    static QString GetCurrentPath()
    {
        return QString(QCoreApplication::applicationDirPath()+"/");
    }

    //设置系统日期时间 windows
    static void SetSystemDateTime(int year,int month,int day,int hour,int min,int sec)
    {
        QProcess p(0);

        p.start("cmd");
        p.waitForStarted();
        p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();

        p.start("cmd");
        p.waitForStarted();
        p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();
    }

    // 设置系统日期和时间 - linux
    // "030457.00,A,2937.0189,N,10629.9850,E,0.00,111.54,290216,,,A*7C" gps
    static void SetSystemDateTimeForLinux(QString date, QString time) {
#ifdef Q_WS_QWS
        if (0 == MyApp::m_uchTimeSetFlag) {
            //date = date+time ddMMyy
            qDebug() << "date" << date;
            if (date.length() < 6) return;
            date.append(time);
            date = date.left(date.length() - 3);

            QString strDateTime = "20";
            strDateTime.append(date.mid(4, 2));
            strDateTime.append("-");
            strDateTime.append(date.mid(2, 2));
            strDateTime.append("-");
            strDateTime.append(date.mid(0, 2));

            strDateTime.append(" ");
            strDateTime.append(QString("%1").arg(time.mid(0, 2).toInt() + 8, 2, 10, QChar('0')));
            strDateTime.append(":");
            strDateTime.append(time.mid(2, 2));
            strDateTime.append(":");
            strDateTime.append(time.mid(4, 2));

            qDebug() << "dateTime = " << strDateTime << date << time;
            QStringList argu = QStringList() << "-s" << strDateTime;
            QProcess::execute("date", argu);
            QProcess::execute("hwclock -w");
            QProcess::execute("sync");

            MyApp::m_uchTimeSetFlag = 1;
        }
#else
        qDebug() << date + time;
#endif
    }

    //获取桌面大小
    static QSize GetDesktopSize()
    {
        QDesktopWidget desktop;
        return QSize(desktop.availableGeometry().width(),desktop.availableGeometry().height());
    }

    // 获取本机ip地址
    static QString GetIP()
    {
        QList<QHostAddress> list = QNetworkInterface::allAddresses();
        foreach (QHostAddress address, list)
        {
            // 我们使用IPv4地址
            if(address.protocol() == QAbstractSocket::IPv4Protocol)
                return address.toString();
        }
        return "";
    }

    //获取选择的文件
    static QString GetFileName(QString filter)
    {
        return QFileDialog::getOpenFileName(NULL,"选择文件",QCoreApplication::applicationDirPath(),filter);
    }

    //获取选择的文件集合
    static QStringList GetFileNames(QString filter)
    {
        return QFileDialog::getOpenFileNames(NULL,"选择文件",QCoreApplication::applicationDirPath(),filter);
    }

    //获取选择的目录
    static QString GetFolderName()
    {
        return QFileDialog::getExistingDirectory();;
    }

    //获取文件名，含拓展名
    static QString GetFileNameWithExtension(QString strFilePath)
    {
        QFileInfo fileInfo(strFilePath);
        return fileInfo.fileName();
    }

    //获取选择文件夹中的文件
    static QStringList GetFolderFileNames(QStringList filter)
    {
        QStringList fileList;
        QString strFolder = QFileDialog::getExistingDirectory();
        if (!strFolder.length() == 0)
        {
            QDir myFolder(strFolder);

            if (myFolder.exists())
            {
                fileList = myFolder.entryList(filter);
            }
        }
        return fileList;
    }

    //文件夹是否存在
    static bool FolderIsExist(QString strFolder)
    {
        QDir tempFolder(strFolder);
        return tempFolder.exists();
    }

    //文件是否存在
    static bool FileIsExist(QString strFile)
    {
        QFile tempFile(strFile);
        return tempFile.exists();
    }

    //复制文件
    static bool CopyFile(QString sourceFile, QString targetFile)
    {
        if (FileIsExist(targetFile))
        {
            int ret = QMessageBox::information(NULL,"提示","文件已经存在，是否替换？",QMessageBox::Yes | QMessageBox::No);
            if (ret != QMessageBox::Yes)
            {
                return false;
            }
        }
        return QFile::copy(sourceFile,targetFile);
    }

    // 拨号重连
    static void recallDail() {
        QStringList argu = QStringList() << "call" << "evdo";
        QProcess::execute("pppd", argu);
    }

    // 打印日志
    static void printLog(const QString &strtex) {
#ifdef Q_WS_QWS
        QFile file("/opt/data/log/system.log");
        if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) return;
        QTextStream in(&file);
        in << strtex << endl;
        file.close();
#else
        Q_UNUSED(strtex);
#endif
    }


#ifdef Q_OS_WIN32
    static void startAlert(HWND hwnd, int durationMs, int timeoutMs)
    {
        FLASHWINFO info;
        info.cbSize = sizeof(info);
        info.hwnd = hwnd;
        info.dwFlags = FLASHW_TRAY;
        info.dwTimeout = timeoutMs;
        info.uCount = durationMs == 0 ? 10 : durationMs / timeoutMs;
        FlashWindowEx(&info);
    }

    static void stopAlert(HWND hwnd)
    {
        FLASHWINFO info;
        info.cbSize = sizeof(info);
        info.hwnd = hwnd;
        info.dwFlags = FLASHW_STOP;
        info.dwTimeout = 0;
        info.uCount = 0;
        FlashWindowEx(&info);
    }
#endif

    /**
     * @brief playSound 播放提示音
     */
    static void playAlertSound(QString strFile) {
        if (!QFile::exists(strFile)) {
            myDebug("Wav warning file is not exists!" << strFile);
            return;
        }

        QSound::play(strFile);
    }

    // QString 转 unicode 编码字符串
       static QString stringToUnicode(QString str) {
           const QChar *q;
           QChar qtmp;
           QString str0, strout;
           int num;
           q = str.unicode();
           int len = str.count();
           for(int i = 0; i < len; i++)
           {
               qtmp =(QChar)*q++;
               num = qtmp.unicode();
               if (num < 255)
                   strout += "00"; //英文或数字前加"00"

               str0 = str0.setNum(num, 16);//变成十六进制数
               strout += str0;
           }

           return strout;

       }

       // unicode 编码字符串 转 QString
       static QString unicodeToString(QString str) {
           int temp[400];
           QChar qchar[100];
           QString strOut;
           bool ok;
           int count = str.count();
           int len = count / 4;
           for(int i=0; i < count; i += 4)
           {
               // 每四位转化为16进制整型
               temp[i] = str.mid(i, 4).toInt(&ok, 16);
               qchar[i / 4] = temp[i];
               QString str0(qchar, len);
               strOut = str0;
           }

           return strOut;
       }


       // 7-bit编码
       // pSrc: 源字符串指针
       // pDst: 目标编码串指针
       // nSrcLength: 源字符串长度
       // 返回: 目标编码串长度
       int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
       {
           int nSrc;        // 源字符串的计数值
           int nDst;        // 目标编码串的计数值
           int nChar;       // 当前正在处理的组内字符字节的序号，范围是0-7
           unsigned char nLeft;    // 上一字节残余的数据

           // 计数值初始化
           nSrc = 0;
           nDst = 0;

           // 将源串每8个字节分为一组，压缩成7个字节
           // 循环该处理过程，直至源串被处理完
           // 如果分组不到8字节，也能正确处理
           while (nSrc < nSrcLength)
           {
               // 取源字符串的计数值的最低3位
               nChar = nSrc & 7;

               // 处理源串的每个字节
               if (nChar == 0)
               {
                   // 组内第一个字节，只是保存起来，待处理下一个字节时使用
                   nLeft = *pSrc;
               }
               else
               {
                   // 组内其它字节，将其右边部分与残余数据相加，得到一个目标编码字节
                   *pDst = (*pSrc << (8 - nChar)) | nLeft;

                   // 将该字节剩下的左边部分，作为残余数据保存起来
                   nLeft = *pSrc >> nChar;

                   // 修改目标串的指针和计数值
                   pDst++;
                   nDst++;
               }

               // 修改源串的指针和计数值
               pSrc++;
               nSrc++;
           }

           // 返回目标串长度
           return nDst;
       }

       // 7-bit解码
       // pSrc: 源编码串指针
       // pDst: 目标字符串指针
       // nSrcLength: 源编码串长度
       // 返回: 目标字符串长度
       int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
       {
           int nSrc;        // 源字符串的计数值
           int nDst;        // 目标解码串的计数值
           int nByte;       // 当前正在处理的组内字节的序号，范围是0-6
           unsigned char nLeft;    // 上一字节残余的数据

           // 计数值初始化
           nSrc = 0;
           nDst = 0;

           // 组内字节序号和残余数据初始化
           nByte = 0;
           nLeft = 0;

           // 将源数据每7个字节分为一组，解压缩成8个字节
           // 循环该处理过程，直至源数据被处理完
           // 如果分组不到7字节，也能正确处理
           while (nSrc < nSrcLength)
           {
               // 将源字节右边部分与残余数据相加，去掉最高位，得到一个目标解码字节
               *pDst = ((*pSrc << nByte) | nLeft) & 0x7f;

               // 将该字节剩下的左边部分，作为残余数据保存起来
               nLeft = *pSrc >> (7 - nByte);

               // 修改目标串的指针和计数值
               pDst++;
               nDst++;

               // 修改字节计数值
               nByte++;

               // 到了一组的最后一个字节
               if (nByte == 7)
               {
                   // 额外得到一个目标解码字节
                   *pDst = nLeft;

                   // 修改目标串的指针和计数值
                   pDst++;
                   nDst++;

                   // 组内字节序号和残余数据初始化
                   nByte = 0;
                   nLeft = 0;
               }

               // 修改源串的指针和计数值
               pSrc++;
               nSrc++;
           }

           *pDst = 0;

           // 返回目标串长度
           return nDst;
       }

#ifdef Q_OS_UNIX
       // 域名转换ip地址
       static char *domainToIp(const char *domain) {
           struct hostent *host;
           host = gethostbyname(domain);

           if (NULL == host) {
               return NULL;
           }

           // 转换ip
           return inet_ntoa(*((struct in_addr *)host->h_addr));
       }
#endif
    // 转换html
    static void stringToHtmlFilter(QString &str)
    {
        //注意这几行代码的顺序不能乱，否则会造成多次替换
        str.replace("&", "&amp;");
        str.replace(">", "&gt;");
        str.replace("<", "&lt;");
        str.replace("\"", "&quot;");
        str.replace("\'", "&#39;");
        str.replace(" ", "&nbsp;");
        str.replace("\n", "<br>");
        str.replace("\r", "<br>");
    }

    // string 转换成html
    static void stringToHtml(QString &str,QColor crl)
    {
        QByteArray array;
        array.append(crl.red());
        array.append(crl.green());
        array.append(crl.blue());
        QString strC(array.toHex());
        str = QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str);
    }

    // 添加图片
    static void imgPathToHtml(QString &path)
    {
        path = QString("<img src=\"%1\"/>").arg(path);
    }

    // 添加文本
    static void stringToText(QString &str)
    {
        str = QString("<span><p>  %1</span></p>").arg(str);
    }
};

#endif // GLOBAL

