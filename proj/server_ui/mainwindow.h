#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartServerButtonClicked();
    void onOpenDatabaseButtonClicked();
    void onServerFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onCloseEvent(QCloseEvent *event);
    void onStopServerButtonClicked();
private:
    Ui::MainWindow *ui;
    QProcess* serverProcess;
    bool serverRunning;
};
#endif // MAINWINDOW_H
