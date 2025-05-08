#include "CourseRegisterStudentPage.h"
#include "course.h"
#include <qmessagebox.h>
CourseRegisterStudentPage::CourseRegisterStudentPage(QWidget *parent)
	: QMainWindow(parent)
{	
	ui.setupUi(this);
	course math101("Math 101", "MATH101", "Basic Math Course", 3, "Dr. Smith", nullptr);
	course phy201("Physics 201", "PHY201", "Intermediate Physics", 4, "Dr. Johnson", &math101);
	course cs301("CS 301", "CS301", "Advanced Programming", 3, "Dr. Lee", &phy201);
	
	allCourses.push_back(math101);
	allCourses.push_back(phy201);
	allCourses.push_back(cs301);
	connect(ui.AvailableCourses1, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));



	for (int i = 0; i < allCourses.size(); i++) {
		ui.AvailableCourses1->addItem(QString::fromStdString( allCourses.at(i).getCourseID()));
		ui.AvailableCourses2->addItem(QString::fromStdString( allCourses.at(i).getCourseID()));
		ui.AvailableCourses3->addItem(QString::fromStdString( allCourses.at(i).getCourseID()));
		ui.AvailableCourses4->addItem(QString::fromStdString( allCourses.at(i).getCourseID()));
		ui.AvailableCourses5->addItem(QString::fromStdString( allCourses.at(i).getCourseID()));
		ui.AvailableCourses6->addItem(QString::fromStdString( allCourses.at(i).getCourseID()));
	}
}

CourseRegisterStudentPage::~CourseRegisterStudentPage()
{}


void CourseRegisterStudentPage::displayCourseName() {
	QString selectedCourseID = ui.AvailableCourses1->currentText();
	bool courseFound = false;
	for (auto c : allCourses) {
		if (QString::fromStdString(c.getCourseID()) ==  selectedCourseID) {
			courseFound = true;
			QString courseName = QString::fromStdString(  c.getCourseTitle());
			string creditH = to_string(c.getCreditHours());
			ui.CourseName1->setText("Course Name\n" + courseName);
			ui.CreditHoursOfcourse1->setText(QString::fromStdString(creditH));
		
			break;

		}
		
		
	}
	if (!courseFound) {
		ui.CourseName1->setText("Course Not Found");
		ui.CreditHoursOfcourse1->setText("N/A");
	}
	
}
