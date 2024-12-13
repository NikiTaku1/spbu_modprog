#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableView>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serverProcess(nullptr)
    , serverRunning(false)
{
    ui->setupUi(this);
    connect(ui->Button1, &QPushButton::clicked, this, &MainWindow::onStartServerButtonClicked);
    connect(ui->Button2, &QPushButton::clicked, this, &MainWindow::onOpenDatabaseButtonClicked);
    connect(ui->Button3, &QPushButton::clicked, this, &MainWindow::onStopServerButtonClicked);
    connect(this, &MainWindow::closeEvent, this, &MainWindow::onCloseEvent);
    ui->labelStatus->setText("Сервер остановлен.");
}

MainWindow::~MainWindow() {
    if (serverProcess) {
        serverProcess->kill();
        serverProcess->waitForFinished();
    }
    delete ui;
}

void MainWindow::onStartServerButtonClicked() {

    QString serverPath = "C:\\Users\\Zver\\Desktop\\uni\\modprog\\proj\\client_server\\server\\build\\Desktop_Qt_6_5_3_MinGW_64_bit-Release\\release\\server.exe";
    serverProcess = new QProcess(this);
    connect(serverProcess, &QProcess::finished, this, &MainWindow::onServerFinished);
    serverProcess->start(serverPath);
    if (!serverProcess->waitForStarted(5000)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось запустить сервер. Проверьте путь и права доступа.");
        delete serverProcess;
        serverProcess = nullptr;
        return;
    }
    serverRunning = true;
    ui->labelStatus->setText("Сервер запущен.");
}


void MainWindow::onStopServerButtonClicked() {
    if (!serverProcess || serverProcess->state() == QProcess::NotRunning) {
        QMessageBox::warning(this, "Предупреждение", "Сервер не запущен.");
        return;
    }

    serverRunning = false;
    serverProcess->kill();
    serverProcess->waitForFinished();
    serverProcess = nullptr;
    ui->labelStatus->setText("Сервер остановлен.");
}


void MainWindow::onServerFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QString statusMessage;
    serverRunning = false;

    if (exitStatus == QProcess::NormalExit) {
        statusMessage = "Сервер упал!";
        QTimer::singleShot(1000, this, [this]() {
            qDebug() << "Trying to restart server after crash...";
            onStartServerButtonClicked();
        });
    } else {
        statusMessage = QString("Сервер завершен с кодом выхода: %1").arg(exitCode);
    }
    ui->labelStatus->setText(statusMessage);
    serverProcess = nullptr;
}

void MainWindow::onCloseEvent(QCloseEvent *event) {
    if (serverProcess) {
        onStopServerButtonClicked();
    }
    event->accept();
}

void MainWindow::onOpenDatabaseButtonClicked() {
    QFile jsonFile("C:\\Users\\Zver\\Desktop\\uni\\modprog\\proj\\ui_client\\build\\Desktop_Qt_6_5_3_MinGW_64_bit-Release\\release\\project_history.json");
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open project_history.json");
        return;
    }
    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        QMessageBox::critical(this, "Error", "Invalid JSON data in project_history.json");
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    if (!jsonObject.contains("projects") || !jsonObject["projects"].isArray()) {
        QMessageBox::critical(this, "Error", "Invalid JSON data: 'projects' key is missing or is not an array");
        return;
    }

    QJsonArray jsonArray = jsonObject["projects"].toArray();

    QStandardItemModel* model = new QStandardItemModel;
    model->setHorizontalHeaderItem(0, new QStandardItem("Action"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Project Name"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Date"));

    for (const QJsonValue& value : jsonArray) {
        QJsonObject projectObject = value.toObject();
        model->appendRow({
            new QStandardItem(projectObject["action"].toString()),
            new QStandardItem(projectObject["projectName"].toString()),
            new QStandardItem(projectObject["date"].toString())
        });
    }

    QTableView* tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Project History");
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(tableView);
    dialog->setLayout(layout);
    dialog->resize(600, 400);
    dialog->exec();
}
