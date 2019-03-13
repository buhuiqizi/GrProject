#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include "userinformation.h"
#include "chatmessage.h"
#include "sqliteconn.h"

namespace Ui {
class chatwindow;
}

class chatwindow : public QWidget
{
    Q_OBJECT

public:
    explicit chatwindow(QWidget *parent = 0);
    explicit chatwindow(QWidget *parent = 0,int id=0);
    ~chatwindow();


private slots:
    void on_pb_sendmessage_clicked();

private:
    Ui::chatwindow *ui;
    int otherid;
    int myid;
    sqliteconn *sqcn;
    QSqlDatabase conn;
    chatmessage *chatms;
};

#endif // CHATWINDOW_H
