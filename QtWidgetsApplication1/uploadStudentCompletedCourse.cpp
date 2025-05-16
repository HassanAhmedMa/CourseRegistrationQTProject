#include "uploadStudentCompletedCourse.h"
#include "ui_uploadStudentCompletedCourse.h"
#include "Admin.h"
#include <map>
#include "Student.h"
#include <qmessagebox.h>
#include "QtWidgetsApplication1.h"
#include "FilesClass.h"
using namespace std;

uploadStudentCompletedCourse::uploadStudentCompletedCourse(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Admin* admin = QtWidgetsApplication1::currentAdmin;
	
	for (auto pair : FilesClass::AllCourses) {
		string courseID = pair.first;
		QString qCourseID = QString::fromStdString(courseID);
		ui.courseIdComboBox->addItem(qCourseID);
	}
}




void uploadStudentCompletedCourse::on_uploadStudentCompletedCourseBtn_clicked()
{
	Admin* admin = QtWidgetsApplication1::currentAdmin;
	string studentId = ui.StudentIdLineEdit->text().toStdString();
	string selectedCourseId = ui.courseIdComboBox->currentText().toStdString();

	unordered_map<string, Student>& studs = FilesClass::demoStudentsMap;
	
	auto it = studs.find(studentId);
	if (it == studs.end())
		QMessageBox::information(this, "Error","Student Id not found.");
	else
		admin -> uploadStudentCompletedCourse(studentId, selectedCourseId, FilesClass::demoStudentsMap, FilesClass::AllCourses);

	QMessageBox::information(this, "Message", "Student's completed course uploaded successfully");

}


void uploadStudentCompletedCourse::on_backBtn_clicked()
{
	this->close();
}

