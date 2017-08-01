#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QApplication>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();
    void net_connected();
    void net_connected1();
    void update_pic();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_radioButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    //视频信息套接字
    QTcpSocket *socket;
    QTimer *timer;
    char picbuf[100*1024];
    unsigned int piclen;
    //环境信息套接字，buf；
    QTcpSocket *soceket1;
   // unsigned int nextBlockSize;


};

#endif // MAINWINDOW_H
