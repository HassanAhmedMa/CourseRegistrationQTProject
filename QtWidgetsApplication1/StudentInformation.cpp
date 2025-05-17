#include "StudentInformation.h"
#include "FilesClass.h"
#include <string>
#include "reportStudent.h"
#include "StudentMainMenu.h"
#include "StudentMainMenu.h"
StudentInformation::StudentInformation(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.Back, &QPushButton::clicked, this, &StudentInformation::on_backBtn_clicked);
	ui.NameField->setText(QString::fromStdString(FilesClass::loggedInStudent->getName()));
	ui.UserField->setText(QString::fromStdString(FilesClass::loggedInStudent->getUsername()));
	ui.PasswordField->setText(QString::fromStdString(FilesClass::loggedInStudent->getPassword()));
	ui.SidField->setText(QString::number(FilesClass::loggedInStudent->getId()));
	string courses = "";
	qDebug() << FilesClass::loggedInStudent->getId();
	if (!FilesClass::loggedInStudent->getCourses().empty() && FilesClass::loggedInStudent->getCourses().at(0) != "none") {
		for (auto x : FilesClass::loggedInStudent->getCourses()) {

			courses.append(FilesClass::AllCourses[x].getCourseTitle() + ", ");
		}
		courses.pop_back();
		courses.pop_back();
		ui.RegisteredCourse->setText(QString::fromStdString("Currently enrolled Courses : " + courses));
		
	}
	else {
		ui.RegisteredCourse->setText(QString::fromStdString("This Student has no registered courses yet !"));
	}
	
	courses = "";
	if (!FilesClass::loggedInStudent->getCoursesCompleted().empty() && FilesClass::loggedInStudent->getCoursesCompleted().at(0) != "none") {
		for (auto x : FilesClass::loggedInStudent->getCoursesCompleted()) {

			courses.append(FilesClass::AllCourses[x].getCourseTitle() + ", ");
		}
		courses.pop_back();
		courses.pop_back();
		ui.CompletedCourse->setText(QString::fromStdString("Completed Courses :111 " + courses));
	}
	else
	{
		ui.CompletedCourse->setText(QString::fromStdString("This Student has no completed courses yet !"));
	}
	Student::history.push("view Student Information");
	if (Student::history.size() > 5) {
		Student::history.pop();
	}
	

}

StudentInformation::~StudentInformation()
{
	StudentMainMenu* m = new StudentMainMenu(this);
	m->show();
	this->hide();

}

void StudentInformation::closeEvent(QCloseEvent* event)
{
	if (parentWidget()) {
		parentWidget()->show();  // Show the parent again
	}
	QMainWindow::closeEvent(event); // Call base class to close window
}
void StudentInformation::on_backBtn_clicked() {
	// Create and show the main menu
	StudentMainMenu* mainMenu = new StudentMainMenu();
	mainMenu->show();

	// Close the current window
	this->close();
}