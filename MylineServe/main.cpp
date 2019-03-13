#include "userinformation.h"
#include <common.h>
#include "databasecoon.h"
#include "tcpsender.h"


//类外定义函数，一定要加区域限定符，要不然会报错
//添加了新的.h和.cpp文件后，一定要删除一次build文件夹，要不然会报错。
tcpsender *sender;      //监听socket
databasecoon *dbcn;      //数据库类对象
QSqlDatabase conn;      //数据库连接对象
userinformation *user;  //本机账号对象
QList<userinformation *> *friendlist;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    QByteArray sendByte;
//    QDataStream out(&sendByte,QIODevice::WriteOnly);        //数据流
//    out.setByteOrder(QDataStream::BigEndian);               //设置大端模式
//    out<<ushort(0)<<ushort(0);                              //包头占位，为了测量完整大小
//    qDebug()<<sendByte.size();


    sender=new tcpsender();
    dbcn=new databasecoon();
    conn=dbcn->getdbconn();    //获取数据库连接
    user=new userinformation();
    friendlist=new QList<userinformation *>;

    /*user->Setpassword("testpass");
    user->Setusername("testuser");

    qDebug()<<user->Getusername();
    qDebug()<<user->Getpassword();

    QByteArray temp=user->Serializable(*user);
    user=user->DeSerializable(temp);

    qDebug()<<user->Getusername();
    qDebug()<<user->Getpassword()*/;

    //dbcn.userland(conn,user);   //登陆
    //dbcn.userregister(conn,user);

//    loadingwindow w;
//    w.show();

    return a.exec();
}
