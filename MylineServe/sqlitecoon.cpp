#include "sqlitecoon.h"

sqlitecoon::sqlitecoon()
{

}

QSqlDatabase sqlitecoon::getsqconn(QString sqname)
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString dbpath=":data"
    database.setDatabaseName("MyDataBase.db");

    if (!database.open())
       {
           qDebug() << "Error: Failed to connect database." << database.lastError();
       }
       else
       {
           qDebug() << "Succeed to connect database." ;
       }
}
