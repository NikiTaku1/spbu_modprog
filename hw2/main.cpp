#include <QApplication>
#include "mainwindow/mainwindow.h"
#include "newwindow/newwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow *mainWindow = new MainWindow;

    NewWindow *newWindow = new NewWindow;

    QObject::connect(mainWindow, &MainWindow::loginSuccess, newWindow, &NewWindow::onLoginSuccess);

    mainWindow->show();

    return app.exec();
}
