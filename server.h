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
    explicit Server(QObject *parent = nullptr , int port = 8080);
    bool start();

signals:

private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer server;
    int port;

};

#endif // SERVER_H
