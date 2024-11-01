#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class NewWindow : public QWidget {
    Q_OBJECT

public:
    NewWindow(QWidget *parent = nullptr);

private:
    QLabel *label;
};

#endif // NEWWINDOW_H
