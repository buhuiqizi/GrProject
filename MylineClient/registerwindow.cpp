#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "userinformation.h"
#include "tcpreceiver.h"

extern tcpreceiver *receiver;
extern userinformation *user;

registerwindow::registerwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerwindow)
{
    ui->setupUi(this);
}

registerwindow::~registerwindow()
{
    delete ui;
}

void registerwindow::on_pb_register_clicked()
{
    user->Setusername(ui->le_username->text());
    user->Setpassword(ui->le_passwordone->text());
    user->Setrealname(ui->le_realname->text());
    user->Setsex(ui->le_sex->text());
    user->Setbirthday(ui->le_birthday->text());
    user->Setaddress(ui->le_address->text());
    user->Setemail(ui->le_email->text());
    user->Setphonenumber(ui->le_phonenumber->text());
    user->Setremarks(ui->te_remarks->toPlainText());

    //user->Setusername(QString::fromLocal8Bit("今天是个好天气"));
//    qDebug()<<user->Getusername();
//    qDebug()<<user->Getremarks();
    QByteArray temp=user->Serializable(*user);
//    qDebug()<<QString::fromLocal8Bit("发送用户名和密码");
//    qDebug()<<user->Getusername();
//    qDebug()<<user->Getpassword();
//    qDebug()<<QString::fromLocal8Bit("开始发送");
    receiver->SendMessage(2,temp);
}
