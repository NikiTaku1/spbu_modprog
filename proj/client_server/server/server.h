#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <QByteArray>

class Server : public QObject {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void newConnection();

private:
    QTcpServer* tcpServer;
    QList<QTcpSocket*> connectedClients;
    QMap<QTcpSocket*, QString> clientNames;
    void relayMessage(QTcpSocket* sender, const QString& message); // Corrected declaration
};

#endif // SERVER_H
