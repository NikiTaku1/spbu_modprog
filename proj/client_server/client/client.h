#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel> // Add this line to include QLabel

QT_BEGIN_NAMESPACE
class QTextEdit;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QLabel; // Add this line to forward declare QLabel
QT_END_NAMESPACE

class Client : public QObject {
    Q_OBJECT
public:
    Client(QWidget *parent = nullptr);
    ~Client();
    QString getUsernameFromUser();

private slots:
    void connected();
    void disconnected();
    void readyRead();
    void errorOccurred(QAbstractSocket::SocketError socketError);
    void sendMessage();
    void updateUsernameLabel(); // Added this slot

private:
    QTcpSocket socket;
    QTextEdit* textEdit;
    QLineEdit* lineEdit;
    QPushButton* sendButton;
    QVBoxLayout* layout;
    QString username;
    QLabel* usernameLabel; // Add this line to declare usernameLabel
};

#endif // CLIENT_H
