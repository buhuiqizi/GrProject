#include "tcpreceiver.h"
#include "userinformation.h"
#include "friendlistwindow.h"
#include "landwindow.h"

extern userinformation *user;
extern landwindow *land;
extern QList<userinformation *> *friendlist;
//landwindow land;
//QTcpSocket *tcpSocket;

QByteArray m_buffer;

tcpreceiver::tcpreceiver()
{
    tcpClient = new QTcpSocket(NULL);

    qDebug()<<QString::fromLocal8Bit("开始连接");
    tcpClient->connectToHost(QHostAddress("192.168.56.1"),8000);
    if (tcpClient->waitForConnected(1000))
    {
        qDebug()<<QString::fromLocal8Bit("连接成功");
    }
    //connect(tcpSocket,SIGNAL(connected()),this,SLOT(tcpreceiver::chenggong()));
    //connect(tcpSocket,SIGNAL(error()),this,SLOT(tcpreceiver::shibai()));

    connect(tcpClient,&QTcpSocket::readyRead,this,&tcpreceiver::ReceiveMessage);        //待修改？

}

void tcpreceiver::SendMode(int mode)
{
    switch (mode) {
    case 0:

        break;
    case 1:
        connect(tcpClient,&QTcpSocket::readyRead,this,&tcpreceiver::MessageReady);
        qDebug()<<(QString::fromLocal8Bit("绑定MessageReady"));
        break;
    case 2:

        break;
    case 3:

        break;
    default:
        break;
    }

    tcpClient->write("1");
    qDebug()<<(QString::fromLocal8Bit("模式已经发送:1"));

}

void tcpreceiver::SendMessage(ushort type_id)      //用来发送确认信息
{
    QByteArray allByte;
    QDataStream out(&allByte,QIODevice::WriteOnly);        //数据流
    out.setByteOrder(QDataStream::BigEndian);               //设置大端模式
    out<<ushort(0)<<ushort(0);                             //包头占位，为了测量完整大小
    out.device()->seek(0);                                  //回到数据开头
    ushort len = (ushort)(allByte.size());                 //计算出完整大小
    out<<type_id<<len;                                      //将数据类型和长度插入数据包
    tcpClient->write(allByte);                             //发送数据
}

void tcpreceiver::SendMessage(ushort type_id,QByteArray &sendByte)      //数据发送函数
{
    QByteArray allByte;
    QDataStream out(&allByte,QIODevice::WriteOnly);        //数据流
    out.setByteOrder(QDataStream::BigEndian);               //设置大端模式
    out<<ushort(0)<<ushort(0)<<sendByte;                              //包头占位，为了测量完整大小
    out.device()->seek(0);                                  //回到数据开头
    ushort len = (ushort)(allByte.size());                 //计算出完整大小
    out<<type_id<<len;                                      //将数据类型和长度插入数据包
    tcpClient->write(allByte);                             //发送数据
}

void tcpreceiver::ReceiveMessage()
{
    //缓冲区没有数据，直接无视
    if( tcpClient->bytesAvailable() <= 0 )
    {
        return;
    }
    //临时获得从缓存区取出来的数据，但是不确定每次取出来的是多少。
    QByteArray buffer;
    //如果是信号readyRead触发的，使用readAll时会一次把这一次可用的数据全总读取出来
    //所以使用while(m_tcpClient->bytesAvailable())意义不大，其实只执行一次。
    buffer = tcpClient->readAll();

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


            case 11:         //登陆是否成功信号
            {
                QMessageBox::information(NULL,"(+_+)?",QString::fromLocal8Bit("登陆失败!"));
            }
            break;

            case 21:
            {
                QMessageBox::information(NULL,"(*^_^*)",QString::fromLocal8Bit("登陆成功!"));
                land->accept();
            }
            break;

            case 12:         //注册是否成功信号
            {
                qDebug()<<QString::fromLocal8Bit("注册失败");
            }
            break;

            case 22:
            {
                qDebug()<<QString::fromLocal8Bit("注册成功");
            }
            break;

            case 13:            //接收用户的详细信息
            {
                QByteArray tmpdata;
                packet >> tmpdata;
                tmpdata=tmpdata.left(mesg_len);
                user=user->DeSerializable(tmpdata);

//                //这里我把所有的数据都缓存在内存中，因为我们传输的文件不大，最大才几M;
//                //大家可以这里收到一个完整的数据包，就往文件里面写入，即使保存。
//                m_recvData.append(tmpdata);
//                //这个可以最后拿来校验文件是否传完，或者是否传的完整。
//                m_checkSize += tmpdata.size();
//                //打印提示，或者可以连到进度条上面。
//                emit sig_displayMesg(QString(”recv: %1”).arg(m_checkSize));
            }
            break;


            case 23:            //接收好友的详细信息
            {
                userinformation *frieninf=new userinformation();
                QByteArray tmpdata;
                packet >> tmpdata;
                tmpdata=tmpdata.left(mesg_len);
                frieninf=frieninf->DeSerializable(tmpdata);
                friendlist->append(frieninf);
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

void tcpreceiver::DisConnect()
{
    tcpClient->disconnectFromHost();
    tcpClient->close();
    tcpClient=NULL;
}

void tcpreceiver::chenggong()
{
    qDebug()<<QString::fromLocal8Bit("连接成功");
}

void tcpreceiver::shibai()
{
    qDebug()<<QString::fromLocal8Bit("连接失败");
}

void tcpreceiver::MessageReady()
{
    QByteArray temp=tcpClient->readAll();
    qDebug()<<(QString::fromLocal8Bit("接收到确认信息"));
    SendUser();
    disconnect(tcpClient,&QTcpSocket::readyRead,this,&tcpreceiver::MessageReady);       //解除确认函数
    connect(tcpClient,&QTcpSocket::readyRead,this,&tcpreceiver::isLand);
}

void tcpreceiver::SendUser()
{
    QByteArray temp=user->Serializable(*user);
    qDebug()<<(QString::fromLocal8Bit("发送用户名和密码"));
    qDebug()<<user->Getusername();
    qDebug()<<user->Getpassword();
    tcpClient->write(temp);
}

void tcpreceiver::isLand()
{
    QByteArray temp=tcpClient->readAll();
    QString str=temp;
    if(str.compare(QString::fromLocal8Bit("exist")) == 0)
    qDebug()<<QString::fromLocal8Bit("登陆成功");
    else
    qDebug()<<QString::fromLocal8Bit("登陆失败");
}
