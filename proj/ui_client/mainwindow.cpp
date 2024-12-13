#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include <QProcess>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDate>
#include <QToolTip>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , projects()
{
    ui->setupUi(this);
    connect(ui->Button1, &QPushButton::clicked, this, &MainWindow::createProject);
    connect(ui->Button2, &QPushButton::clicked, this, &MainWindow::connectToProject);
    loadProjectHistory();
}

MainWindow::~MainWindow() {
    saveProjectHistory();
    delete ui;
}


void MainWindow::createProject() {
    QDialog dialog;
    dialog.setWindowTitle("Create New Project");

    QLineEdit nameEdit;
    nameEdit.setPlaceholderText("Project Name");
    QTextEdit descEdit;
    descEdit.setPlaceholderText("Project Description");
    QPushButton okButton("OK");
    QPushButton cancelButton("Cancel");

    QVBoxLayout layout;
    layout.addWidget(&nameEdit);
    layout.addWidget(&descEdit);
    layout.addWidget(&okButton);
    layout.addWidget(&cancelButton);
    dialog.setLayout(&layout);

    QString projectName;

    connect(&okButton, &QPushButton::clicked, [&, this]() {
        projectName = nameEdit.text();
        QString desc = descEdit.toPlainText();
        if (!projectName.isEmpty()) {
            projects.append({projectName, desc});
            dialog.accept();
        } else {
            QMessageBox::warning(&dialog, "Error", "Project name cannot be empty.");
        }
    });

    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Project created successfully!");
        addProjectToHistory("creation", projectName);
    }
}

void MainWindow::connectToProject() {
    QDialog* projectDialog = new QDialog(this);
    projectDialog->setWindowTitle("Connect to Project");
    QVBoxLayout* mainLayout = new QVBoxLayout(projectDialog);

    QListWidget* projectList = new QListWidget;
    for (const auto& project : projects) {
        QListWidgetItem* item = new QListWidgetItem(project.name);
        item->setData(Qt::UserRole, QVariant::fromValue(project));
        projectList->addItem(item);
    }

    if (projects.isEmpty()) {
        QMessageBox::warning(projectDialog, "No Projects", "No projects available to connect to.");
        delete projectDialog;
        return;
    }

    QPushButton* connectButton = new QPushButton("Connect");
    QObject::connect(connectButton, &QPushButton::clicked, [this, projectList, projectDialog]() {
        QListWidgetItem* selectedItem = projectList->currentItem();
        if (selectedItem) {
            Project project = selectedItem->data(Qt::UserRole).value<Project>();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Connect to Project?");
            msgBox.setText(QString("Name: %1\nDescription: %2\n\nAre you sure you want to connect?").arg(project.name).arg(project.description));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();

            if (ret == QMessageBox::Yes) {
                launchClients(project.name);
                addProjectToHistory("connection", project.name);
            }

            projectDialog->accept();

        } else {
            QMessageBox::warning(projectDialog, "Error", "Please select a project.");
        }
    });

    QPushButton* cancelButton = new QPushButton("Cancel");
    QObject::connect(cancelButton, &QPushButton::clicked, projectDialog, &QDialog::reject);

    mainLayout->addWidget(projectList);
    mainLayout->addWidget(connectButton);
    mainLayout->addWidget(cancelButton);
    projectDialog->setLayout(mainLayout);
    projectDialog->exec();

    delete projectList;
    delete connectButton;
    delete cancelButton;
    delete mainLayout;
    delete projectDialog;
}


void MainWindow::showProjectDetails(const Project& project){
    QDialog detailsDialog;
    detailsDialog.setWindowTitle(project.name);

    QVBoxLayout* detailsLayout = new QVBoxLayout(&detailsDialog);
    QLabel* nameLabel = new QLabel("Name: " + project.name);
    QLabel* descLabel = new QLabel("Description: " + project.description);
    detailsLayout->addWidget(nameLabel);
    detailsLayout->addWidget(descLabel);
    detailsDialog.setLayout(detailsLayout);
    detailsDialog.exec();
    delete detailsLayout;
}
void MainWindow::addProjectToHistory(const QString& action, const QString& projectName) {
    QFile saveFile("project_history.json");
    QJsonObject rootObject;
    QJsonArray projectArray;


    if (saveFile.exists()) {
        if (!saveFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Error opening file to read";
            return;
        }

        QByteArray saveData = saveFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        if (!loadDoc.isNull()){
            rootObject = loadDoc.object();
            projectArray = rootObject.value("projects").toArray();
        }
        saveFile.close();

    }


    QJsonObject projectObject;
    projectObject["action"] = action;
    projectObject["projectName"] = projectName;
    projectObject["date"] = QDate::currentDate().toString("yyyy-MM-dd");
    projectArray.append(projectObject);
    rootObject["projects"] = projectArray;


    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file to write";
        return;
    }
    QJsonDocument saveDoc(rootObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

}

void MainWindow::loadProjectHistory() {
    QFile loadFile("project_history.json");
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File not found or error opening file for reading.";
        return;
    }
    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(loadData);
    if (!loadDoc.isNull()){
        QJsonObject root = loadDoc.object();
        QJsonArray projects = root.value("projects").toArray();
        for(const auto &project : projects){
            qDebug() << "Loaded project from JSON: " << project.toObject();
        }

    }
    loadFile.close();
}

void MainWindow::saveProjectHistory() {

}

void MainWindow::launchClients(const QString& projectName) {
    QString clientPath = "C:\\Users\\Zver\\Desktop\\uni\\modprog\\proj\\client_server\\client\\build\\Desktop_Qt_6_5_3_MinGW_64_bit-Release\\release\\client.exe"; // Replace with actual path to your client executable.
    QProcess *client1 = new QProcess(this);
    client1->start(clientPath);

    QProcess *client2 = new QProcess(this);
    client2->start(clientPath);

    QObject::connect(client1, &QProcess::finished, [client1]() {
        delete client1;
    });

    QObject::connect(client2, &QProcess::finished, [client2]() {
        delete client2;
    });

    qDebug() << "Launched two instances of client.exe for project:" << projectName;
}
