#include "AdminMenu.h"
#include "AdminProfileInfoPage.h"
#include "ViewStudentGradeAdminPage.h"
#include "setPrerequisitesPage.h"
#include "UploadEditStudentGradesPage.h"
#include "uploadCourse.h"
#include <uploadStudentCompletedCourse.h>


AdminMenu::AdminMenu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

AdminMenu::~AdminMenu()
{}


void AdminMenu::on_viewProfile_Btn_clicked()
{
	AdminProfileInfoPage* form = new AdminProfileInfoPage();
	form->show();
}


void AdminMenu::on_viewStudentGrades_Btn_clicked()
{
	ViewStudentGradeAdminPage* form = new ViewStudentGradeAdminPage();
	form->show();
}


void AdminMenu::on_uploadGrades_Btn_clicked()
{
	UploadEditStudentGradesPage* form = new UploadEditStudentGradesPage();
	form->show();
}


void AdminMenu::on_setPrerequisites_Btn_clicked()
{
	setPrerequisitesPage* form = new setPrerequisitesPage();
	form->show();
}

void AdminMenu::on_UploadCourseAdminMenuBtn_clicked()
{

	
	uploadCourse* form = new uploadCourse();
	form->show();

}

void AdminMenu::on_UploadCompletedCourseAdminMenuBtn_clicked()
{
	uploadStudentCompletedCourse* form = new uploadStudentCompletedCourse();
	form->show();

}

