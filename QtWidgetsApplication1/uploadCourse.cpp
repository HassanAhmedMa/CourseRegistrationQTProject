#include "uploadCourse.h"
#include "ui_uploadCourse.h"
#include "admin.h"
#include "qmessagebox.h"
#include "QtWidgetsApplication1.h"
#include <map>
using namespace std;


uploadCourse::uploadCourse(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

uploadCourse::~uploadCourse()
{}

void uploadCourse::on_uploadEditCourseBtn_clicked()
{




	string courseId = ui.lineEditCourseId->text().toStdString();
	string courseTitle = ui.lineEdit_CourseTitle->text().toStdString();
	string instructorName = ui.lineEdit_InstructorName->text().toStdString();
	string desc = ui.textEdit_CourseDesc->toPlainText().toStdString();
	int creditHours = ui.LineEdit_CourseCreditHours->text().toInt();

	Admin* admin = QtWidgetsApplication1::currentAdmin;
	
	
	admin -> uploadCourse(FilesClass::AllCourses, courseId, courseTitle, desc, creditHours, instructorName);


	QMessageBox::information(this, "Message", "Course Uploaded Sucessfully.");


}


void uploadCourse::on_backBtn_clicked()
{
	this->close();
}

