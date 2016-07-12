#ifndef FRMMESSAGEBOX_H
#define FRMMESSAGEBOX_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class frmMessageBox;
}

class frmMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmMessageBox(QWidget *parent = 0);
    ~frmMessageBox();

    void SetMessage(const QString &msg, int type);
    bool m_bClose;
    int getAcceptRole() { return m_nAcceptRole; }
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnOk_clicked();
    void sltCancel();
    void sltTimeOut();
private:
    Ui::frmMessageBox *ui;
    QTimer *m_timer;                // 定时关闭
    int m_nTimeCnt;                 // 定时计次

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下

    int m_nAcceptRole;
};

#endif // FRMMESSAGEBOX_H
