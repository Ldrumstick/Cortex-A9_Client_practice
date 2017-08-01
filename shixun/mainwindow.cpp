#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include "stdio.h"
#include <QThread>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ipEdit->setText("192.168.2.111");
    ui->portEdit->setText("8888");
    socket = NULL;
    soceket1 =NULL;
    timer = NULL;
   // nextBlockSize=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_pic()
{
    //2、发请求命令给server
    char buf[10] = "pic";
    char headbuf[307200];
     int res =socket->write(buf,sizeof(buf));
    if(res == -1)
    {
        qDebug()<<"read pic error  l";
    }
    //3、接收服务器发送过来的视频数据
    memset(headbuf,0,sizeof(headbuf)); //clear headbuf
    if(socket->bytesAvailable()<sizeof(headbuf))
        return;
    int ret = socket->read(headbuf,sizeof(headbuf));//read socket
    qDebug()<<"ret="<<ret;
    if(ret == -1)
    {
        qDebug()<<"read piclen error";
        socket->close();
        timer->stop();
        socket = NULL;
        timer = NULL;
    }
     qDebug()<<"headbuf:"<<headbuf;
    //5、显示视频
    QPixmap pixmap;
    pixmap.loadFromData((uchar *)headbuf,307200,"JPEG");
    ui->label->setPixmap(pixmap);
}

void MainWindow::net_connected()
{
    timer->start(240);
    qDebug()<<"net_connected success";

}
void MainWindow::net_connected1()
{
    qDebug()<<"net_connected success";
}

void MainWindow::on_btnStart_clicked()
{
    if(socket == NULL)
    {
        socket = new QTcpSocket();
        int port = ui->portEdit->text().toInt();
        socket->connectToHost(ui->ipEdit->text(),port);

    }

    if(timer == NULL)
    {
        timer = new QTimer();
    }
    connect(socket,SIGNAL(connected()),this,SLOT(net_connected()));
    connect(timer,SIGNAL(timeout()),this,SLOT(update_pic()));

}

//获取环境信息
void MainWindow::on_pushButton_8_clicked()
{

    if(soceket1 == NULL)
    {
        soceket1 = new QTcpSocket();
        int port = ui->portEdit->text().toInt();
        soceket1->connectToHost(ui->ipEdit->text(),port);

        char hjbuf[10] ="start";
            int ret;
            if((ret =soceket1->write(hjbuf,sizeof(hjbuf)))==-1)
            {
                    qDebug()<<"命令发送失败";
            }

    }
    connect(soceket1,SIGNAL(connected()),this,SLOT(net_connected1()));

}



//风扇开
void MainWindow::on_pushButton_5_clicked()
{

     char hjbuf[10] ="fsk";
     soceket1->write(hjbuf,sizeof(hjbuf));
         QMessageBox::warning(this,tr("恭喜你"),tr("风扇打开了"));
}
//风扇关闭
void MainWindow::on_pushButton_6_clicked()
{
    char hjbuf[10] ="fsg";
    soceket1->write(hjbuf,sizeof(hjbuf));
        QMessageBox::warning(this,tr("恭喜你"),tr("风扇关闭了"));
}
//蜂鸣器开
void MainWindow::on_pushButton_clicked()
{
    char hjbuf[10] ="fmqk";
    soceket1->write(hjbuf,sizeof(hjbuf));
        QMessageBox::warning(this,tr("恭喜你"),tr("蜂鸣器打开"));

}
//蜂鸣器关
void MainWindow::on_pushButton_3_clicked()
{
    char hjbuf[10] ="fmqg";
    soceket1->write(hjbuf,sizeof(hjbuf));
        QMessageBox::warning(this,tr("恭喜你"),tr("蜂鸣器关闭"));

}
//led灯开
void MainWindow::on_pushButton_2_clicked()
{
    char hjbuf[10] ="ledk";
    soceket1->write(hjbuf,sizeof(hjbuf));
        QMessageBox::warning(this,tr("恭喜你"),tr("LED灯打开了"));
}
//led灯关
void MainWindow::on_pushButton_4_clicked()
{
    char hjbuf[10] ="ledg";
    soceket1->write(hjbuf,sizeof(hjbuf));
        QMessageBox::warning(this,tr("恭喜你"),tr("LED灯关闭了"));

}
//视频关
void MainWindow::on_pushButton_7_clicked()
{
  char hjbuf[10] ="spg";
  socket->write(hjbuf,sizeof(hjbuf));

      QMessageBox::warning(this,tr("恭喜你"),tr("视频关闭成功"));
      timer->stop();
      socket->close();
      socket = NULL;
  }

void MainWindow::on_pushButton_9_clicked()
{


    char hjbuf[10] ="start";
    char wd[10];
    char sd[10];
    char gzd[10];
    char info[30];
    int ret;
    if((ret =soceket1->write(hjbuf,sizeof(hjbuf)))==-1)
    {
            qDebug()<<"命令发送失败";
    }
    memset(info,0,sizeof(info));
    if(soceket1->bytesAvailable()<sizeof(info))
        return;
    int res;
    if((res=soceket1->read(info,sizeof(info)))<0){
       qDebug()<<"获取失败";
       qDebug()<<soceket1->errorString();
    }
    qDebug()<<res;
    qDebug()<<info;

    strncpy(wd,info,5);
    strncpy(sd,info+10,10);
    strncpy(gzd,info+20,4);


    ui->label_5->setText(wd);
    ui->label_7->setText(sd);
    ui->label_9->setText(gzd);


}

