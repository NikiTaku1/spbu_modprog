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
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

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
    void updateUsernameLabel();

private:
    QTcpSocket socket;
    QTextEdit* textEdit;
    QLineEdit* lineEdit;
    QPushButton* sendButton;
    QVBoxLayout* layout;
    QString username;
    QLabel* usernameLabel;
    QTimer* connectTimer;
};

#endif // CLIENT_H
