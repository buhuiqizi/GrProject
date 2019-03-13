#ifndef SQLITECOON_H
#define SQLITECOON_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class sqlitecoon
{
public:
    sqlitecoon();
    QSqlDatabase getsqconn();
};

#endif // SQLITECOON_H
