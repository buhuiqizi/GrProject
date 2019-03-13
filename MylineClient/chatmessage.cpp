#include "chatmessage.h"

chatmessage::chatmessage()
{

}

//GET函数

int chatmessage::Getmyid()
{
    return this->myid;
}

int chatmessage::Getotherid()
{
    return this->otherid;
}

QString chatmessage::Getmessage()
{
    return this->message;
}

QString chatmessage::Getmessagedate()
{
    return this->messagedate;
}

//SET函数

void chatmessage::Setmyid(int value)
{
    this->myid=value;
}

void chatmessage::Setotherid(int value)
{
    this->otherid=value;
}

void chatmessage::Setmessage(QString value)
{
    this->message=value;
}

void chatmessage::Setmessagedate(QString value)
{
    this->messagedate=value;
}

QDataStream & operator<<(QDataStream & output, const chatmessage &obj)      //类对象序列化操作符重载
{
    output<<obj.myid<<obj.otherid<<obj.message<<obj.messagedate;
    return output;
}

QDataStream & operator>>(QDataStream & input, chatmessage & obj)            //类对象反序列化操作符重载
{
    input>>obj.myid>>obj.otherid>>obj.message>>obj.messagedate;
    return input;
}


chatmessage* chatmessage::DeSerializable(const QByteArray &datagram)    //反序列化
{
    //读取文件流信息
    QByteArray tmp_array = datagram;
    QBuffer buffer(&tmp_array);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    //反序列化，获取对象信息
    chatmessage *chat=new chatmessage();
    in>>*chat;
    buffer.close();
    qDebug()<<(QString::fromLocal8Bit("反序列化中："));
    qDebug()<<chat->Getmyid();
    qDebug()<<chat->Getotherid();
    qDebug()<<chat->Getmessage();
    qDebug()<<chat->Getmessagedate();
    return chat;
}

QByteArray chatmessage::Serializable(const chatmessage &chat)          //序列化
{
    QByteArray tmp_array;
    QBuffer buffer(&tmp_array);
    buffer.open(QIODevice::WriteOnly);

    QDataStream out(&buffer);
    //序列化对象信息
    out<<chat;
    buffer.close();
    return tmp_array;
}
