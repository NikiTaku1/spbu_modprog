#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString UserName = ui->lineEdit_User_Name->text();
    QString Password = ui->lineEdit_Password->text();
    if (UserName == "admin" && Password == "1234")
    {
        QMessageBox::information(this, "Qt Login", "Login Successful");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();

    }
    else
    {
        QMessageBox::warning(this, "Qt Login", "Incorrect Information");
    }
}


void MainWindow::on_pushButton_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Qt Login", "Are you sure you want to close the app?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

