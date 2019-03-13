#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QWidget>
#include "common.h"

namespace Ui {
class loadingwindow;
}

class loadingwindow : public QWidget
{
    Q_OBJECT

public:
    explicit loadingwindow(QWidget *parent = 0);
    ~loadingwindow();

private:
    Ui::loadingwindow *ui;
};

#endif // LOADINGWINDOW_H
