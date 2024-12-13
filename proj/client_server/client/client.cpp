#include "client.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QInputDialog>

Client::Client(QWidget *parent) : QObject(parent) {
    // Create UI elements.
    textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    lineEdit = new QLineEdit();
    sendButton = new QPushButton("Send");
    usernameLabel = new QLabel();

    // Create the layout.
    layout = new QVBoxLayout();
    layout->addWidget(usernameLabel);
    layout->addWidget(textEdit);
    layout->addWidget(lineEdit);
    layout->addWidget(sendButton);
    QWidget* window = new QWidget(parent);
    window->setLayout(layout);
    window->show();

    // Crucial: Use a timer to check for connection status.
    connectTimer = new QTimer(this);
    connect(connectTimer, &QTimer::timeout, this, [this](){
        if(socket.state() != QAbstractSocket::ConnectedState){
            QMessageBox::warning(nullptr, "Connection Error", "Failed to connect to server.");
            socket.close();
            deleteLater(); // Important: Delete the client object when connection fails
        }
    });
    connectTimer->start(2000); // Check connection every 2 seconds.

    //Connect signals and slots.
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(&socket, &QTcpSocket::errorOccurred, this, &Client::errorOccurred);
    connect(sendButton, &QPushButton::clicked, this, &Client::sendMessage);

    //Connect to server.
    socket.connectToHost("127.0.0.1", 8080);

    username = getUsernameFromUser();
    updateUsernameLabel();
}

Client::~Client() {
    socket.close();
    delete textEdit;
    delete lineEdit;
    delete sendButton;
    delete layout;
}

QString Client::getUsernameFromUser(){
    bool ok;
    QString username = QInputDialog::getText(nullptr, "Username", "Enter your username:", QLineEdit::Normal, "", &ok);
    if(ok && !username.isEmpty()){
        return username;
    }else{
        return "Anonymous"; // Provide a default if username is empty or input canceled
    }
}

void Client::connected() {
    qDebug() << "Connected to server";
    textEdit->append("Connected to server");
    updateUsernameLabel();
    // Important: Stop the connection timer once connected.
    connectTimer->stop();

    if (!username.isEmpty()) {
        socket.write((username + ":" + "Connected").toUtf8());
    }
}

void Client::updateUsernameLabel(){
    usernameLabel->setText("Username: " + (username.isEmpty() ? "Anonymous" : username));
}

void Client::disconnected() {
    qDebug() << "Disconnected from server";
    textEdit->append("Disconnected from server");
    updateUsernameLabel();
}

void Client::readyRead() {
    QByteArray data = socket.readAll();
    QString message = QString::fromLatin1(data);
    textEdit->append(message); // Display the message
}

void Client::errorOccurred(QAbstractSocket::SocketError socketError) {
    QString errorString = socket.errorString();
    qDebug() << "Socket error:" << errorString;
    QMessageBox::critical(nullptr, "Error", "Socket error:" + errorString);
    socket.close();
}

void Client::sendMessage() {
    QString message = lineEdit->text();
    if (message.isEmpty()) return;

    if (message == "exit") {
        socket.disconnectFromHost();
        return;
    }

    QWidget* parentWidget = qobject_cast<QWidget*>(this->parent());
    if (socket.state() == QAbstractSocket::ConnectedState) {
        socket.write((username + ": " + message).toUtf8()); // Send message without username prefix
        socket.flush();
        lineEdit->clear();
        textEdit->append((username + ": " + message)); //Append message directly
    } else {
        if (parentWidget)
            QMessageBox::warning(parentWidget, "Connection Error", "Not connected to the server.");
        else
            QMessageBox::warning(nullptr, "Connection Error", "Not connected to the server.");
    }
}
