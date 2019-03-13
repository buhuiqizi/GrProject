#ifndef SENDMESSAGELOOP_H
#define SENDMESSAGELOOP_H


#include <QObject>
#include <QMutex>

class sendmessageloop:public QObject
{
    Q_OBJECT
public:
    sendmessageloop();
    ~sendmessageloop();

public slots:
    void messagesendloop(const QString &parameter);
signals:
    void resultready(const QString &result);
};

class controller:public QObject
{
    Q_OBJECT
    QThread workthread;
public:
    controller();
    ~controller();
public slots:
    void handresult(const QString &);
signals:
    void operate(const QString &);
}

#endif // SENDMESSAGELOOP_H
