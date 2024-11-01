#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_mainwindow.h" // Включите файл ui_mainwindow.h

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openWindow1();
    void openWindow2();

private:
    Ui::MainWindow *ui; // Объявите ui как указатель
};



#endif // MAINWINDOW_H
