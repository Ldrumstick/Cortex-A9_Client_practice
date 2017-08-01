#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <mainwindow.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    MainWindow mainwindowl;
private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
      QTcpSocket *socket;
};

#endif // DIALOG_H
