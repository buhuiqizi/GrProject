#include "databasecoon.h"

//析构函数的相关操作还未添加

extern QList<userinformation *> *friendlist;

databasecoon::databasecoon()//构造函数
{

}

QSqlDatabase  databasecoon::getdbconn()  //数据库连接函数，返回一个数据库连接
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mylinedatabase");
    db.setUserName("root");
    db.setPassword("lmbdyn1997725");
    bool ok = db.open();

        if(ok){
            QMessageBox::information(NULL,"test",QString::fromLocal8Bit("连接成功!"));
        }else{
            QMessageBox::information(NULL,"test",QString::fromLocal8Bit("连接失败!"));
        }

    return db;
}


bool  databasecoon::userland(QSqlDatabase conn,userinformation *user)   //用户登陆
{
    //user->Setusername(QString::fromLocal8Bit("测试账号"));  //要在添加的时候使用QString::fromLocal8Bit，要不然会存储乱码
    //user->Setpassword(QString::fromLocal8Bit("测试密码"));  //而内部传递时，编码是对的，应该是要在由单纯的"test"这样的向QString自动转换时添加QString::fromLocal8Bit
                                                           //“QString QString::fromLocal8Bit(const QByteArray &)” “QString QString::fromLocal8Bit(const char *,int)”
    bool isexist=false;
    QSqlQuery query(conn);
    query.prepare("select * from userid where username=? and password=?");
    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());
    query.exec();
    int size=query.size();
    if(size==1)
    {
        isexist=true;
        //QMessageBox::information(NULL,"test",QString::fromLocal8Bit("登陆成功!"));
    }
    //else QMessageBox::information(NULL,"test",QString::fromLocal8Bit("登陆失败!"));
    return isexist;         //如果用户名和密码正确，则返回true
}

bool databasecoon::userregister(QSqlDatabase conn,userinformation *user)        //要同时向三个表中插入数据
{

//    user->Setusername(QString::fromLocal8Bit("测试账号2"));
//    user->Setpassword(QString::fromLocal8Bit("测试密码2"));
//    user->Setrealname(QString::fromLocal8Bit("测试账号2"));
//    user->Setsex(QString::fromLocal8Bit("男"));
//    user->Setbirthday("1997-11-23");
//    user->Setaddress(QString::fromLocal8Bit("男"));
//    user->Setemail(QString::fromLocal8Bit("男"));
//    user->Setphonenumber(QString::fromLocal8Bit("男"));
//    user->Setremarks(QString::fromLocal8Bit("男"));

    bool res1,res2,res3,res4,res5;        //保存三条语句执行后的返回值
    QSqlQuery query(conn);      //数据库操作类实例化

    query.exec("START TRANSACTION");    //开始事务

    query.prepare("insert into userid (username,password) values (?,?)");   //先向userid数据库中插入用户名和密码
    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());
    res1=query.exec();

    //再将详细数据插入userinformation中
    //@@identity是表示的是最近一次向具有identity属性(即自增列)的表插入数据时对应的自增列的值,是系统定义的全局变量

    query.prepare("insert into userinformation (id,realname,sex,birthday,address,email,phonenumber,remarks) "
                  "values(@@IDENTITY,?,?,?,?,?,?,?)");

    query.addBindValue(user->Getrealname());
    query.addBindValue(user->Getsex());
    query.addBindValue(user->Getbirthday());
    query.addBindValue(user->Getaddress());
    query.addBindValue(user->Getemail());
    query.addBindValue(user->Getphonenumber());
    query.addBindValue(user->Getremarks());
    res2=query.exec();

    query.prepare("insert into userstatus (id) values(@@IDENTITY)");    //然后将id插入userstatus中
    res3=query.exec();


    //得到刚刚自增的id，因为要拿来建表
    query.prepare("select @@IDENTITY");
    query.exec();query.next();
    QString strid=query.value(0).toString();

    //字符床拼接，因为表格名不能使用占位符，注意拼接前后都要加上空格。
    QString querysentence="create table "+strid+"friend"+"( friendid INT NOT NULL,"
                                                                       " friendgroup varchar(20) NOT NULL, "
                                                                       "PRIMARY KEY ( friendid ))";
    query.prepare(querysentence);    //创建以该用户命名的好友表
    res4=query.exec();

    querysentence="create table "+strid+"message"+"( friendid INT NOT NULL,"
                                                                       " message varchar(255) NOT NULL ,"
                                                                "messagedate datetime NOT NULL"
                                                                       ")";
    query.prepare(querysentence);    //创建以该用户命名的消息表
    res5=query.exec();

    qDebug()<<"res1:"<<res1<<"res2:"<<res2<<"res3:"<<res3<<"res4:"<<res4<<"res5:"<<res5<<"strid:"<<strid;

    if(res1&&res2&&res3&&res4&&res5)     //如果四条都执行成功
    {
        query.exec("COMMIT");  //提交操作
        //QMessageBox::information(NULL,"test",QString::fromLocal8Bit("提交!"));
        return true;
    }
    else                    //如果至少有一条失败
    {
        query.exec("ROLLBACK");    //回滚操作
        //QMessageBox::information(NULL,"test",QString::fromLocal8Bit("回滚!"));
        return false;
    }
}

bool databasecoon::userinformupdate(QSqlDatabase conn, userinformation *user)   //用户信息更新函数
{
    bool res1;
    QSqlQuery query(conn);
    query.prepare("update userinformation set realname=?,sex=?,birthday=?,address=?,email=?,phonenumber=?,remarks=? "
                  "where id=(select id from userid where username=? and password=?)");

    query.addBindValue(user->Getrealname());
    query.addBindValue(user->Getsex());
    query.addBindValue(user->Getbirthday());
    query.addBindValue(user->Getaddress());
    query.addBindValue(user->Getemail());
    query.addBindValue(user->Getphonenumber());
    query.addBindValue(user->Getremarks());
    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());

    res1=query.exec();
    return res1;
}

bool databasecoon::userstatusupdate(QSqlDatabase conn, userinformation *user)  //用户状态更新函数
{
    bool res1;
    QSqlQuery query(conn);
    query.prepare("update userstatus set ipaddress=?,port=?,status=? "
                  "where id=(select id from userid where username=? and password=?)");

    query.addBindValue(user->Getipaddress());
    query.addBindValue(user->Getport());
    query.addBindValue(user->Getstatus());
    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());

    res1=query.exec();
    return res1;
}

bool databasecoon::passwordmodify(QSqlDatabase conn, userinformation *user)     //密码修改函数
{
    bool res1;
    QSqlQuery query(conn);
    query.prepare("update userid set password=? "
                  "where  username=? and password=?");

    query.addBindValue(user->Getnewpassword());
    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());

    res1=query.exec();

    if(res1)
    {
        user->Setpassword(user->Getnewpassword());   //将user中的密码修改为新密码
    }

    return res1;
}

bool databasecoon::getuserinform(QSqlDatabase conn, userinformation *user)      //用户信息获取函数
{
    bool res1;
    QSqlQuery query(conn);
    query.prepare("select * from userinformation where id=(select id from userid where username=? and password=?)");

    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());
    res1=query.exec();
    query.next();

    user->Setuserid(query.value(0).toInt());
    user->Setrealname(query.value(1).toString());
    user->Setsex(query.value(2).toString());
    user->Setbirthday(query.value(3).toString());
    user->Setaddress(query.value(4).toString());
    user->Setemail(query.value(5).toString());
    user->Setphonenumber(query.value(6).toString());
    user->Setremarks(query.value(7).toString());

    return res1;
}

bool databasecoon::getfriendlist(QSqlDatabase conn, userinformation *user)      //好友列表获取函数
{
    bool res1;
    QSqlQuery query(conn);
    //查询对应用户的好友表
    QString querysentence="select * from "+QString::number(user->Getuserid())+"friend "+"ORDER BY friendgroup DESC";
    query.prepare(querysentence);
    res1=query.exec();

    userinformation *friendinf;

    while(query.next()) //当还有数据时
    {
        friendinf=new userinformation();
        friendinf->Setuserid(query.value(0).toInt());
        friendinf->Setgroup(query.value(1).toString());
        //qDebug()<<friendinf->Getgroup();
        friendlist->append(friendinf);
    }

    return res1;
}

bool databasecoon::getfriendinform(QSqlDatabase conn,userinformation *user)    //好友信息获取函数
{
    bool res1,res2;
    QSqlQuery query(conn);

    query.prepare("select * from userinformation where id=?");
    query.addBindValue(user->Getuserid());
    res1=query.exec();
    query.next();
    user->Setrealname(query.value(1).toString());
    user->Setsex(query.value(2).toString());
    user->Setbirthday(query.value(3).toString());
    user->Setaddress(query.value(4).toString());
    user->Setemail(query.value(5).toString());
    user->Setphonenumber(query.value(6).toString());
    user->Setremarks(query.value(7).toString());

    query.prepare("select * from userid where id=?");
    query.addBindValue(user->Getuserid());
    res2=query.exec();
    query.next();
    user->Setusername(query.value(1).toString());

    return (res1&&res2);
}

bool databasecoon::getuserstatus(QSqlDatabase conn, userinformation *user)      //用户状态获取函数
{
    bool res1;
    QSqlQuery query(conn);
    query.prepare("select * from userstatus where id=(select id from userid where username=? and password=?)");

    query.addBindValue(user->Getusername());
    query.addBindValue(user->Getpassword());
    res1=query.exec();
    query.next();

    user->Setipaddress(query.value(0).toString());
    user->Setport(query.value(1).toString());
    user->Setstatus(query.value(2).toInt());

    return res1;
}

bool databasecoon::getusermessage(QSqlDatabase conn, userinformation *user)
{
    bool rea1;
    QSqlQuery query(conn);
    //这里要做到取一条，删一条
    query.prepare()
}

bool databasecoon::savechatmessage(QSqlDatabase conn, chatmessage *chatms)      //消息保存函数
{
    bool res1;
    QSqlQuery query(conn);
    QString querysentence="INSERT INTO "+QString::number(chatms->Getotherid())+"message "+"(friendid,message,messagedate) VALUES(?,?,?)";
    query.prepare(querysentence);
    query.addBindValue(chatms->Getmyid());
    query.addBindValue(chatms->Getmessage());
    query.addBindValue(chatms->Getmessagedate());

    res1=query.exec();
    qDebug()<<QString::fromLocal8Bit("保存聊天是否成功:")<<res1<<"id:"<<QString::number(chatms->Getotherid())<<chatms->Getmessagedate();

    return res1;
}
