//2018 Jack
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),datagram(CORETRONIC_MEG),datagram1(BOTTON1),datagram2(BOTTON2)
    ,datagram3(BOTTON3),datagram4(BOTTON4),datagram5(BOTTON5){
    ui->setupUi(this);
    mUdpClient = new UdpClient();
    mUdpClient->udp_getinfo();
    connect(this->mUdpClient->mTcpclient,SIGNAL(valueChanged(int ,int )),this,SLOT(change(int , int)));
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
    mUdpClient->send_databytes(datagram3);
}
void MainWindow::on_pushButton_2_clicked(){
    mUdpClient->send_databytes(datagram2);
}
void MainWindow::on_pushButton_4_clicked(){
    mUdpClient->send_databytes(datagram4);
}
void MainWindow::on_pushButton_5_clicked(){
    mUdpClient->send_databytes(datagram5);
}
void MainWindow::change(int mTotalBytes, int mBytesReceived){
    ui->progressBar->setMaximum(mTotalBytes);
    ui->progressBar->setValue(mBytesReceived);
}
