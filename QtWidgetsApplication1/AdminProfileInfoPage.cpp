#include "AdminProfileInfoPage.h"
#include "qsettings.h"
#include "Admin.h"
#include "qmessagebox.h"
#include "QtWidgetsApplication1.h"

AdminProfileInfoPage::AdminProfileInfoPage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    // QSettings is used for simple key value storage
    // Load saved data
    QSettings settings("YourCompany", "YourApp");

    QString qName = settings.value("profile/name", "").toString();
    QString qUsername = settings.value("profile/username", "").toString();
    QString qPassword = settings.value("profile/password", "").toString();

    //update Ui elements
    ui.NamelineEdit->setText(qName);
    ui.UsernamelineEdit->setText(qUsername);
    ui.passwordLineEdit->setText(qPassword);
   
}

AdminProfileInfoPage::~AdminProfileInfoPage()
{}

void AdminProfileInfoPage::on_backBtn_clicked()
{
    this->close();
}


void AdminProfileInfoPage::on_editInfoBtn_clicked()
{   
   // Admin* admin = QtWidgetsApplication1::currentAdmin;

    QString qName = ui.NamelineEdit->text();
    QString qUsername = ui.UsernamelineEdit->text();
    QString qPassword = ui.passwordLineEdit->text();

    string name = qName.toStdString();
    string username = qUsername.toStdString();
    string password = qPassword.toStdString();
    /*
    admin ->setName(name);
    admin ->setUsername(username);
    admin ->setPassword(password);
    */

    // save information to QSettings
    QSettings settings("YourCompany", "YourApp");
    settings.setValue("profile/name", qName);
    settings.setValue("profile/username", qUsername);
    settings.setValue("profile/password", qPassword);

    QMessageBox::information(this, "Message", "Your profile information has been updated successfully.");
}

