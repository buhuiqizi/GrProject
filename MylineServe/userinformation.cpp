#include "userinformation.h"

userinformation::userinformation()
{

}


//GET函数
int userinformation::Getuserid()
{
    return this->userid;
}

QString userinformation::Getusername()
{
    return this->username;
}

QString userinformation::Getpassword()
{
    return this->password;
}

QString userinformation::Getnewpassword()
{
    return this->newpassword;
}

QString userinformation::Getrealname()
{
    return this->realname;
}

QString userinformation::Getsex()
{
    return this->sex;
}

QString userinformation::Getbirthday()
{
    return this->birthday;
}

QString userinformation::Getaddress()
{
    return this->address;
}

QString userinformation::Getemail()
{
    return this->email;
}

QString userinformation::Getphonenumber()
{
    return this->phonenumber;
}

QString userinformation::Getremarks()
{
    return this->remarks;
}

QString userinformation::Getipaddress()
{
    return this->ipaddress;
}

QString userinformation::Getport()
{
    return this->port;
}

QString userinformation::Getgroup()
{
    return this->group;
}

int userinformation::Getstatus()
{
    return this->status;
}

//SET函数
void userinformation::Setuserid(int value)
{
    this->userid=value;
}

void userinformation::Setusername(QString value)
{
    this->username=value;
}

void userinformation::Setpassword(QString value)
{
    this->password=value;
}

void userinformation::Setnewpassword(QString value)
{
    this->newpassword=value;
}

void userinformation::Setrealname(QString value)
{
    this->realname=value;
}

void userinformation::Setsex(QString value)
{
    this->sex=value;
}

void userinformation::Setbirthday(QString value)
{
    this->birthday=value;
}

void userinformation::Setaddress(QString value)
{
    this->address=value;
}

void userinformation::Setemail(QString value)
{
    this->email=value;
}

void userinformation::Setphonenumber(QString value)
{
    this->phonenumber=value;
}

void userinformation::Setremarks(QString value)
{
    this->remarks=value;
}

void userinformation::Setipaddress(QString value)
{
    this->ipaddress=value;
}

void userinformation::Setport(QString value)
{
    this->port=value;
}

void userinformation::Setgroup(QString value)
{
    this->group=value;
}

void userinformation::Setstatus(int value)
{
    this->status=value;
}

QDataStream & operator<<(QDataStream & output, const userinformation &obj)      //类对象序列化操作符重载
{
    output<<obj.username<<obj.password<<obj.newpassword<<obj.realname<<obj.sex<<obj.birthday<<obj.address;
    output<<obj.email<<obj.phonenumber<<obj.remarks<<obj.ipaddress<<obj.port<<obj.status<<obj.userid<<obj.group;
    return output;
}

QDataStream & operator>>(QDataStream & input, userinformation & obj)            //类对象反序列化操作符重载
{
    input>>obj.username>>obj.password>>obj.newpassword>>obj.realname>>obj.sex>>obj.birthday>>obj.address;
    input>>obj.email>>obj.phonenumber>>obj.remarks>>obj.ipaddress>>obj.port>>obj.status>>obj.userid>>obj.group;
    return input;
}


userinformation *  userinformation::DeSerializable(const QByteArray &datagram)    //反序列化
{
    //读取文件流信息
    QByteArray tmp_array = datagram;
    QBuffer buffer(&tmp_array);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    //反序列化，获取对象信息
    userinformation *user=new userinformation();
    in>>*user;
    buffer.close();
    qDebug()<<(QString::fromLocal8Bit("反序列化中："));
    qDebug()<<user->Getusername();
    qDebug()<<user->Getpassword();
    qDebug()<<user->Getrealname();
    qDebug()<<user->Getsex();
    qDebug()<<user->Getbirthday();
    qDebug()<<user->Getemail();
    qDebug()<<user->Getaddress();
    qDebug()<<user->Getphonenumber();
    qDebug()<<user->Getremarks();
    return user;
}

QByteArray  userinformation::Serializable(const userinformation &user)          //序列化
{
    QByteArray tmp_array;
    QBuffer buffer(&tmp_array);
    buffer.open(QIODevice::WriteOnly);

    QDataStream out(&buffer);
    //序列化对象信息
    out<<user;
    buffer.close();
    return tmp_array;
}

