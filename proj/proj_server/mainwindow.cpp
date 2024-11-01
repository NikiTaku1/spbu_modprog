#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->Button1, &QPushButton::clicked, this, &MainWindow::openWindow1);
    connect(ui->Button2, &QPushButton::clicked, this, &MainWindow::openWindow2);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openWindow1() {
    // Создание нового окна
    QWidget *window1 = new QWidget;

    // Создание виджета для отображения текста
    QLabel *label1 = new QLabel("Здесь будет база данных");

    // Создание вертикального макета
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(label1);

    // Установка макета для окна
    window1->setLayout(layout1);

    // Настройка окна
    window1->setWindowTitle("База данных");
    window1->resize(900, 600);

    // Показ окна
    window1->show();
}

void MainWindow::openWindow2() {
    // Создание нового окна
    QWidget *window2 = new QWidget;

    // Создание виджета для отображения текста
    QLabel *label2 = new QLabel("Здесь будут активные процессы");

    // Создание вертикального макета
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(label2);

    // Установка макета для окна
    window2->setLayout(layout2);

    // Настройка окна
    window2->setWindowTitle("Активные процессы");
    window2->resize(900, 600);

    // Показ окна
    window2->show();
}
