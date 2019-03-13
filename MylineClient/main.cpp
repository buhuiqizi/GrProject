#include "mainwindow.h"
#include <QApplication>
#include "tcpreceiver.h"
#include "landwindow.h"
#include "userinformation.h"
#include "registerwindow.h"
#include "friendlistwindow.h"

userinformation *user;
tcpreceiver *receiver;
landwindow *land;
QList<userinformation *> *friendlist;
//landwindow land;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    //下面是用来登陆和注册的
    receiver=new tcpreceiver();
    user=new userinformation();
    friendlist=new QList<userinformation *>;
    //landwindow land;
    land=new landwindow();
    friendlistwindow frienwindow;



    if(land->exec()== QDialog::Accepted)
    {


        qDebug()<<QString::fromLocal8Bit("开始打开好友列表");
        QThread::sleep(10);

        for(int i=0;i<friendlist->size();i++)
        {
            qDebug()<<(*friendlist).at(i)->Getuserid();
            qDebug()<<(*friendlist).at(i)->Getusername();
            qDebug()<<(*friendlist).at(i)->Getgroup();
        }
        //receiver->SendMessage();
        frienwindow.show();
    }
//    friendlistwindow friendwindow;
//    friendwindow.show();

//    registerwindow regist;
//    regist.exec();


    return a.exec();
}
