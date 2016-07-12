#include "frmapplog.h"
#include "ui_frmapplog.h"
#include "applog.h"
#include "unit.h"
#include <QDateTime>

#include <QDebug>

frmAppLog::frmAppLog(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmAppLog)
{
	ui->setupUi(this);
}

frmAppLog::~frmAppLog()
{
	delete ui;
}

void frmAppLog::on_ckLog_stateChanged(int arg1)
{
	if (arg1 == 0) {
		AppLog::Instance()->Stop();
	} else {
        AppLog::Instance()->Start();
	}
}

void frmAppLog::on_btnDebug_clicked()
{
    qDebug() << DATETIME_FRM1 << "测试输出日志";
}
