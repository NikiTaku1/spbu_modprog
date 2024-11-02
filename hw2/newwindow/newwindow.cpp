#include "newwindow.h"
#include <QtWidgets>

NewWindow::NewWindow(QWidget *parent) : QWidget(parent) {
    // Создаем виджет для отображения текста
    label = new QLabel("Добро пожаловать!");

    // Создаем вертикальный макет
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    // Устанавливаем макет для окна
    setLayout(layout);

    // Настройка окна
    setWindowTitle("Главное окно");
    resize(300, 100);
}

void NewWindow::onLoginSuccess(QString username) {
    // Обновляем текст метки после успешного входа
    label->setText("Добро пожаловать, " + username + "!");

    // Отображаем главное окно
    this->show();
}
