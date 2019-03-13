#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

//此类用来保存聊天信息
#include <QString>
#include <QDataStream>
#include <QObject>
#include <QtCore>

class chatmessage:public QObject
{
    Q_OBJECT
public:
    chatmessage();

private:
    int myid;
    int otherid;
    QString message;
    QString messagedate;


public:
    int Getmyid();
    int Getotherid();
    QString Getmessage();
    QString Getmessagedate();
public:
    void Setmyid(int value);
    void Setotherid(int value);
    void Setmessage(QString value);
    void Setmessagedate(QString value);

public:
    friend QDataStream &operator<<(QDataStream & , const chatmessage &);        //序列化操作符重载
    friend QDataStream &operator>>(QDataStream & , chatmessage &);              //反序列化操作符重载
    chatmessage* DeSerializable(const QByteArray &datagram);                    //反序列化
    QByteArray Serializable(const chatmessage &chat);                               //序列化
};

#endif // CHATMESSAGE_H
