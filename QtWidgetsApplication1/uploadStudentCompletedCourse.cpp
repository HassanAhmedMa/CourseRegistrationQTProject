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

uploadStudentCompletedCourse::~uploadStudentCompletedCourse()
{}


void uploadStudentCompletedCourse::on_uploadStudentCompletedCourseBtn_clicked()
{
	Admin* admin = QtWidgetsApplication1::currentAdmin;
	int studentId = ui.StudentIdLineEdit->text().toInt();
	string selectedCourseId = ui.courseIdComboBox->currentText().toStdString();

	map<int, Student>& studs = admin -> getStudents();
	map<string, course>& courses = admin->getAllCourses();
	auto it = studs.find(studentId);
	if (it == studs.end())
		QMessageBox::information(this, "Error","Student Id not found.");
	else
		admin -> uploadStudentCompletedCourse(studentId, selectedCourseId, studs, courses);

	QMessageBox::information(this, "Message", "Student's completed course uploaded successfully");

}


void uploadStudentCompletedCourse::on_backBtn_clicked()
{
	this->close();
}

