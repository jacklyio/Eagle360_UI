//2018 Jack
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
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
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    UdpClient *mUdpClient;
    TcpClient *mTcpClient;
    //unsigned int mIP_host_num;
    //QString *mHostAddressList;
    QByteArray datagram;
};

#endif // MAINWINDOW_H
