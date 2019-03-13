#ifndef TCPRECEIVER_H
#define TCPRECEIVER_H

#include <QtNetwork>
#include <QDebug>
#include <QObject>


class tcpreceiver:public QObject
{
    Q_OBJECT
public:
    tcpreceiver();
    void SendMessage(ushort type_id);
    void SendMessage(ushort type_id,QByteArray &sendByte);
    void SendMode(int mode);
    void ReceiveMessage();
    void DisConnect();
    void chenggong();
    void shibai();
    void MessageReady();
    void SendUser();
    void isLand();

private:
    QTcpSocket *tcpClient;
};

#endif // TCPRECEIVER_H
