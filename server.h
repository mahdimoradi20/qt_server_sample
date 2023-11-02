#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include<QTcpServer>
#include<QTcpSocket>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>

#include<QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    bool start(int port);
    void send(QVariantMap data , QTcpSocket* socket);

signals:
    void data_recived(QJsonDocument data , QTcpSocket *socket);
private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer server;

};

#endif // SERVER_H
