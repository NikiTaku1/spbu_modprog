#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputDialog"

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

void MainWindow::on_createProjectButton_clicked()
{
    // Open a file dialog to upload a file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project File"), "", tr("All Files (*)"));
    if (!fileName.isEmpty()) {
        // Show the local IP address
        QString localIP = getLocalIP();
        ui->ipAddressLabel->setText("Your IP: " + localIP);
    }
}

void MainWindow::on_joinProjectButton_clicked()
{
    bool ok;
    QString ipAddress = QInputDialog::getText(this, tr("Join Project"),
                                              tr("Enter IP Address:"),
                                              QLineEdit::Normal, "", &ok);
    if (ok && !ipAddress.isEmpty()) {
        // Here you would generally verify the IP and connect to the project.
        // Implement connection logic, for now, we simulate a successful connection.
        QMessageBox::information(this, tr("Connection Status"),
                                 tr("Successful connection"),
                                 QMessageBox::Ok);
    }
}

QString MainWindow::getLocalIP()
{
    // Get local IP address
    QString ipAddress;
    foreach(const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.toIPv4Address()) {
            ipAddress = address.toString();
            break;  // You can change the logic if you want specific IP address
        }
    }
    return ipAddress;
}
