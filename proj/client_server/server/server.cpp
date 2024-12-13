#include "server.h"
#include <QDebug>
#include <QList>
#include <QTcpSocket>
#include <QHostAddress>


Server::Server(QObject *parent) : QObject(parent), tcpServer(new QTcpServer(this)) {
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);

    if (!tcpServer->listen(QHostAddress::LocalHost, 8080)) {
        qFatal("Failed to start server: %s", tcpServer->errorString().toUtf8().constData());
    } else {
        qDebug() << "Server started on port 8080";
    }
}

Server::~Server() {
    if (tcpServer->isListening()) {
        tcpServer->close();
    }
    qDeleteAll(connectedClients);
    connectedClients.clear();
    delete tcpServer;
}


void Server::relayMessage(QTcpSocket* sender, const QString& message) {
    QByteArray messageBytes = message.toUtf8(); //Convert to QByteArray before sending
    for (QTcpSocket* client : connectedClients) {
        if (client != sender && client->isOpen()) {
            client->write(messageBytes);
            client->flush();
        }
    }
}

void Server::newConnection() {
    QTcpSocket* client = tcpServer->nextPendingConnection();
    if (!client) return;
    qDebug() << "Client connected";

    connect(client, &QTcpSocket::readyRead, [client, this]() {
        QByteArray data = client->readAll();
        QString message = QString::fromLatin1(data);
        if (message.contains("exit", Qt::CaseInsensitive)) {
            client->disconnectFromHost();
            clientNames.remove(client);
            client->deleteLater();
            return;
        }
        //Relay message without modifying it.  The username should already be part of the message
        relayMessage(client, message);
    });
    connectedClients.append(client);
}
