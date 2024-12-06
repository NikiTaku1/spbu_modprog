#include "server.h"
#include <QDebug>
#include <QList>
#include <QTcpSocket>


Server::Server(QObject *parent) : QObject(parent) {}

Server::~Server() {
    tcpServer->close();
    delete tcpServer;
}

void Server::newConnection() {
    QTcpSocket* client = tcpServer->nextPendingConnection();
    if (!client) {
        qWarning() << "Failed to get client socket";
        return;
    }
    qDebug() << "Client connected";

    connect(client, &QTcpSocket::readyRead, [client, this]() {
        QByteArray data = client->readAll();
        QString message = QString::fromLatin1(data);
        QString username = clientNames[client];

        if(username.isEmpty()){
            QStringList parts = message.split(":", Qt::SkipEmptyParts);
            if(parts.size() == 2){
                QString newUsername = parts[0];
                clientNames[client] = newUsername;
                qDebug() << "Username registered: " << newUsername;
            }else{
                qDebug() << "Invalid username registration message: " << message;
                client->close();
                return;
            }

        }else{

            if (message.contains("exit", Qt::CaseInsensitive)) {
                client->disconnectFromHost();
                client->deleteLater();
                clientNames.remove(client);
                return;
            }
            qDebug() << username << ": " << message;

            // Relay the message to other clients
            relayMessage(client, (username + ": " + message).toUtf8());
        }
    });

    connect(client, &QTcpSocket::disconnected, [client, this]() {
        qDebug() << "Client disconnected";
        connectedClients.removeAll(client);
        clientNames.remove(client);
        client->deleteLater();
    });

    connect(client, &QTcpSocket::errorOccurred, [client, this](QAbstractSocket::SocketError error) {
        qDebug() << "Client socket error:" << client->errorString();
    });

    connectedClients.append(client);
}

void Server::relayMessage(QTcpSocket* sender, QByteArray message) {
    for (QTcpSocket* client : connectedClients) {
        if (client != sender && client->isOpen()) {
            client->write(message);
            client->flush();
        }
    }
}

QByteArray Server::getAllFilesData(const QString& directory){
    return QByteArray(); //This method is not needed
}
