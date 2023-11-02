#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{


    connect(&server , &QTcpServer::newConnection , this , &Server::newConnection);


}


bool Server::start(int port)
{
    if(!server.listen(QHostAddress::Any , port)){
        qDebug() << server.errorString();
        return false;
    }

    return true;
}

void Server::send(QVariantMap data, QTcpSocket *socket)
{

    QJsonDocument document = QJsonDocument::fromVariant(data);
    socket->write(document.toJson());
}


void Server::newConnection()
{
    QTcpSocket* socket = server.nextPendingConnection();

    connect(socket , &QTcpSocket::disconnected , this ,&Server::disconnected);
    connect(socket , &QTcpSocket::readyRead , this ,&Server::readyRead);



}


void Server::disconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());


}

void Server::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    QJsonDocument document = QJsonDocument::fromJson(socket->readAll());

    emit data_recived(document , socket);

}


