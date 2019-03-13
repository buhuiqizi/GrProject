#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "tcpreceiver.h"
#include <QDateTime>

extern tcpreceiver *receiver;
extern userinformation *user;

chatwindow::chatwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);

}

//自定义构造函数，用来设置当前聊天窗口的对象
chatwindow::chatwindow(QWidget *parent,int id) :
    QWidget(parent),
    ui(new Ui::chatwindow)
{
    myid=user->Getuserid();
    otherid=id;
    ui->setupUi(this);
    //qDebug()<<otherid;
    chatms=new chatmessage();
    //连接数据库
    sqcn=new sqliteconn();
    conn=sqcn->getsqconn(myid);

    //与该好友的聊天信息表是否存在
    if(!(sqcn->tableisexit(conn,otherid)))
    {
        sqcn->createmessageform(conn,otherid);       //创建这个表
    }
    qDebug()<<QString::fromLocal8Bit("构造函数执行完毕");
}

chatwindow::~chatwindow()
{
    delete ui;
}


void chatwindow::on_pb_sendmessage_clicked()
{

    //如果信息框中没有信息,那么就不做处理
    if(ui->te_sendtext->document()->isEmpty())
    {
        return;
    }
    //将消息类按照格式填入
    chatms->Setmyid(user->Getuserid());
    chatms->Setotherid(this->otherid);
    chatms->Setmessage(ui->te_sendtext->toPlainText());
    chatms->Setmessagedate(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    //发送给服务端
    QByteArray temp=chatms->Serializable(*chatms);
    receiver->SendMessage(4,temp);
    //填入本地的消息数据库
    sqcn->insertmymessage(conn,chatms);
    ui->te_sendtext->clear();
}
