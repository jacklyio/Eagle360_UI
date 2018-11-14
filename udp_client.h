//2018 Jack
#ifndef UDP_CLIENT_BROCAST_H
#define UDP_CLIENT_BROCAST_H
#include <QWidget>
#include <QtNetwork>
#include "ui_parameter.h"
#include "tcp_connection.h"
#include <QTime>

class UdpClient : public QWidget
{
    Q_OBJECT
public:
    UdpClient();
    virtual ~UdpClient();
    QUdpSocket     *uSocket;
    TcpClient      *mTcpclient;
    void udp_broadcast(const QByteArray );
    void udp_getinfo();
    void send_databytes(const QByteArray );
    void receive_databytes(QByteArray *);
private:
    bool find_host_num(unsigned int *);
    void find_host_list(QString *);
    QList<QNetworkInterface> mIfaces;
    unsigned int mIP_host_num;
    QString *mHostAddressList;
    QByteArray datagram;
private slots:
    void process_pending_datagram();
};

#endif // UDP_CLIENT_BROCAST_H



