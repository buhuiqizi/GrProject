#ifndef DATABASECOON_H
#define DATABASECOON_H

//此类定义关于数据库的各种操作，需要扩展

#include <common.h>
#include "userinformation.h"
#include "chatmessage.h"

class databasecoon
{
public:
    databasecoon(); //构造函数
    QSqlDatabase  getdbconn();  //数据库连接函数,返回一个数据库连接
    bool userland(QSqlDatabase conn,userinformation *user); //登陆函数
    bool userregister(QSqlDatabase conn,userinformation *user); //注册函数
    bool userinformupdate(QSqlDatabase conn,userinformation *user);   //信息修改函数
    bool userstatusupdate(QSqlDatabase conn,userinformation *user);     //状态修改函数
    bool passwordmodify(QSqlDatabase conn,userinformation *user);       //密码修改函数
    bool getuserinform(QSqlDatabase conn,userinformation *user);     //信息获取函数
    bool getfriendlist(QSqlDatabase conn,userinformation *user);        //好友列表获取函数
    bool getfriendinform(QSqlDatabase conn,userinformation *user);      //好友信息获取函数
    bool getuserstatus(QSqlDatabase conn,userinformation *user);     //状态获取函数
    bool getusermessage(QSqlDatabase conn,userinformation *user);       //获取用户消息表中的消息
    bool savechatmessage(QSqlDatabase conn,chatmessage *chatms);        //消息保存函数

};

#endif // DATABASECOON_H
