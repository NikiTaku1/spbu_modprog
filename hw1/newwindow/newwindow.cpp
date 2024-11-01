#include "newwindow.h"
#include <QtWidgets>

NewWindow::NewWindow(QWidget *parent) : QWidget(parent) {
    // Создаем виджет для отображения текста
    label = new QLabel("Вы успешно вошли!");

    // Создаем вертикальный макет
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    // Устанавливаем макет для окна
    setLayout(layout);

    // Настройка окна
    setWindowTitle("Новое окно");
    resize(300, 100);
}

