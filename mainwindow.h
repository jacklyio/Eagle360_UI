//2018 Jack
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QProgressBar>
#include "ui_parameter.h"
#include "udp_client.h"
#include "tcp_connection.h"

namespace Ui {
class MainWindow;
class UdpClient;
class TcpClient;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void find_host(unsigned int *);
    void find_host(QString *);
    void setProgress(int value);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    //void on_progressBar_valueChanged();
    void change(int , int );

private:
    int i = 0;
    Ui::MainWindow *ui;
    //QProgressBar *mProgressBar;
    UdpClient *mUdpClient;
    //unsigned int mIP_host_num;
    //QString *mHostAddressList;
    QByteArray datagram,datagram1,datagram2 ,datagram3 , datagram4, datagram5;
};

#endif // MAINWINDOW_H
