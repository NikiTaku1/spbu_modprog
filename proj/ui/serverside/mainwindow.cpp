#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_databaseButton_clicked()
{
    openDatabase();
}

void MainWindow::on_activeIpsButton_clicked()
{
    openActiveIps();
}

void MainWindow::openDatabase()
{
    // Specify the path to your CSV file
    QString filePath = "C:\\Users\\Zver\\Desktop\\uni\\modprog\\proj\\ui\\serverside\\2.csv";
    QFile csvFile(filePath);

    if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Could not open the database file.");
        return;
    }

    QTextStream in(&csvFile);
    QString data;
    while (!in.atEnd()) {
        data += in.readLine() + "\n"; // Read each line and append to data
    }
    csvFile.close();

    // Show the data in a message box (or handle it as needed)
    QMessageBox::information(this, "Database Content", data);
}

void MainWindow::openActiveIps()
{
    // Specify the path to your TXT file
    QString filePath = "C:\\Users\\Zver\\Desktop\\uni\\modprog\\proj\\ui\\serverside\\1.txt";
    QFile txtFile(filePath);

    if (!txtFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Could not open the active IPs file.");
        return;
    }

    QTextStream in(&txtFile);
    QString data;
    while (!in.atEnd()) {
        data += in.readLine() + "\n"; // Read each line and append to data
    }
    txtFile.close();

    // Show the data in a message box (or handle it as needed)
    QMessageBox::information(this, "Active IPs Content", data);
}
