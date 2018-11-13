//2018 Jack
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <QWidget>
#include <QtNetwork>
#include "ui_parameter.h"

class TcpClient:public QWidget
{
    Q_OBJECT
public:
    TcpClient();
    virtual ~TcpClient();
    void    tcp_startlisten();
    inline qint64  get_trans_totalbyte();
    inline qint64  get_trans_receivedbyte();
private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;
    qint64 mTotalBytes;
    qint64 mBytesReceived;
    qint64 mFileNameSize;
    QString mFileName;
    QFile *mLocalfile;
    QByteArray mBuffer;
private slots:
    void    build_connection();
    void    download_progress();
    void    display_error(QAbstractSocket::SocketError );
signals:
     void valueChanged(int);
};
#endif // TCP_CLIENT_H
