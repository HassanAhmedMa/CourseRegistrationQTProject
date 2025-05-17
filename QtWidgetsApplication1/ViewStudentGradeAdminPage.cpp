#include "ViewStudentGradeAdminPage.h"
#include <iostream>
#include <QMessageBox>
#include <string>
#include <AdminMenu.h>
#include <FilesClass.h>

ViewStudentGradeAdminPage::ViewStudentGradeAdminPage( QWidget* parent)
	: QMainWindow(parent)
{
	ui = new Ui::ViewStudentGradeAdminPageClass();
	ui->setupUi(this);

	connect(ui->ViewGradeSearchStudent_Btn, &QPushButton::clicked, this, &ViewStudentGradeAdminPage::onSearchClicked);
	connect(ui->ShowGradeBtn, &QPushButton::clicked, this, &ViewStudentGradeAdminPage::onShowGradeClicked);
	connect(ui->ViewStudentGradeAdminBackBtn, &QPushButton::clicked, this, &ViewStudentGradeAdminPage::onBackToAdminMenuClicked);


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ViewStudentGradeAdminPage::onSearchClicked() {
	string studentId = ui->StudentIDTextFieldViewGrade->text().toStdString(); //  ID text field
	vector<string> courses = getStudentCourses(studentId);

	ui->AdminViewGradesCoursesComboBox->clear();

	for (string& course : courses) {
		ui->AdminViewGradesCoursesComboBox->addItem(QString::fromStdString(course));
	}

	if (courses.empty()) {
		QMessageBox::warning(this, "Not Found", "No completed courses found or student ID not found.");
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> ViewStudentGradeAdminPage::getStudentCourses(string studentId)
{
	vector<string> courses;
	if (FilesClass::demoStudentsMap.find(studentId) != FilesClass::demoStudentsMap.end()) {
		Student* student = &FilesClass::demoStudentsMap[studentId];
		courses = student->getCoursesCompleted();

	}
	else {
		cout << "Student not found." << endl;
	}
	return courses;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ViewStudentGradeAdminPage::onShowGradeClicked()
{
	string studentId = ui->StudentIDTextFieldViewGrade->text().toStdString();
	string courseID = ui->AdminViewGradesCoursesComboBox->currentText().toStdString();
	float grade;

	if (FilesClass::demoStudentsMap.find(studentId) != FilesClass::demoStudentsMap.end()) {
		Student* student = &FilesClass::demoStudentsMap[studentId];

		if (student->getGradeValue(courseID, grade)) {
			ui->DisplayGradelineEdit->setText(QString::number(grade));
		}
		else {
			ui->DisplayGradelineEdit->setText("N/A");
			QMessageBox::warning(this, "No Grade", "No grade recorded for this course.");
		}

	}
	else {
		QMessageBox::warning(this, "Error", "Student not found.");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ViewStudentGradeAdminPage::onBackToAdminMenuClicked()
{

	this->close();
}


ViewStudentGradeAdminPage::~ViewStudentGradeAdminPage()
{
	delete ui;
}

