#include "ViewStudentGradeAdminPage.h"
#include <qpushbutton.h>
#include <string>
using namespace std;
ViewStudentGradeAdminPage::ViewStudentGradeAdminPage(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	connect(ui->ViewGradeSearchStudent_Btn, &QPushButton::clicked, this, &ViewStudentGradeAdminPage::displayGrades);
}

ViewStudentGradeAdminPage::~ViewStudentGradeAdminPage()
{}


void ViewStudentGradeAdminPage::displayGrades() {
	//string idToSearch = ui->lineEdit->text().toStdString();
	//for (auto x : /*staticAttribute*/) {

	//}


}
