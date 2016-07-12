/********************************************************************************
** Form generated from reading UI file 'frmnumberinput.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMNUMBERINPUT_H
#define UI_FRMNUMBERINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmNumberInput
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetInputTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *btnClose;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEditPasswd;
    QGridLayout *gridLayout;
    QPushButton *btn7;
    QPushButton *btn3;
    QPushButton *btn0;
    QPushButton *btn4;
    QPushButton *btn1;
    QPushButton *btn9;
    QPushButton *btnOk;
    QPushButton *btn2;
    QPushButton *btnDelete;
    QPushButton *btn6;
    QPushButton *btn8;
    QPushButton *btn5;

    void setupUi(QWidget *FrmNumberInput)
    {
        if (FrmNumberInput->objectName().isEmpty())
            FrmNumberInput->setObjectName(QStringLiteral("FrmNumberInput"));
        FrmNumberInput->resize(308, 229);
        FrmNumberInput->setStyleSheet(QLatin1String("QPushButton {\n"
"	border: 1px solid #c9c9c9;\n"
"	border-radius: 5px;\n"
"	padding: 0px;\n"
"	color: #000000;\n"
"	background-color: #ffffff;\n"
"	min-width: 90px;\n"
"	min-height: 30px;\n"
"}\n"
"\n"
"QPushButton:hover,QPushButton:pressed {\n"
"	padding: 1px;\n"
"	background-color: #f3f3f3;\n"
"}\n"
"\n"
"QPushButton#btnClose  {\n"
"	border: none;\n"
"	border-radius: 0px;\n"
"	background: transparent;\n"
"	min-width: 30px;\n"
"}\n"
"\n"
"\n"
"QPushButton#btnClose:hover,QPushButton#btnClose:pressed {\n"
"	background-color: #ff0000;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(FrmNumberInput);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetInputTitle = new QWidget(FrmNumberInput);
        widgetInputTitle->setObjectName(QStringLiteral("widgetInputTitle"));
        widgetInputTitle->setMinimumSize(QSize(0, 30));
        widgetInputTitle->setStyleSheet(QLatin1String("background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #4D4D4D, stop:1 #292929);\n"
""));
        horizontalLayout_2 = new QHBoxLayout(widgetInputTitle);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, 0, 0, 0);
        label = new QLabel(widgetInputTitle);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("color: #ffffff;\n"
"font-family: \"\346\245\267\344\275\223\";\n"
"font-size: 18px;\n"
""));

        horizontalLayout_2->addWidget(label);

        btnClose = new QPushButton(widgetInputTitle);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/common/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout_2->addWidget(widgetInputTitle);

        widget_2 = new QWidget(FrmNumberInput);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font-family: \"\346\245\267\344\275\223\";\n"
"font-size: 16px;\n"
"color: #000000;"));

        horizontalLayout->addWidget(label_2);

        lineEditPasswd = new QLineEdit(widget_2);
        lineEditPasswd->setObjectName(QStringLiteral("lineEditPasswd"));
        lineEditPasswd->setMinimumSize(QSize(0, 25));
        lineEditPasswd->setReadOnly(true);

        horizontalLayout->addWidget(lineEditPasswd);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btn7 = new QPushButton(widget_2);
        btn7->setObjectName(QStringLiteral("btn7"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn7->sizePolicy().hasHeightForWidth());
        btn7->setSizePolicy(sizePolicy);
        btn7->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn7, 0, 0, 1, 1);

        btn3 = new QPushButton(widget_2);
        btn3->setObjectName(QStringLiteral("btn3"));
        sizePolicy.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy);
        btn3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn3, 2, 2, 1, 1);

        btn0 = new QPushButton(widget_2);
        btn0->setObjectName(QStringLiteral("btn0"));
        sizePolicy.setHeightForWidth(btn0->sizePolicy().hasHeightForWidth());
        btn0->setSizePolicy(sizePolicy);
        btn0->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn0, 3, 1, 1, 1);

        btn4 = new QPushButton(widget_2);
        btn4->setObjectName(QStringLiteral("btn4"));
        sizePolicy.setHeightForWidth(btn4->sizePolicy().hasHeightForWidth());
        btn4->setSizePolicy(sizePolicy);
        btn4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn4, 1, 0, 1, 1);

        btn1 = new QPushButton(widget_2);
        btn1->setObjectName(QStringLiteral("btn1"));
        sizePolicy.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy);
        btn1->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn1, 2, 0, 1, 1);

        btn9 = new QPushButton(widget_2);
        btn9->setObjectName(QStringLiteral("btn9"));
        sizePolicy.setHeightForWidth(btn9->sizePolicy().hasHeightForWidth());
        btn9->setSizePolicy(sizePolicy);
        btn9->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn9, 0, 2, 1, 1);

        btnOk = new QPushButton(widget_2);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        sizePolicy.setHeightForWidth(btnOk->sizePolicy().hasHeightForWidth());
        btnOk->setSizePolicy(sizePolicy);
        btnOk->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnOk, 3, 2, 1, 1);

        btn2 = new QPushButton(widget_2);
        btn2->setObjectName(QStringLiteral("btn2"));
        sizePolicy.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy);
        btn2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn2, 2, 1, 1, 1);

        btnDelete = new QPushButton(widget_2);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        sizePolicy.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy);
        btnDelete->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnDelete, 3, 0, 1, 1);

        btn6 = new QPushButton(widget_2);
        btn6->setObjectName(QStringLiteral("btn6"));
        sizePolicy.setHeightForWidth(btn6->sizePolicy().hasHeightForWidth());
        btn6->setSizePolicy(sizePolicy);
        btn6->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn6, 1, 2, 1, 1);

        btn8 = new QPushButton(widget_2);
        btn8->setObjectName(QStringLiteral("btn8"));
        sizePolicy.setHeightForWidth(btn8->sizePolicy().hasHeightForWidth());
        btn8->setSizePolicy(sizePolicy);
        btn8->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn8, 0, 1, 1, 1);

        btn5 = new QPushButton(widget_2);
        btn5->setObjectName(QStringLiteral("btn5"));
        sizePolicy.setHeightForWidth(btn5->sizePolicy().hasHeightForWidth());
        btn5->setSizePolicy(sizePolicy);
        btn5->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn5, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(FrmNumberInput);
        QObject::connect(btnClose, SIGNAL(clicked()), FrmNumberInput, SLOT(hide()));

        QMetaObject::connectSlotsByName(FrmNumberInput);
    } // setupUi

    void retranslateUi(QWidget *FrmNumberInput)
    {
        FrmNumberInput->setWindowTitle(QApplication::translate("FrmNumberInput", "Form", 0));
        label->setText(QApplication::translate("FrmNumberInput", "\346\225\260\345\255\227\350\276\223\345\205\245\351\224\256\347\233\230", 0));
        btnClose->setText(QString());
        label_2->setText(QApplication::translate("FrmNumberInput", "\345\257\206\347\240\201\357\274\232", 0));
        btn7->setText(QApplication::translate("FrmNumberInput", "7", 0));
        btn3->setText(QApplication::translate("FrmNumberInput", "3", 0));
        btn0->setText(QApplication::translate("FrmNumberInput", "0", 0));
        btn4->setText(QApplication::translate("FrmNumberInput", "4", 0));
        btn1->setText(QApplication::translate("FrmNumberInput", "1", 0));
        btn9->setText(QApplication::translate("FrmNumberInput", "9", 0));
        btnOk->setText(QApplication::translate("FrmNumberInput", "\347\241\256\345\256\232", 0));
        btn2->setText(QApplication::translate("FrmNumberInput", "2", 0));
        btnDelete->setText(QApplication::translate("FrmNumberInput", "\342\206\220", 0));
        btn6->setText(QApplication::translate("FrmNumberInput", "6", 0));
        btn8->setText(QApplication::translate("FrmNumberInput", "8", 0));
        btn5->setText(QApplication::translate("FrmNumberInput", "5", 0));
    } // retranslateUi

};

namespace Ui {
    class FrmNumberInput: public Ui_FrmNumberInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMNUMBERINPUT_H
