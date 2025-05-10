#include "QtWidgetsApplication1.h"
#include "RegisterPage.h"
#include"StudentMainMenu.h"
#include"AdminMenu.h"
#include"Student.h"
#include"Admin.h"
#include<qmessagebox.h>
#include <vector>

vector<Admin> allAdmins;
vector<Student> allStudents;
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.RegisterButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_registerButton_clicked);
    connect(ui.LoginButton, &QPushButton::clicked, this, &QtWidgetsApplication1::on_LoginButton_clicked);
    
     //3 dummies

    allAdmins.push_back(Admin(101, "Alice Admin", "alice@admin", "admin123"));
    allAdmins.push_back(Admin(102, "Bob Boss", "bob@admin", "boss456"));
    allAdmins.push_back(Admin(103, "Carol Chief", "carol@admin", "chief789"));

    
    allStudents.push_back(Student("mohamed123", "pass1", "Mohamed Tarek", 201));
    allStudents.push_back(Student("sara456", "pass2", "Sara Youssef", 202));
    allStudents.push_back(Student("ahmed789", "pass3", "Ahmed Nabil", 203));
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
        for ( Admin admin : allAdmins) {
            if (admin.getUsername() == usernameStd && admin.getPassword() == passwordStd) {
                AdminMenu* adminMenu = new AdminMenu(this);
                adminMenu->show();
                found = true;
                break;
            }
        }
    }
    else {
        // Student Login
        for ( Student student : allStudents) {
            if (student.getUsername() == usernameStd && student.getPassword() == passwordStd) {
                StudentMainMenu* studentMenu = new StudentMainMenu(this);
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




