#ifndef SQLITECONN_H
#define SQLITECONN_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "chatmessage.h"


class sqliteconn
{
public:
    sqliteconn();
    QSqlDatabase getsqconn(int myid);
    bool tableisexit(QSqlDatabase conn,int otherid);            //查询表格是否存在
    bool createmessageform(QSqlDatabase conn,int otherid);       //创建消息表格
    bool insertmymessage(QSqlDatabase conn,chatmessage *chatms);         //插入自己发送的消息
    bool insertotmessage(QSqlDatabase conn,chatmessage *chatms);         //插入对面发送的消息
    bool readmessage(QSqlDatabase conn,chatmessage *chatms);             //读取消息
};

#endif // SQLITECONN_H
