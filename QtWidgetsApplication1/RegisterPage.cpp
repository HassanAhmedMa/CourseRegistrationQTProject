#include "RegisterPage.h"
#include "QtWidgetsApplication1.h"
#include"person.h"
#include <QMessageBox>
#include"Admin.h"
#include"Student.h"
#include"AdminMenu.h"
#include"StudentMainMenu.h"
RegisterPage::RegisterPage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.ActiveUserButton, &QPushButton::clicked, this, &RegisterPage::on_ActiveUserButton_clicked);
    connect(ui.NewUserButton, &QPushButton::clicked, this, &RegisterPage::RegisterUser_Add);
}

RegisterPage::~RegisterPage()
{}

void RegisterPage::on_ActiveUserButton_clicked() 
{
    this->hide();  // Only hide

    QtWidgetsApplication1* loginWindow = dynamic_cast<QtWidgetsApplication1*>(parentWidget());
    if (loginWindow) {
        loginWindow->show();
    }
    else {
        qDebug() << "loginWindow is nullptr!";
    }
}
void RegisterPage::RegisterUser_Add() 
{
    QString Firstname = ui.FirstNameBox->text();
    QString LastName = ui.LastNameBox->text();
    QString fullName = (Firstname + " " + LastName).trimmed();

    QString idStr = ui.IDBox->text();
    QString username = ui.UserNameBox->text();
    QString password = ui.PasswordBox->text();
    QString confirmpassword = ui.ConfirmPassBox->text();


    if (Firstname.isEmpty() || LastName.isEmpty() || idStr.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    if (password != confirmpassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match!");
        return; 
    }

    //to convert from Qstring to c++ String
    string nameStd = fullName.toStdString();
    string usernameStd = username.toStdString();
    string passwordStd = password.toStdString();
    int id = idStr.toInt();


    //to select whether he is an admin or a student 

    if (username.contains("@admin", Qt::CaseInsensitive)) {
        Admin* newAdmin = new Admin(id, nameStd, usernameStd, passwordStd);
        QMessageBox::information(this, "Success", "Admin registered successfully!");
        AdminMenu* adminMenu = new AdminMenu();
        adminMenu->show();
    }
    else {
        Student* newStudent = new Student(usernameStd, passwordStd, nameStd, id);
        QMessageBox::information(this, "Success", "Student registered successfully!");
        StudentMainMenu* studentMenu = new StudentMainMenu();
        studentMenu->show();
    }


}
