#include "server.h"

Server::Server(QObject *parent , int port)
    : QObject{parent}
{

    this->port = port;

    connect(&server , &QTcpServer::newConnection , this , &Server::newConnection);


}


bool Server::start()
{
    if(!server.listen(QHostAddress::Any , this->port)){
        qDebug() << server.errorString();
        return false;
    }

    return true;
}


void Server::newConnection()
{
    QTcpSocket* socket = server.nextPendingConnection();

    connect(socket , &QTcpSocket::disconnected , this ,&Server::disconnected);
    connect(socket , &QTcpSocket::readyRead , this ,&Server::readyRead);

    qDebug() << "Connected " << socket;


}


void Server::disconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "Disconnected " << socket;


}

void Server::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "ReadyRead " << socket;


}


