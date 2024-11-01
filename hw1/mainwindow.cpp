#include "mainwindow.h"
#include <QtWidgets>

class NewWindow : public QWidget {
    Q_OBJECT

public:
    NewWindow(QWidget *parent = nullptr) : QWidget(parent) {
        QLabel *label = new QLabel("Вы успешно вошли!");

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(label);


        setLayout(layout);

        setWindowTitle("Новое окно");
        resize(900, 600);
    }
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QLabel *label1 = new QLabel("Введите логин:");
    QLabel *label2 = new QLabel("Введите пароль:");
    usernameLineEdit = new QLineEdit;
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Войти");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(label2);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    setLayout(layout);

    resize(400, 300);

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
}

MainWindow::~MainWindow() {
    delete usernameLineEdit;
    delete passwordLineEdit;
    delete loginButton;
}

void MainWindow::onLoginButtonClicked() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username == "admin" && password == "password") {
        NewWindow *newWindow = new NewWindow;
        newWindow->show();

        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка входа", "Неверный логин или пароль.");
    }
}
#include "mainwindow.moc"
