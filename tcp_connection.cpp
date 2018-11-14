//2018 Jack
#include "tcp_connection.h"

TcpClient::TcpClient():mTotalBytes(0),mBytesReceived(0),mFileNameSize(0),mFileName("aaa.mp4"){
    mTcpServer = new QTcpServer(this);
    connect(this->mTcpServer, SIGNAL(newConnection()), this, SLOT(build_connection()));

    mLocalfile= new QFile(mFileName);
    if(!mLocalfile->open(QFile::WriteOnly)){
         qDebug() << "open file error!";
         return;
    }

}
TcpClient::~TcpClient(){
    delete mTcpServer;
    delete mTcpSocket;
    delete mLocalfile;
}
void TcpClient::tcp_startlisten(){
    if(!this->mTcpServer->listen(QHostAddress::AnyIPv4,quint16(PORT))){
       qDebug() << this->mTcpServer->errorString();
       close();
       return;
    }
    qDebug()<<"Start listen TCP";
}
void TcpClient::build_connection(){
    mTcpSocket = mTcpServer->nextPendingConnection();
    connect(mTcpSocket,SIGNAL(readyRead()),this,SLOT(download_progress()));
    connect(mTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(display_error(QAbstractSocket::SocketError)));
    mTcpServer->close();
    if(mTcpSocket->state() == QAbstractSocket::UnconnectedState){
        mTcpSocket->waitForConnected();
    }
    qDebug()<<"Connection Builded";
}
void TcpClient::download_progress(){
#if 0
    QDataStream in(mTcpSocket);
    QVariant tempQ(sizeof(qint64)*2);
    in.setVersion(QDataStream::Qt_4_7);

       if(mBytesReceived <= tempQ.toLongLong())
       {
           qDebug()<<"Jack_1";
           if((mTcpSocket->bytesAvailable() >= tempQ.toLongLong())&&(mFileNameSize == 0)){
               in >> mTotalBytes >> mFileNameSize;
               qDebug()<<"mFileNameSize :"<<mFileNameSize;
               qDebug()<<"mTotalBytes: "<<mTotalBytes;
               qDebug()<<"bytesAvailable: "<<mTcpSocket->bytesAvailable();
               qDebug()<<"sizeof: "<<sizeof(qint64)*2;
               mBytesReceived += sizeof(qint64) * 2;
               qDebug()<<"Jack_1_1";
           }
           if((mTcpSocket->bytesAvailable() >= mFileNameSize)&&(mFileNameSize != 0)){
               qDebug()<<"Jack_1_2";
               in >> mFileName;
               mBytesReceived += mFileNameSize;
               mLocalfile= new QFile(mFileName);
               if(!mLocalfile->open(QFile::WriteOnly)){
                    qDebug() << "open file error!";
                    return;
               }
           }
           else{
               qDebug()<<"Jack_1_3";
               return;
           }
       }
       qDebug()<<"Jack_3";
       qDebug()<<"Jack_3_"<<mBytesReceived;
       qDebug()<<"Jack_3_"<<mTotalBytes;
#endif
       //if(mBytesReceived < mTotalBytes)
       if(mTcpSocket->bytesAvailable() >0 ){
          qDebug()<<"Jack_2";
          mBytesReceived += mTcpSocket->bytesAvailable();
          mBuffer= mTcpSocket->readAll();
          mLocalfile->write(mBuffer);
          mBuffer.resize(0);
       }
       //ui->serverProgressBar->setMaximum(totalBytes);
       //ui->serverProgressBar->setValue(bytesReceived);
       else
        mLocalfile->close();
#if 0
       if(mBytesReceived == mTotalBytes)
       {
        //tcpServerConnection->close();
        mLocalfile->close();
        //ui->startButton->setEnabled(true);
        //ui->serverStatusLabel->setText(tr("接收文件 %1 成功！").arg(fileName));
       }
#endif
}
void TcpClient::display_error(QAbstractSocket::SocketError ){
    qDebug() << mTcpSocket->errorString();
    mTcpSocket->close();
}
bool TcpClient::write(const QByteArray datagram){
    qDebug()<<"Jack__"<<datagram;
    if(this->mTcpSocket->state() == QAbstractSocket::ConnectedState){
        //this->mTcpSocket->write(IntToArray(datagram.size()));
        this->mTcpSocket->write(datagram); //write the data itself
        return this->mTcpSocket->waitForBytesWritten();
    }
    else
        return false;
}
bool TcpClient::read(QByteArray *datagram){
    datagram = nullptr;
    return false;
}
