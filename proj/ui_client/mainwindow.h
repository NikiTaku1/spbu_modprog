#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialog>
#include <QMessageBox>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QProcess>
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDate>
#include <QMenu>
#include <QToolTip>


struct Project {
    QString name;
    QString description;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createProject();
    void connectToProject();
    void showProjectDetails(const Project& project);

private:
    Ui::MainWindow *ui;
    QList<Project> projects;
    void launchClients(const QString& projectName);
    void addProjectToHistory(const QString& action, const QString& projectName);
    void loadProjectHistory();
    void saveProjectHistory();
};

#endif // MAINWINDOW_H
