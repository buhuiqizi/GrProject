#include "landwindow.h"
#include "ui_landwindow.h"
#include "userinformation.h"
#include "registerwindow.h"

extern tcpreceiver *receiver;
extern userinformation *user;
int island;

landwindow::landwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::landwindow)
{
    ui->setupUi(this);
}

landwindow::~landwindow()
{
    delete ui;
}

void landwindow::on_pb_land_clicked()
{
    user->Setusername(ui->le_username->text());
    user->Setpassword(ui->le_password->text());
    QByteArray temp=user->Serializable(*user);
    qDebug()<<QString::fromLocal8Bit("发送用户名和密码");
    qDebug()<<user->Getusername();
    qDebug()<<user->Getpassword();
    qDebug()<<QString::fromLocal8Bit("开始发送");
    receiver->SendMessage(1,temp);
}

void landwindow::on_pb_register_clicked()
{
    this->hide();
    registerwindow registe;
    registe.exec();
    this->show();
}
