#ifndef USERINFORMATION_H
#define USERINFORMATION_H

//此类用来暂时保存用户信息，扩展可能


#include <QString>
#include <QDataStream>
#include <QObject>
#include <QtCore>

class userinformation:public QObject
{
    Q_OBJECT
public:
    userinformation();
private:
    int userid;
    QString username;
    QString password;
    QString newpassword;
    QString realname;
    QString sex;
    QString birthday;
    QString address;
    QString email;
    QString phonenumber;
    QString remarks;
    QString ipaddress;
    QString port;
    QString group;
    int status;

public:
    int Getuserid();
    QString Getusername();
    QString Getpassword();
    QString Getnewpassword();
    QString Getrealname();
    QString Getsex();
    QString Getbirthday();
    QString Getaddress();
    QString Getemail();
    QString Getphonenumber();
    QString Getremarks();
    QString Getipaddress();
    QString Getport();
    QString Getgroup();
    int Getstatus();

public:
    void Setuserid(int value);
    void Setusername(QString value);
    void Setpassword(QString value);
    void Setnewpassword(QString value);
    void Setrealname(QString value);
    void Setsex(QString value);
    void Setbirthday(QString value);
    void Setaddress(QString value);
    void Setemail(QString value);
    void Setphonenumber(QString value);
    void Setremarks(QString value);
    void Setipaddress(QString value);
    void Setport(QString value);
    void Setgroup(QString value);
    void Setstatus(int value);

public:
    friend QDataStream &operator<<(QDataStream & , const userinformation &);        //序列化操作符重载
    friend QDataStream &operator>>(QDataStream & , userinformation &);              //反序列化操作符重载
    userinformation * DeSerializable(const QByteArray &datagram);                    //反序列化
    QByteArray  Serializable(const userinformation &user);                               //序列化
};

#endif // USERINFORMATION_H
