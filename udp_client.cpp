//2018 Jack
#include "udp_client.h"

UdpClient::UdpClient():mIP_host_num(0){
    uSocket = new QUdpSocket(this);
    //uSocket->bind(QHostAddress::LocalHost, PORT);
    mIfaces = QNetworkInterface::allInterfaces();
    mTcpclient = new TcpClient();
    connect(this->uSocket, SIGNAL(readyRead()), this, SLOT(process_pending_datagram()));
}

UdpClient::~UdpClient(){
    disconnect(this->uSocket, SIGNAL(readyRead()), this, SLOT(process_pending_datagram()));
    delete [] mHostAddressList;
    delete uSocket;
}
bool UdpClient::find_host_num(unsigned int *i){
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()){
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            if(!QString(address.toString()).isEmpty()){
            (*i)+=1;
            }
    }
    if((*i)==0)
        return false;
    else
        return true;
}
void UdpClient::find_host_list(QString *list){
    unsigned int temp_count = 0;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()){
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            if(!QString(address.toString()).isEmpty()){
            list[temp_count]=address.toString();
            temp_count++;
            }
    }
}
void UdpClient::udp_broadcast(const QByteArray datagram){
    for (int i = 0; i < mIfaces.size(); i++){
        QList<QNetworkAddressEntry> addrs = mIfaces[i].addressEntries();
        for (int j = 0; j < addrs.size(); j++)
            if ((addrs[j].ip().protocol() == QAbstractSocket::IPv4Protocol) && (addrs[j].broadcast().toString() != "")){
                this->uSocket->writeDatagram(datagram.data(), datagram.length(), addrs[j].broadcast(), quint16(PORT));
            }
    }
}
//e93
void UdpClient::process_pending_datagram(){
    while(this->uSocket->hasPendingDatagrams()){
        QByteArray datagram;
        QVariant mSize(this->uSocket->pendingDatagramSize());
        datagram.resize(mSize.toInt());
        //this->uSocket->readDatagram(datagram.data(), datagram.size());
        if(this->uSocket->readDatagram(datagram.data(), datagram.size())!=-1){
        qDebug() << "Jack: " << datagram.data();
        qDebug() << "Start Listen! ";
        mTcpclient->tcp_startlisten();
        }
        else{
            qDebug()<<"Can't get receive ACK";
            exit(0);
        }
    }
}
void UdpClient::udp_getinfo(){
    if(this->find_host_num(&mIP_host_num)){
    mHostAddressList = new QString[mIP_host_num];
    this->find_host_list(mHostAddressList);
    qDebug()<<"Success get network link";
    }
    else{
        qDebug()<<"Could not get network link";
        exit(0);
    }
}
void UdpClient::send_databytes(const QByteArray datagram){

    if(this->mTcpclient->write(datagram)){
        qDebug()<<"Success Send!";
    }
    else
        qDebug()<<"Fail Send!";

}
void UdpClient::receive_databytes(QByteArray *datagram){
    this->mTcpclient->read(datagram);
}
