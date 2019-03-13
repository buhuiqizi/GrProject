#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QtNetwork>
#include <QDebug>
#include <QObject>

class tcpsender:public QObject
{
    Q_OBJECT
public:
    tcpsender();

    void SendMessage(ushort type_id);
    void SendMessage(ushort type_id,QByteArray &sendByte);
    void ReceiveMessage();
    void SelectMode();
    void DisConnect();
    void ConnectToClient();
    void ReiceiveLand();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    int mode;

private slots:

};

#endif // TCPSENDER_H
