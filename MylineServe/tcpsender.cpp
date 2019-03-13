#include "tcpsender.h"
#include "userinformation.h"
#include "databasecoon.h"
#include "chatmessage.h"

extern userinformation *user;
extern databasecoon *dbcn;
extern QSqlDatabase conn;
extern QList<userinformation *> *friendlist;

QByteArray m_buffer;

//连续写数据，但是readall会一次性读取出来

tcpsender::tcpsender()
{
    bool inmode=false;
    tcpServer=new QTcpServer(NULL);

    if(tcpServer->listen(QHostAddress::Any,8000))
    {
        qDebug()<<QString::fromLocal8Bit("端口监听成功");
    }
    else
    {
        qDebug()<<QString::fromLocal8Bit("端口监听失败");
    }

    //绑定新连接信号与连接处理函数，下面是QT5的connect写法
    connect(tcpServer, &QTcpServer::newConnection, this, &tcpsender::ConnectToClient);
    //QT4的写法，槽函数需要使用private slot指定出来，而且newConnection和ConnectToClient前面不能加上区域限定 QTcpServer::
    //QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(ConnectToClient()));


    qDebug()<<QNetworkInterface().allAddresses().at(1).toString();
    //tcpSocket->connectToHost(QHostAddress::Any,8000);
}


void tcpsender::ConnectToClient()   //连接客户端
{
    qDebug()<<QString::fromLocal8Bit("开始连接");
    tcpSocket=tcpServer->nextPendingConnection();

    //对方发送消息后消息处理的绑定工作
    connect(tcpSocket,&QTcpSocket::readyRead,this,&tcpsender::ReceiveMessage);      //将模式选择函数与消息接收信息连接起来

    QString ip=tcpSocket->peerAddress().toString();
    qint16 port=tcpSocket->peerPort();                  //得到ip和port
    qDebug()<<QString::fromLocal8Bit("连接成功");
}

void tcpsender::SendMessage(ushort type_id)      //用来发送确认信息
{
    QByteArray allByte;
    QDataStream out(&allByte,QIODevice::WriteOnly);        //数据流
    out.setByteOrder(QDataStream::BigEndian);               //设置大端模式
    out<<ushort(0)<<ushort(0);                             //包头占位，为了测量完整大小
    out.device()->seek(0);                                  //回到数据开头
    ushort len = (ushort)(allByte.size());                 //计算出完整大小
    out<<type_id<<len;                                      //将数据类型和长度插入数据包
    tcpSocket->write(allByte);                             //发送数据
}

void tcpsender::SendMessage(ushort type_id,QByteArray &sendByte)      //数据发送函数
{
    QByteArray allByte;
    QDataStream out(&allByte,QIODevice::WriteOnly);        //数据流
    out.setByteOrder(QDataStream::BigEndian);               //设置大端模式
    out<<ushort(0)<<ushort(0)<<sendByte;                              //包头占位，为了测量完整大小
    out.device()->seek(0);                                  //回到数据开头
    ushort len = (ushort)(allByte.size());                 //计算出完整大小
    out<<type_id<<len;                                      //将数据类型和长度插入数据包
    tcpSocket->write(allByte);                             //发送数据
}

void tcpsender::ReceiveMessage()
{
    //缓冲区没有数据，直接无视
    if( tcpSocket->bytesAvailable() <= 0 )
    {
        return;
    }
    //临时获得从缓存区取出来的数据，但是不确定每次取出来的是多少。
    QByteArray buffer;
    //如果是信号readyRead触发的，使用readAll时会一次把这一次可用的数据全总读取出来
    //所以使用while(m_tcpClient->bytesAvailable())意义不大，其实只执行一次。
    buffer = tcpSocket->readAll();

    //上次缓存加上这次数据
    /*
        上面有讲到混包的三种情况，数据A、B，他们过来时有可能是A+B、B表示A包+B包中一部分数据，
        然后是B包剩下的数据，或者是A、A+B表示A包一部分数据，然后是A包剩下的数据与B包组合。
        这个时候，我们解析时肯定会残留下一部分数据，并且这部分数据对于下一包会有效，所以我们
        要和下一包组合起来。
    */
    m_buffer.append(buffer);
    ushort type_id, mesg_len;
    int totalLen = m_buffer.size();

    while( totalLen )
    {
        //与QDataStream绑定，方便操作。
        QDataStream packet(m_buffer);
        packet.setByteOrder(QDataStream::BigEndian);


        //不够包头的数据直接就不处理。
        if( totalLen < 4 )
        {
            break;
        }


        packet >> type_id >> mesg_len;


        //如果不够长度等够了在来解析
        if( totalLen < mesg_len )
        {
            break;
        }



        //数据足够多，且满足我们定义的包头的几种类型
        switch(type_id)
        {
            case 0:
            break;


            case 1:         //登陆信息
            {
                QByteArray tmpdata;
                packet >> tmpdata;
                tmpdata=tmpdata.left(mesg_len);
                user=user->DeSerializable(tmpdata);
                bool isexist=dbcn->userland(conn,user);
                if(isexist)
                {
                    qDebug()<<(QString::fromLocal8Bit("用户存在"));
                    this->SendMessage(21);
                    //获取登陆的用户的信息
                    bool isok=dbcn->getuserinform(conn,user);
                    QByteArray temp=user->Serializable(*user);
                    this->SendMessage(13,temp);
                    //获取好友列表
                    isok=dbcn->getfriendlist(conn,user);
                    //获取并发送好友信息
                    for(int i=0;i<friendlist->size();i++)
                    {
                        dbcn->getfriendinform(conn,(*friendlist).at(i));
                        temp=user->Serializable(*(*friendlist).at(i));
                        qDebug()<<"test this is group:";
                        qDebug()<<(*friendlist).at(i)->Getgroup();
                        this->SendMessage(23,temp);
                    }

                }
                else
                {
                    qDebug()<<(QString::fromLocal8Bit("用户不存在"));
                    this->SendMessage(11);
                }
                break;
            }



            case 2:     //注册信息
            {

                QByteArray tmpdata;
                packet >> tmpdata;
                tmpdata=tmpdata.left(mesg_len);
                user=user->DeSerializable(tmpdata);
                bool istrue=dbcn->userregister(conn,user);
                if(istrue)
                {
                    qDebug()<<(QString::fromLocal8Bit("注册成功"));
                    this->SendMessage(22);
                }
                else
                {
                    qDebug()<<(QString::fromLocal8Bit("注册失败"));
                    this->SendMessage(12);
                }
//                //这里我把所有的数据都缓存在内存中，因为我们传输的文件不大，最大才几M;
//                //大家可以这里收到一个完整的数据包，就往文件里面写入，即使保存。
//                m_recvData.append(tmpdata);
//                //这个可以最后拿来校验文件是否传完，或者是否传的完整。
//                m_checkSize += tmpdata.size();
//                //打印提示，或者可以连到进度条上面。
//                emit sig_displayMesg(QString(”recv: %1”).arg(m_checkSize));
                break;
            }



            case 4:     //聊天信息
            {

                QByteArray tmpdata;
                packet >> tmpdata;
                tmpdata=tmpdata.left(mesg_len);
                chatmessage *chatms=new chatmessage;
                chatms=chatms->DeSerializable(tmpdata);
                dbcn->savechatmessage(conn,chatms);
//                packet >> m_DataSize;
//                saveImage();
//                clearData();
            }
                break;


            default:
            break;
        }


        //缓存多余的数据
        buffer = m_buffer.right(totalLen - mesg_len);


        //更新长度
        totalLen = buffer.size();


        //更新多余数据
        m_buffer = buffer;


    }
}


void tcpsender::SelectMode()        //接收消息类型选择函数
{
    QByteArray temp=tcpSocket->readAll();
    qDebug()<<(QString::fromLocal8Bit(temp));


        int mode=temp.toInt();
    qDebug()<<"mode:"<<mode;

        switch (mode) {             //通过传递过来的参数决定将readyRead信号绑定到哪一个函数上面
        case 0:                     //退出信号

            break;                  //登陆信号
        case 1:
            disconnect(tcpSocket,&QTcpSocket::readyRead,this,&tcpsender::SelectMode);       //先解除连接
            connect(tcpSocket,&QTcpSocket::readyRead,this,&tcpsender::ReiceiveLand);        //连接登陆用消息接收函数
            qDebug()<<(QString::fromLocal8Bit("已经准备好接收"));
            tcpSocket->write("OK");
            break;                  //注册信号
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            break;
        }

}

void tcpsender::DisConnect()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket=NULL;
}

void tcpsender::ReiceiveLand()      //接收登陆的用户的信息
{
    qDebug()<<(QString::fromLocal8Bit("开始接收信息"));
    QByteArray temp=tcpSocket->readAll();
    qDebug()<<(QString::fromLocal8Bit("接收完毕"));
    user=user->DeSerializable(temp);            //反序列化，得到用户信息
    qDebug()<<(QString::fromLocal8Bit("反序列化完毕"));
    bool isexist=dbcn->userland(conn,user);                  //进行查询
    qDebug()<<(QString::fromLocal8Bit("查询完毕"));
    qDebug()<<user->Getusername();
    qDebug()<<user->Getpassword();
    if(isexist)
    {
        qDebug()<<(QString::fromLocal8Bit("用户存在"));
        tcpSocket->write("exist");
    }
    else
    {
        qDebug()<<(QString::fromLocal8Bit("用户不存在"));
        tcpSocket->write("noexist");
    }
    disconnect(tcpSocket,&QTcpSocket::readyRead,this,&tcpsender::ReiceiveLand);        //解除登陆用消息接收函数
    connect(tcpSocket,&QTcpSocket::readyRead,this,&tcpsender::SelectMode);       //连接模式选择

}
