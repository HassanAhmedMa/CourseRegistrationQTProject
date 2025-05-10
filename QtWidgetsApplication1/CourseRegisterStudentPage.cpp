#include "CourseRegisterStudentPage.h"
#include "course.h"
#include "Student.h"
#include <qmessagebox.h>
CourseRegisterStudentPage::CourseRegisterStudentPage(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	course math101("Math 101", "MATH101", "Basic Math Course", 3, "Dr. Smith", nullptr);
	course phy201("Physics 201", "PHY201", "Intermediate Physics", 4, "Dr. Johnson", &math101);
	course cs301("CS 301", "CS301", "Advanced Programming", 3, "Dr. Lee", &phy201);

	student = new Student("user1", "pass", "Ali", 123);
	student->addCourseCompleted("MATH101"); // Student completed only MATH101

	allCourses.push_back(math101);
	allCourses.push_back(phy201);
	allCourses.push_back(cs301);
	connect(ui.AvailableCourses1, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	connect(ui.AvailableCourses2, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	connect(ui.AvailableCourses3, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	connect(ui.AvailableCourses4, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	connect(ui.AvailableCourses5, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	connect(ui.AvailableCourses6, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	connect(ui.SubmitButtomForCourse, &QPushButton::clicked, this, &CourseRegisterStudentPage::registerSelectedCourses);



	for (int i = 0; i < allCourses.size(); i++) {
		ui.AvailableCourses1->addItem(QString::fromStdString(allCourses.at(i).getCourseID()));
		ui.AvailableCourses2->addItem(QString::fromStdString(allCourses.at(i).getCourseID()));
		ui.AvailableCourses3->addItem(QString::fromStdString(allCourses.at(i).getCourseID()));
		ui.AvailableCourses4->addItem(QString::fromStdString(allCourses.at(i).getCourseID()));
		ui.AvailableCourses5->addItem(QString::fromStdString(allCourses.at(i).getCourseID()));
		ui.AvailableCourses6->addItem(QString::fromStdString(allCourses.at(i).getCourseID()));
	}
}

CourseRegisterStudentPage::~CourseRegisterStudentPage()
{
}



void CourseRegisterStudentPage::displayCourseName() {
	QComboBox* senderCombo = qobject_cast<QComboBox*>(sender());
	if (!senderCombo) return;

	QString selectedCourseID = senderCombo->currentText();
	QString courseName = "Course Not Found";
	QString creditHours = "N/A";

	for (const auto& c : allCourses) {
		if (QString::fromStdString(c.getCourseID()) == selectedCourseID) {
			courseName = QString::fromStdString(c.getCourseTitle());
			creditHours = QString::number(c.getCreditHours());
			break;
		}
	}

	if (senderCombo == ui.AvailableCourses1) {
		ui.CourseName1->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse1->setText(creditHours);
	}
	else if (senderCombo == ui.AvailableCourses2) {
		ui.CourseName2->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse2->setText(creditHours);
	}
	else if (senderCombo == ui.AvailableCourses3) {
		ui.CourseName3->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse3->setText(creditHours);
	}
	else if (senderCombo == ui.AvailableCourses4) {
		ui.CourseName4->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse4->setText(creditHours);
	}
	else if (senderCombo == ui.AvailableCourses5) {
		ui.CourseName5->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse5->setText(creditHours);
	}
	else if (senderCombo == ui.AvailableCourses6) {
		ui.CourseName6->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse6->setText(creditHours);
	}
	updateTotalCreditHours();

}

void CourseRegisterStudentPage::checkMaxCreditLimit(int total) {
	if (total > 21) {
		QMessageBox::warning(this, "Registration Error", "You cannot register because total credit hours exceed 21.");
	}
}

void CourseRegisterStudentPage::updateTotalCreditHours() {
	int total = 0;
	QStringList selectedIDs = {
		ui.AvailableCourses1->currentText(),
		ui.AvailableCourses2->currentText(),
		ui.AvailableCourses3->currentText(),
		ui.AvailableCourses4->currentText(),
		ui.AvailableCourses5->currentText(),
		ui.AvailableCourses6->currentText()
	};

	for (const QString& id : selectedIDs) {
		for (const course& c : allCourses) {
			if (QString::fromStdString(c.getCourseID()) == id) {
				total += c.getCreditHours();
				break;
			}
		}
	}

	ui.progressBarTotalCreditHours->setMaximum(21);
	ui.progressBarTotalCreditHours->setValue(total);


	checkMaxCreditLimit(total);
	//checkCoursePrerequisites();
}

//void CourseRegisterStudentPage::checkCoursePrerequisites() {
//	QStringList selectedIDs = {
//	  ui.AvailableCourses1->currentText(),
//	  ui.AvailableCourses2->currentText(),
//	  ui.AvailableCourses3->currentText(),
//	  ui.AvailableCourses4->currentText(),
//	  ui.AvailableCourses5->currentText(),
//	  ui.AvailableCourses6->currentText()
//	};
//
//	// Create a map for Student::CheckPrerequisties
//	unordered_map<string, course> courseMap;
//	for (const course& c : allCourses) {
//		courseMap[c.getCourseID()] = c;
//	}
//	vector<string> completed = student->getCoursesCompleted();
//
//	for (const QString& id : selectedIDs) {
//		string courseID = id.toStdString();
//
//		if (!student->CheckPrerequisties(courseID, completed, courseMap)) {
//			QString prereq = QString::fromStdString(courseMap[courseID].getPrerequisite()->getCourseID());
//			QMessageBox::warning(this, "Prerequisite Not Met",
//				"You cannot register for " + id + " because you have not completed its prerequisite: " + prereq);
//		}
//	}
//	QMessageBox::information(this, "Debug", "checkCoursePrerequisites() was triggered!");
//
//}
//void CourseRegisterStudentPage::checkCoursePrerequisites() {
//	QStringList selectedIDs = {
//		ui.AvailableCourses1->currentText(),
//		ui.AvailableCourses2->currentText(),
//		ui.AvailableCourses3->currentText(),
//		ui.AvailableCourses4->currentText(),
//		ui.AvailableCourses5->currentText(),
//		ui.AvailableCourses6->currentText()
//	};
//
//	// Convert allCourses to map
//	unordered_map<string, course> courseMap;
//	for (const course& c : allCourses) {
//		courseMap[c.getCourseID()] = c;
//	}
//
//	vector<string> completed = student->getCoursesCompleted();
//
//	for (const QString& id : selectedIDs) {
//		string courseID = id.toStdString();
//
//		// Check if course exists and has a prerequisite
//		auto it = courseMap.find(courseID);
//		if (it != courseMap.end() && it->second.getPrerequisite() != nullptr) {
//			string prereqID = it->second.getPrerequisite()->getCourseID();
//
//			// Check if student has NOT completed the prerequisite
//			bool found = false;
//			for (const string& completedID : completed) {
//				if (completedID == prereqID) {
//					found = true;
//					break;
//				}
//			}
//
//			// ? Not found ? show warning
//			if (!found) {
//				QMessageBox::warning(this, "Prerequisite Not Met",
//					"You cannot register for " + id + " because you have not completed its prerequisite: " + QString::fromStdString(prereqID));
//			}
//		}
//	}
//}


void CourseRegisterStudentPage::registerSelectedCourses() {
	QStringList selectedIDs = {
		ui.AvailableCourses1->currentText(),
		ui.AvailableCourses2->currentText(),
		ui.AvailableCourses3->currentText(),
		ui.AvailableCourses4->currentText(),
		ui.AvailableCourses5->currentText(),
		ui.AvailableCourses6->currentText()
	};

	// Step 1: Convert allCourses vector to map for Student class methods
	unordered_map<string, course> allCoursesMap;
	for (const course& c : allCourses) {
		allCoursesMap[c.getCourseID()] = c;
	}

	int totalCredits = 0;

	// Step 2: Check each course
	for (const QString& qid : selectedIDs) {
		string courseID = qid.toStdString();

		// Skip if empty selection
		if (courseID.empty()) continue;

		// Check if course exists
		if (!student->CourseIsAvaliable(courseID, allCoursesMap)) {
			QMessageBox::warning(this, "Course Error", QString::fromStdString("Course not available: " + courseID));
			return;
		}

		// Check prerequisite
		if (!student->CheckPrerequisties(courseID, student->getCoursesCompleted(), allCoursesMap)) {
			course* prereq = allCoursesMap[courseID].getPrerequisite();
			string prereqID = (prereq != nullptr) ? prereq->getCourseID() : "UNKNOWN";
			QMessageBox::warning(this, "Prerequisite Error",
				QString::fromStdString("You must complete " + prereqID + " before registering for " + courseID));
			return;
		}

		totalCredits += allCoursesMap[courseID].getCreditHours();
	}

	// Step 3: Check credit limit
	if (totalCredits > 21) {
		QMessageBox::warning(this, "Credit Limit Exceeded", "You cannot register for more than 21 credit hours.");
		return;
	}

	// Step 4: Register valid courses
	for (const QString& qid : selectedIDs) {
		string courseID = qid.toStdString();
		if (!courseID.empty()) {
			student->CourseRegisteration(courseID, allCoursesMap, student->getCoursesCompleted());
		}
	}

	QMessageBox::information(this, "Registration Complete", "Courses registered successfully!");
}
