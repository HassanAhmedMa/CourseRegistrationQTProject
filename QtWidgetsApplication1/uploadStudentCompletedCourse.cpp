#include "uploadStudentCompletedCourse.h"
#include "ui_uploadStudentCompletedCourse.h"
#include "Admin.h"
#include <map>
#include "Student.h"
#include <qmessagebox.h>
#include "QtWidgetsApplication1.h"
#include "FilesClass.h"
#include <string>
using namespace std;

uploadStudentCompletedCourse::uploadStudentCompletedCourse(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Admin* admin = QtWidgetsApplication1::currentAdmin;

	connect(ui.searchBtn, &QPushButton::clicked, this, &uploadStudentCompletedCourse::on_searchBtn_clicked);
	connect(ui.uploadStudentCompletedCourseBtn, &QPushButton::clicked, this, &uploadStudentCompletedCourse::on_uploadStudentCompletedCourseBtn_clicked);
	connect(ui.backBtn, &QPushButton::clicked, this, &uploadStudentCompletedCourse::on_backBtn_clicked);


}




void uploadStudentCompletedCourse::on_uploadStudentCompletedCourseBtn_clicked()
{
	Admin* admin = QtWidgetsApplication1::currentAdmin;
	string studentId = ui.StudentIdLineEdit->text().toStdString();

	string selectedCourseId = ui.courseIdComboBox->currentText().toStdString();


	admin->uploadStudentCompletedCourse(studentId, selectedCourseId, FilesClass::demoStudentsMap, FilesClass::AllCourses);

	QMessageBox::information(this, "Message", "Student's completed course uploaded successfully");

}


void uploadStudentCompletedCourse::on_backBtn_clicked()
{
	this->close();
}

void uploadStudentCompletedCourse::setComboBoxItems(string studentId)
{
	ui.courseIdComboBox->clear();

	Student& stud = FilesClass::demoStudentsMap.at(studentId);
	vector <string> studCourses = stud.getCourses();
	for (int i = 0; i < studCourses.size(); i++) {
		string courseId = studCourses[i];
		QString item = QString::fromStdString(courseId);
		ui.courseIdComboBox->addItem(item);
	}
}



uploadStudentCompletedCourse::~uploadStudentCompletedCourse()
{

}

void uploadStudentCompletedCourse::on_searchBtn_clicked()
{
	string studentId = ui.StudentIdLineEdit->text().toStdString();
	unordered_map<string, Student>& studs = FilesClass::demoStudentsMap;

	auto it = studs.find(studentId);
	if (it == studs.end()) {
		QMessageBox::information(this, "Error", "Student Id not found.");
	}
	else {
		//QMessageBox::information(this, "Success", "Student found Successfully");
		setComboBoxItems(studentId);
	}


}

