#include <QApplication>
#include "mainwindow/mainwindow.h"
#include "newwindow/newwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создаем окно входа
    MainWindow *mainWindow = new MainWindow;

    // Создаем главное окно
    NewWindow *newWindow = new NewWindow;

    // Подключаем сигнал loginSuccess к слоту onLoginSuccess
    QObject::connect(mainWindow, &MainWindow::loginSuccess, newWindow, &NewWindow::onLoginSuccess);

    // Отображаем окно входа
    mainWindow->show();

    return app.exec();
}
