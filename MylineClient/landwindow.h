#ifndef LANDWINDOW_H
#define LANDWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "tcpreceiver.h"
#include "common.h"

namespace Ui {
class landwindow;
}

class landwindow : public QDialog
{
    Q_OBJECT

public:
    explicit landwindow(QWidget *parent = 0);
    ~landwindow();

private slots:
    void on_pb_land_clicked();

    void on_pb_register_clicked();

private:
    Ui::landwindow *ui;
};

#endif // LANDWINDOW_H
