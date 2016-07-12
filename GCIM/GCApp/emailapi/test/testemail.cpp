#include "testemail.h"
#include "smtpmime.h"
#include "global.h"
#include "date.h"

testEmail *testEmail::self = 0;

testEmail::testEmail(QObject *parent) :
    QObject(parent)
{

}

/**
 * @brief testEmail::sendEmails
 * 发送邮件，此处只需要发送固定邮箱，因此没有提供参数接口
 */
void testEmail::sendEmails()
{
    // 实例化发送邮件对象
    SmtpClient smtp(MyApp::m_strSmtpAddr);
    // 用户名和密码
    smtp.setUser("cyhc_vict@163.com");
    smtp.setPassword("cyhc1234");

    // 构建邮件主题,包含发件人收件人附件等.
    MimeMessage message;
    message.setSender(new EmailAddress("cyhc_vict@163.com"));

    // 逐个添加收件人
//    message.addRecipient(new EmailAddress("13527450007@139.com"));
    message.addRecipient(new EmailAddress("lynnhua@163.com"));
    message.addRecipient(new EmailAddress("fanyunke123@163.com"));

    // 构建邮件标题
    message.setSubject("车载终端测试日志");

    //构建邮件正文
    MimeHtml text;
    QString strText = "<html><i>";
    strText.append("最近10天，车载终端测试邮件：【");
    strText.append(Date::getBeforDays(10));
    strText.append("-");
    strText.append(QDATE);
    strText.append("】");
    strText += "</i></html>";
    text.setHtml(strText);

    message.addPart(&text);

    //构建附件
#ifdef Q_OS_WIN32
    message.addPart(new MimeAttachment(new QFile("d:/123.txt")));
#else
    QString strFileName = getTarFile();
    if (QFile::exists(strFileName)) {
        message.addPart(new MimeAttachment(new QFile(strFileName)));
    }
    else {
        myDebug("tes log files is not exists!!");
    }
#endif
    // 连接服务器失败
    if (!smtp.connectToHost()){
        myError("connect to SMTP server failed!");
        return;
    }

    // 登录失败
    if (!smtp.login()){
        myError("user login to server failed!");
        return;
    }

    // 邮件发送失败，可能收件人不正确
    if (!smtp.sendMail(message)){
        myError("the email send failed!" << MyApp::m_strSmtpAddr);
        return;
    }
    // 邮件发送成功
    else {
        myDebug("Test-log email send successed!");
    }

    smtp.quit();
}

// 打包文件
QString testEmail::getTarFile()
{
    QString strFileName = MyApp::m_strBackupPath;
    strFileName.append(MyApp::m_strAppName);
    strFileName.append("_log.tar.gz");

    // 打包文件存在，删除之
    if (QFile::exists(strFileName)) {
        QFile::remove(strFileName);
    }

#ifdef Q_OS_UNIX
    QProcess::execute(MyApp::m_strBackupPath + "tar.sh", QStringList() << strFileName);
    QProcess::execute("sync");
#endif
    myHelper::Sleep(1000);

    return strFileName;
}

