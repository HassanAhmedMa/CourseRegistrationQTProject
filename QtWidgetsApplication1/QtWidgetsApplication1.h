

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"

class Admin;
class Student;

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();
    static Admin* currentAdmin;


private:
    Ui::QtWidgetsApplication1Class ui;


private slots:
    void on_registerButton_clicked();
    void on_LoginButton_clicked();

};
