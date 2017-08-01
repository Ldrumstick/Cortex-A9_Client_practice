#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

class db
{
public:
    db();
     void user_opendb(void);
     int user_login(int rws);
     int user_logup(int rws);
};


#endif // DB_H
