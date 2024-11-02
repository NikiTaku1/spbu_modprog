#include "newwindow.h"
#include <QtWidgets>

NewWindow::NewWindow(QWidget *parent) : QWidget(parent) {
    label = new QLabel("Добро пожаловать!");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);

    setWindowTitle("Главное окно");
    resize(300, 100);
}

void NewWindow::onLoginSuccess(QString username) {
    label->setText("Добро пожаловать, " + username + "!");

    this->show();
}
