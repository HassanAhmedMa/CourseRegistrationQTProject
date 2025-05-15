/*

#include "QtWidgetsApplication1.h"
#include "RegisterPage.h"
#include"StudentMainMenu.h"
#include"AdminMenu.h"
#include"Student.h"
#include"Admin.h"
#include<qmessagebox.h>
#include <vector>
#include "FilesClass.h"
vector<Admin> allAdmins;
//<<<<<<< HEAD
vector<Student> allStudents;
Admin* QtWidgetsApplication1::currentAdmin = nullptr;

//=======
//>>>>>>> bfa0e2f8ab56be0a073df552b570b2f4ecc1cb43
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.RegisterButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_registerButton_clicked);
    connect(ui.LoginButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_LoginButton_clicked);
    
     //3 dummies

    allAdmins.push_back(Admin(101, "Alice Admin", "alice@admin", "admin123"));


    
    
}



QtWidgetsApplication1::~QtWidgetsApplication1()
{
    this->hide();

}


void QtWidgetsApplication1::on_registerButton_clicked() //when presses the register button take him to the register page
{ 
    RegisterPage* registerPage = new RegisterPage(this);  
    this->hide();  // just hide, do NOT close
    registerPage->show();
    
}
void QtWidgetsApplication1::on_LoginButton_clicked()// when presses the login button
{
    QString username = ui.UserNamelogin->text();
    QString password = ui.PasswordLogin->text();

    std::string usernameStd = username.toStdString();
    std::string passwordStd = password.toStdString();

    bool found = false;

    // Admin Login
    if (username.contains("@admin", Qt::CaseInsensitive)) {
        for ( Admin admin : allAdmins) {
            if (admin.getUsername() == usernameStd && admin.getPassword() == passwordStd) {
                currentAdmin = &admin;
                AdminMenu* adminMenu = new AdminMenu(this);
                adminMenu->show();
                found = true;
                break;
            }
        }
    }
    else {
        // Student Login
        for ( auto it : FilesClass::demoStudentsMap) //searches for the students in the files 
        {
            if (it.second.getUsername() == usernameStd && it.second.getPassword() == passwordStd) // checks if the username and password are the correct ones in the files
            {
                StudentMainMenu* studentMenu = new StudentMainMenu(this);
                this->hide(); //~Hassan
                FilesClass::loggedInStudent = &FilesClass::demoStudentsMap[usernameStd];
                studentMenu->show();
                found = true;
                break;
            }
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
                                         
}

*/


#include "QtWidgetsApplication1.h"
#include "RegisterPage.h"
#include"StudentMainMenu.h"
#include"AdminMenu.h"
#include"Student.h"
#include"Admin.h"
#include<qmessagebox.h>
#include <vector>
#include "FilesClass.h"
vector<Admin> allAdmins;
Admin* QtWidgetsApplication1::currentAdmin = nullptr;
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.RegisterButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_registerButton_clicked);
    connect(ui.LoginButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_LoginButton_clicked);

    //3 dummies

    allAdmins.push_back(Admin(101, "Alice Admin", "alice@admin", "admin123"));
    allAdmins.push_back(Admin(102, "Bob Boss", "bob@admin", "boss456"));
    allAdmins.push_back(Admin(103, "Carol Chief", "carol@admin", "chief789"));


}



QtWidgetsApplication1::~QtWidgetsApplication1()
{
    this->hide();

}


void QtWidgetsApplication1::on_registerButton_clicked() {
    RegisterPage* registerPage = new RegisterPage(this);
    this->close();  // just hide, do NOT close
    registerPage->show();

}
void QtWidgetsApplication1::on_LoginButton_clicked()
{
    QString username = ui.UserNamelogin->text();
    QString password = ui.PasswordLogin->text();

    std::string usernameStd = username.toStdString();
    std::string passwordStd = password.toStdString();

    bool found = false;

    // Admin Login
    if (username.contains("@admin", Qt::CaseInsensitive)) {
        for (Admin admin : allAdmins) {
            if (admin.getUsername() == usernameStd && admin.getPassword() == passwordStd) {
                currentAdmin = &admin;
                AdminMenu* adminMenu = new AdminMenu(this);
                adminMenu->show();
                found = true;
                break;
            }
        }
    }
    else {
        // Student Login
        for (auto it : FilesClass::demoStudentsMap) {
            if (it.second.getUsername() == usernameStd && it.second.getPassword() == passwordStd) {
                StudentMainMenu* studentMenu = new StudentMainMenu(this);
                this->hide(); //~Hassan
                FilesClass::loggedInStudent = &FilesClass::demoStudentsMap[usernameStd];
                studentMenu->show();
                found = true;
                break;
            }
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }

}




