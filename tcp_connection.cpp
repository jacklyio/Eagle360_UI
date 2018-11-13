//2018 Jack
#include "tcp_connection.h"

TcpClient::TcpClient():mTotalBytes(0),mBytesReceived(0),mFileNameSize(0){
    mTcpServer = new QTcpServer(this);
    connect(this->mTcpServer, SIGNAL(newConnection()), this, SLOT(build_connection()));

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
    QDataStream in(mTcpSocket);
    in.setVersion(QDataStream::Qt_4_6);
    QVariant mSize_t1(mBytesReceived);
    QVariant mSize_t2(mTcpSocket->bytesAvailable());
    //if(mBytesReceived <= sizeof(qint64)*2){
    if(mSize_t1.toULongLong() <= sizeof(qint64)*2){
        if((mSize_t2.toULongLong() >= sizeof(qint64)*2) && (mFileNameSize == 0)){
            in >> mTotalBytes >> mFileName;               mBytesReceived += sizeof(qint64) * 2;
           }
           if((mTcpSocket->bytesAvailable() >= mFileNameSize) && (mFileNameSize != 0)){
               in >> mFileName;
               //ui->serverStatusLabel->setText(tr(" %1 ...").arg(fileName));
               mBytesReceived += mFileNameSize;
               mLocalfile= new QFile(mFileName);
               if(!mLocalfile->open(QFile::WriteOnly)){
                   qDebug() << "open file error!";
                   return;
               }
           }
           else return;
       }
       if(mBytesReceived < mTotalBytes){
          mBytesReceived += mTcpSocket->bytesAvailable();
          mBuffer= mTcpSocket->readAll();
          mLocalfile->write(mBuffer);
          mBuffer.resize(0);
       }
    //
       //ui->serverProgressBar->setMaximum(totalBytes);
       //ui->serverProgressBar->setValue(bytesReceived);
#if 0
       if(bytesReceived == totalBytes)
       { //
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
    ui->serverStatusLabel->setText(tr("！")
    .arg(fileName));
       }
#endif
}
qint64 TcpClient::get_trans_totalbyte(){
    return this->mTotalBytes;
}
qint64 TcpClient::get_trans_receivedbyte(){
    return this->mBytesReceived;
}
void TcpClient::display_error(QAbstractSocket::SocketError ){
    qDebug() << mTcpSocket->errorString();
    mTcpSocket->close();
}

