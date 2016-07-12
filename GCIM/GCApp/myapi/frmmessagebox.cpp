#include "frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include "global.h"

#include <QMouseEvent>

frmMessageBox::frmMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);

    this->mousePressed = false;
    m_nAcceptRole = 0;

    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);
    //关联关闭按钮
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(sltCancel()));
    //窗体居中显示
    myHelper::FormInCenter(this);
    m_bClose = true;
    m_nTimeCnt = 10;

    // 自动关闭定时器
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sltTimeOut()));
}

frmMessageBox::~frmMessageBox()
{
    delete ui;
}

void frmMessageBox::SetMessage(const QString &msg, int type)
{
    if (type == 0) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/common/info.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText(tr("提示"));
    } else if (type == 1) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/common/question.png);");
        ui->lab_Title->setText(tr("询问"));
    } else if (type == 2) {
        ui->labIcoMain->setStyleSheet("border-image: url(:/images/common/error.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText(tr("错误"));
    }

    // 启动定时器
    m_timer->start(1000);

    ui->labInfo->setText(msg);
    ui->btnCancel->setText(m_bClose ? tr("取消") : tr("拒接"));
}

// 确定按钮
void frmMessageBox::on_btnOk_clicked()
{
    // 停止定时器
    if (m_nTimeCnt > 0) {
        m_timer->stop();
    }

    done(1);
    if (m_bClose)
        this->close();
    else
        this->hide();

    m_nAcceptRole = 1;
}

void frmMessageBox::sltCancel()
{
    done(0);
    if (m_bClose)
        this->close();
    else
        this->hide();
    m_nAcceptRole = 0;
}

// 定时器
void frmMessageBox::sltTimeOut()
{
    m_nTimeCnt--;
    if (m_nTimeCnt < 0) {
        on_btnOk_clicked();
    }
    else
        ui->btnOk->setText(tr("确定(%1)").arg(m_nTimeCnt, 2, 10, QChar('0')));
}

void frmMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
