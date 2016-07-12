/********************************************************************************
** Form generated from reading UI file 'frmapplog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMAPPLOG_H
#define UI_FRMAPPLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmAppLog
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *ckLog;
    QPushButton *btnDebug;

    void setupUi(QWidget *frmAppLog)
    {
        if (frmAppLog->objectName().isEmpty())
            frmAppLog->setObjectName(QStringLiteral("frmAppLog"));
        frmAppLog->resize(171, 41);
        horizontalLayout = new QHBoxLayout(frmAppLog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ckLog = new QCheckBox(frmAppLog);
        ckLog->setObjectName(QStringLiteral("ckLog"));

        horizontalLayout->addWidget(ckLog);

        btnDebug = new QPushButton(frmAppLog);
        btnDebug->setObjectName(QStringLiteral("btnDebug"));

        horizontalLayout->addWidget(btnDebug);


        retranslateUi(frmAppLog);

        QMetaObject::connectSlotsByName(frmAppLog);
    } // setupUi

    void retranslateUi(QWidget *frmAppLog)
    {
        frmAppLog->setWindowTitle(QApplication::translate("frmAppLog", "Form", 0));
        ckLog->setText(QApplication::translate("frmAppLog", "\346\227\245\345\277\227\350\276\223\345\207\272", 0));
        btnDebug->setText(QApplication::translate("frmAppLog", "\346\217\220\347\244\272\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class frmAppLog: public Ui_frmAppLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMAPPLOG_H
