#include "sendmessageloop.h"
#include "userinformation.h"
#include "tcpsender.h"
#include "databasecoon.h"


extern tcpsender *sender;      //监听socket
extern databasecoon *dbcn;      //数据库类对象
extern QSqlDatabase conn;
extern userinformation *user;

sendmessageloop::sendmessageloop()
{

}

sendmessageloop::~sendmessageloop()
{

}

void sendmessageloop::messagesendloop(const QString &parameter)      //消息循环函数
{
    while (1) {
        //查询对应的用户的消息表，查看是否有消息，如果有，则循环发送消息
    }
}

controller::controller()
{
    sendmessageloop *messageloop=new sendmessageloop();
    messageloop->moveToThread(&workthread);
    connect(&workthread,&QThread::finished,messageloop,&deleteLater);
    connect(this,&controller::operate,messageloop,&sendmessageloop::messagesendloop);
    connect(messageloop,&sendmessageloop::resultready,&workthread,&handresult);
    workthread.start();
}

controller::~controller()
{
    workthread.quit();
    workthread.wait();
}
