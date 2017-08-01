#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(tr("请输入用户名"));
    ui->lineEdit_2->setPlaceholderText(tr("请输入密码"));
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("root.db");
    if(db.open())
       qDebug() << "open database success";
    else
        qDebug() << "open database error";
    //socket=NULL;
    //if(socket == NULL)
    //{
    //   socket = new QTcpSocket();
   //    socket->connectToHost("192.168.2.111",8888);
  //  }

    //connect(socket,SIGNAL(connected()),this,SLOT(net_connected()));
}

Dialog::~Dialog()
{
    delete ui;
}


/*void insertUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("INSERT INTO dl (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
}
*/

//登录函数
void Dialog::on_pushButton_clicked()
{

    QSqlQuery query;
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    query.exec("select * from user");
    bool islogin =false;
    while(query.next()) {
        if(username==query.value(0).toString() && password==query.value(1).toString()){
            islogin =true;
            mainwindowl.show();
            this->close();
            break;
        }else islogin = false;
    }
    if(islogin == false)
    {
        QMessageBox::warning(this,tr("啊！，错了"),tr("登录失败"));
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }

    return;

}


     /*socket->write("dl",sizeof("dl"));
     //char username[20]= ui->lineEdit->text().toStdString();
     char username[20],passwd[20];
     strcpy(username,ui->lineEdit->text().toStdString().c_str());
     strcpy(passwd,ui->lineEdit_2->text().toStdString().c_str());
     socket->write(username,sizeof(username));
     socket->write(passwd,sizeof(passwd));
     char buf[10];
       if(1 == socket->read(buf,sizeof(buf)))
       {
           mainwindowl.show();
           this->close();
       }
       else
       {
             QMessageBox::warning(this,tr("啊！，错了"),tr("登录失败"));
             ui->lineEdit->clear();
             ui->lineEdit_2->clear();
       }
}*/
//注册函数
void Dialog::on_pushButton_2_clicked()
{
     QSqlQuery sql_query,query;
    QString create_sql = "create table user (username text,passwd text)";
      sql_query.prepare(create_sql); //创建表
      if(!sql_query.exec()) //查看创建表是否成功
      {
            qDebug()<<QObject::tr("Table Create failed");
          //  qDebug()<<sql_query.lastError();
      }
    QString username= ui->lineEdit->text();
    QString password= ui->lineEdit_2->text();
    query.prepare("INSERT INTO user (username, passwd) VALUES (:username, :passwd)");
    query.bindValue(":username", username);
    query.bindValue(":passwd", password);
    query.exec();
    //socket->write("zu",sizeof("zu"));
    //char username[20]= ui->lineEdit->text().toStdString();
    //char username[20],passwd[20];
    //strcpy(username,ui->lineEdit->text().toStdString().c_str());
    //strcpy(passwd,ui->lineEdit_2->text().toStdString().c_str());
    //socket->write(username,sizeof(username));
    //socket->write(passwd,sizeof(passwd));
    //char buf[10];
     // if(1 == socket->read(buf,sizeof(buf)))
      //{
          QMessageBox::warning(this,tr("恭喜你"),tr("注册成功"));
          ui->lineEdit->clear();
          ui->lineEdit_2->clear();
          ui->lineEdit->setFocus();
     // }
    //  else
      //{
       //     QMessageBox::warning(this,tr("啊！，错了"),tr("注册失败"));
      //      ui->lineEdit->clear();
     //       ui->lineEdit_2->clear();
     // }

}
