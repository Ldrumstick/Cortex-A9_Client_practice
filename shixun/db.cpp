#include "db.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
//创建数据库并打开
void user_opendb(void)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("root.db");
    if(db.open())
    qDebug() << "open database success";
    else
    qDebug() << "open database error";
}
int user_login(int rws)
{
    read(rws,buf,20);
    read(rws,buf1,20);
    QSqlQuery query;
    QString username;
    QString password;
    strncpy(usernmae,buf,sizeof(buf));
    strncpy(password,buf1,sizeof(buf1));
    query.exec("select * from user");
    while(query.next()) {
            if(username==query.value(0).toString() && password==query.value(1).toString()){
              int buf3=1;
              write(rws,buf3,4);
            }

        }else
    {
        int buf3=0;
        write(rws,buf3,4);//返回一个登录失败
    }

}
int user_logup(int rws)
{
    read(rws,buf,20);
    read(rws,buf1,20);
    QSqlQuery sql_query,query;
       QString create_sql = "create table user (username text,password text)";
          sql_query.prepare(create_sql); //创建表
         QString username;
         QString password;
         strncpy(usernmae,buf,sizeof(buf));
         strncpy(password,buf1,sizeof(buf1));
          if(!sql_query.exec()) //查看创建表是否成功
          {
                qDebug()<<QObject::tr("Table Create failed");
                //qDebug()<<sql_query.lastError();
          }

        query.prepare("INSERT INTO user (username, passwd) VALUES (:username, :password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.exec();
}
