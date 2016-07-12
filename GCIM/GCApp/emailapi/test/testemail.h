#ifndef TESTEMAIL_H
#define TESTEMAIL_H

#include <QObject>
#include <QMutex>

class testEmail : public QObject
{
    Q_OBJECT
public:
    explicit testEmail(QObject *parent = 0);

    static testEmail *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new testEmail;
            }
        }

        return self;
    }

    void sendEmails();
signals:

public slots:
private:
    static testEmail *self;

    QString getTarFile();
};

#endif // TESTEMAIL_H
