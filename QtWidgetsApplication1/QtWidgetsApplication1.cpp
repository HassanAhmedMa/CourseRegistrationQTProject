#include "QtWidgetsApplication1.h"
#include "RegisterPage.h"
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsApplication1::on_registerButton_clicked);
}



QtWidgetsApplication1::~QtWidgetsApplication1()
{
    delete this;

}


void QtWidgetsApplication1::on_registerButton_clicked() {

    RegisterPage* registerPage = new RegisterPage(this);
    this->hide();
    this->close();
    registerPage->show();



}




