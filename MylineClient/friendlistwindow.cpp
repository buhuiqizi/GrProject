#include "friendlistwindow.h"
#include "ui_friendlistwindow.h"
#include "userinformation.h"
#include "QMessageBox"
#include "chatwindow.h"

extern QList<userinformation *> *friendlist;

friendlistwindow::friendlistwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendlistwindow)
{
    ui->setupUi(this);
    ui->friendlistree->setColumnCount(2);
    ui->friendlistree->setHeaderHidden(true);
    QHeaderView *head=ui->friendlistree->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    //绑定双击函数
    connect(ui->friendlistree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(qtreewidgetclicked(QTreeWidgetItem*,int)));
}

void friendlistwindow::listresfresh()
{
    //树的的开头设置

    QList<QTreeWidgetItem *> rootList;

    if(friendlist->size()==0)
    {
        QMessageBox::information(NULL,"(*^_^*)",QString::fromLocal8Bit("没有好友数据"));
        return;
    }
    //先将第一种分类加入
    QString friendgroup;
    friendgroup=friendlist->at(0)->Getgroup();
    QTreeWidgetItem *myfriend = new QTreeWidgetItem(ui->friendlistree, QStringList(friendgroup));
    rootList << myfriend;

    QTreeWidgetItem* leaf;
    for(int i=0;i<friendlist->size();i++)
    {
        //如果出现新的分类，就改变名字，重新加入
        if(friendgroup.compare((*friendlist).at(i)->Getgroup())!=0)
        {
            friendgroup=(*friendlist).at(i)->Getgroup();
            myfriend=new QTreeWidgetItem(ui->friendlistree, QStringList(friendgroup));
            rootList<<myfriend;
        }
        leaf= new QTreeWidgetItem();
        leaf->setData(0,Qt::UserRole,1);
        leaf->setData(0,Qt::UserRole+1,(*friendlist).at(i)->Getuserid());
        leaf->setText(0,(*friendlist).at(i)->Getusername());
        leaf->setIcon(0,QIcon(tr("ico/test.png")));
        myfriend->addChild(leaf);
    }

//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
//    leaf2->setCheckState(0, Qt::Checked);
//    root->addChild(leaf2);

    ui->friendlistree->insertTopLevelItems(0, rootList);
    //tree->show();


    QWidget::repaint();
}

void friendlistwindow::qtreewidgetclicked(QTreeWidgetItem *item, int column)
{
    //如果不是子节点，则不做处理
    if(item->data(0,Qt::UserRole).toInt()!=1)
       return;
    //新建聊天框对象，传入对方id
    chatwindow *chat=new chatwindow(0,item->data(0,Qt::UserRole+1).toInt());
    chat->show();
}

friendlistwindow::~friendlistwindow()
{
    delete ui;
}

void friendlistwindow::on_pushButton_clicked()
{
    this->listresfresh();
}
