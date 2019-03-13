#include "sqliteconn.h"

sqliteconn::sqliteconn()
{

}

QSqlDatabase sqliteconn::getsqconn(int myid)
{
    //创建对应文件夹
    QString dbpath="./data/"+QString::number(myid)+"file/"+"message";   //dir不能用路径来初始化，要不然会出双重目录
    QDir dir;
    if(!(dir.exists(dbpath)))
    {
        dir.mkpath(dbpath);
    }

    //打开对应数据库
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    dbpath=dbpath+"/"+QString::number(myid)+"db.db";
    database.setDatabaseName(dbpath);

    if (!database.open())
       {
           qDebug() << "Error: Failed to connect database." << database.lastError();
       }
       else
       {
           qDebug() << "Succeed to connect database." ;
       }
    return database;
}

bool sqliteconn::tableisexit(QSqlDatabase conn, int otherid)
{
    //bool res1;
    QSqlQuery query(conn);
    QString querysentence="select * from sqlite_master where name='friend"+QString::number(otherid)+"'";
    query.exec(querysentence);
    return query.next();
}

bool sqliteconn::createmessageform(QSqlDatabase conn, int otherid)
{
    bool res1;
    QSqlQuery query(conn);
    QString querysentence="create table friend"+QString::number(otherid)+"(sendid int not null,receiveid int not null"
                                                                       ",message varchar(255) not null, "
                                                                       "messagedate datetime not null)";
    res1=query.exec(querysentence);
    return res1;
}

bool sqliteconn::insertmymessage(QSqlDatabase conn, chatmessage *chatms)
{
    bool res1;
    QSqlQuery query(conn);
    QString querysentence="insert into friend"+QString::number(chatms->Getotherid())+" values(?,?,?,?)";
    qDebug()<<querysentence;
    query.prepare(querysentence);
    query.addBindValue(chatms->Getmyid());
    query.addBindValue(chatms->Getotherid());
    query.addBindValue(chatms->Getmessage());
    query.addBindValue(chatms->Getmessagedate());
    return query.exec();
}
