/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QWidget *centralwidget;
    QLabel *lbl_Title;

    void setupUi(QMainWindow *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName("MainPage");
        MainPage->resize(640, 480);
        QFont font;
        font.setPointSize(40);
        font.setBold(true);
        MainPage->setFont(font);
        centralwidget = new QWidget(MainPage);
        centralwidget->setObjectName("centralwidget");
        lbl_Title = new QLabel(centralwidget);
        lbl_Title->setObjectName("lbl_Title");
        lbl_Title->setGeometry(QRect(0, 0, 640, 480));
        lbl_Title->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	background-color:rgb(52,50,64);\n"
"	color:white;\n"
"}"));
        lbl_Title->setAlignment(Qt::AlignCenter);
        MainPage->setCentralWidget(centralwidget);

        retranslateUi(MainPage);

        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QMainWindow *MainPage)
    {
        MainPage->setWindowTitle(QCoreApplication::translate("MainPage", "MainWindow", nullptr));
        lbl_Title->setText(QCoreApplication::translate("MainPage", "Welcome", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
