#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class NewWindow : public QWidget {
    Q_OBJECT

public:
    NewWindow(QWidget *parent = nullptr);

public slots:
    void onLoginSuccess(QString username);

private:
    QLabel *label;
};

#endif
