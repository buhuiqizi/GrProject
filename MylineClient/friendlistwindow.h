#ifndef FRIENDLISTWINDOW_H
#define FRIENDLISTWINDOW_H

#include <QWidget>
#include <QTreeWidget>

namespace Ui {
class friendlistwindow;
}

class friendlistwindow : public QWidget
{
    Q_OBJECT

public:
    explicit friendlistwindow(QWidget *parent = 0);
    ~friendlistwindow();

public:
    void listresfresh();


private slots:
    void on_pushButton_clicked();
    void qtreewidgetclicked(QTreeWidgetItem*,int);

private:
    Ui::friendlistwindow *ui;

};

#endif // FRIENDLISTWINDOW_H
