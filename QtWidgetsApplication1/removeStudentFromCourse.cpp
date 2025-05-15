#include "removeStudentFromCourse.h"
#include "Admin.h"
#include "qmessagebox.h"
#include "QtWidgetsApplication1.h"
#include <map>
#include "QtWidgetsApplication1.h"
#include "FilesClass.h"
using namespace std;

removeStudentFromCourse::removeStudentFromCourse(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Admin* admin = QtWidgetsApplication1::currentAdmin;
	for (auto pair : FilesClass::AllCourses) {
		string courseID = pair.first;
		QString qCourseID = QString::fromStdString(courseID);
		ui.comboBoxCourseId->addItem(qCourseID);
	}
	
}

removeStudentFromCourse::~removeStudentFromCourse()
{}

void removeStudentFromCourse::on_removeStudentFromCourseBtn_clicked()
{
	int studentId = ui.lineEditStudentId->text().toInt();
	string courseId = ui.comboBoxCourseId->currentText().toStdString();

	Admin* admin = QtWidgetsApplication1::currentAdmin;
	map<int, Student>& studs = admin -> getStudents();
	auto it = studs.find(studentId);
	if (it == studs.end())
		QMessageBox::information(this, "Error", "Student ID cannot be found.");
	else
		admin -> removeStudentFromCourse(studentId, courseId, admin -> getStudents());

	QMessageBox::information(this, "Message", "Student removed from course successfully.");
}


void removeStudentFromCourse::on_backBtn_clicked()
{
	this->close();
}

