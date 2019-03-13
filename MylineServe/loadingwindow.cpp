#include "loadingwindow.h"
#include "ui_loadingwindow.h"
#include "loadingwindow.h"

loadingwindow::loadingwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loadingwindow)
{
    ui->setupUi(this);

}

loadingwindow::~loadingwindow()
{
    delete ui;
}
