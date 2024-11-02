#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    // Создаем виджеты
    QLabel *label1 = new QLabel("Введите логин:");
    QLabel *label2 = new QLabel("Введите пароль:");
    usernameLineEdit = new QLineEdit;
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password); // Скрываем пароль
    loginButton = new QPushButton("Войти");

    // Создаем вертикальный макет
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(label2);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    // Устанавливаем макет для окна
    setLayout(layout);

    // Подключаем сигнал "clicked" к слоту
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
}

void MainWindow::onLoginButtonClicked() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username == "admin" && password == "password") {
        // Если логин и пароль верны, эмитируем сигнал loginSuccess
        emit loginSuccess(username);
        this->close(); // Закрываем окно входа
    } else {
        QMessageBox::warning(this, "Ошибка входа", "Неверный логин или пароль.");
    }
}
