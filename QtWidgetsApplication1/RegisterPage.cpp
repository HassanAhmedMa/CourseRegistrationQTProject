#include "RegisterPage.h"
#include "QtWidgetsApplication1.h"
RegisterPage::RegisterPage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//connect(ui.pushButton, &QPushButton::clicked, this, &RegisterPage::on_pushButton_clicked);
}

RegisterPage::~RegisterPage()
{}

void RegisterPage::on_pushButton_clicked() {
    // Simply hide the current RegisterPage and show the existing login window
    this->hide();

    // Find the main window and show it again
    QtWidgetsApplication1* loginWindow = dynamic_cast<QtWidgetsApplication1*>(parentWidget());
    if (loginWindow) {
        loginWindow->show();  // Show the main (login) window
    }
	

}
