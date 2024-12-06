#include <QTcpServer>
#include <QObject>
#include <QMap>
#include <QFile>
#include <QDataStream>
#include <QHash>
#include <QList>
#include <QString>

class Server : public QObject {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void newConnection();
    void handleClient(QTcpSocket* socket);
    void relayMessage(QTcpSocket* sender, QByteArray message);

private:
    QTcpServer* tcpServer;
    QHash<QTcpSocket*, QString> clientNames; // Map sockets to client names
    QList<QTcpSocket*> connectedClients;
    QByteArray getAllFilesData(const QString& directory);
};
