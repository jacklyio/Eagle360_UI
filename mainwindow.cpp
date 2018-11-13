//2018 Jack
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),datagram(CORETRONIC_MEG)
{
    ui->setupUi(this);
    mUdpClient = new UdpClient();
    mUdpClient->udp_getinfo();
}
MainWindow::~MainWindow(){
    delete ui;
    delete mUdpClient;
}
void MainWindow::on_pushButton_clicked(){
    mUdpClient->udp_broadcast(datagram);
    //mTcpClient->tcp_startlisten();
}
void MainWindow::on_pushButton_3_clicked(){
}
void MainWindow::on_pushButton_2_clicked(){
}
void MainWindow::on_pushButton_4_clicked(){
}
void MainWindow::on_pushButton_5_clicked(){
}
