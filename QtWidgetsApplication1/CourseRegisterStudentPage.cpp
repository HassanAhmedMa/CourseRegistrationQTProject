
#include "CourseRegisterStudentPage.h"
#include "course.h"
#include "Student.h"
#include <qmessagebox.h>
#include <QComboBox>
#include <vector>
#include "FilesClass.h"
#include<queue>
CourseRegisterStudentPage::CourseRegisterStudentPage(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Allocate courses on heap to avoid pointer issues
	FilesClass::AllCourses;
	//student = new Student("user1", "pass", "Ali", 1);

	//student->addCourseCompleted("PHY201");
	
	comboBoxes.push_back(ui.AvailableCourses1);
	comboBoxes.push_back(ui.AvailableCourses2);
	comboBoxes.push_back(ui.AvailableCourses3);
	comboBoxes.push_back(ui.AvailableCourses4);
	comboBoxes.push_back(ui.AvailableCourses5);
	comboBoxes.push_back(ui.AvailableCourses6);


	//FilesClass::AllStudents;


	
	// Connect course selectors
	for (auto x : comboBoxes) {
		x->addItem("Select an option... "); //initialize the index 0 with a "select an option" option for friendly user interface ~Hassan
		connect(x, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));
	}
	connect(ui.SubmitButtomForCourse, &QPushButton::clicked, this, &CourseRegisterStudentPage::registerSelectedCourses);

	// Populate comboboxes
	for (auto c : FilesClass::AllCourses) {
		QString id = QString::fromStdString(c.second.getCourseID());
		for (auto comboBox : comboBoxes) { //Put all the course Ids in all the combox boxes using a nested loop ~Hassan
			comboBox->addItem(id);
		}
	}
}

CourseRegisterStudentPage::~CourseRegisterStudentPage() {
	//for (course* c : allCourses) delete c;
}

void CourseRegisterStudentPage::displayCourseName() {
	QComboBox* senderCombo = qobject_cast<QComboBox*>(sender());
	if (!senderCombo) return;

	QString selectedCourseID = senderCombo->currentText();
	QString courseName = "Course Not Found";
	QString creditHours = "N/A";

	for (auto c : FilesClass::AllCourses) {
		if (QString::fromStdString(c.second.getCourseID()) == selectedCourseID) {
			courseName = QString::fromStdString(c.second.getCourseTitle());
			creditHours = QString::number(c.second.getCreditHours());
			break;
		}
	}

	//for (auto combo : comboBoxes) {
	//	if (senderCombo == combo) {
	//		ui.CourseName1->setText("Course Name\n" + courseName);
	//		ui.CreditHoursOfcourse1->setText("Credit Hours : " + creditHours);
	//	}
	//}


	if (senderCombo == ui.AvailableCourses1) {
		ui.CourseName1->setText("Course Name\n" + courseName);
		ui.CreditHoursOfcourse1->setText("Credit Hours : " + creditHours);
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
	
	QStringList selectedIDs;
	for (auto x : comboBoxes) {
		selectedIDs.append(x->currentText());
	}

	for (const QString& id : selectedIDs) {
		for (auto c : FilesClass::AllCourses) {
			if (QString::fromStdString(c.second.getCourseID()) == id) {
				total += c.second.getCreditHours();
				break;
			}
		}
	}

	ui.progressBarTotalCreditHours->setValue(total);
	checkMaxCreditLimit(total);
}





void CourseRegisterStudentPage::registerSelectedCourses() {
	if (FilesClass::toLower(student->getCourses().at(0)) != "none") { //none flag (for files) to check if the student is not registered ~hassan
		QMessageBox::warning(this, "Already Registered", "You have already registered courses. You cannot register again.");
		return;
	}
	QStringList selectedIDs; //Add all courses id
	for (auto x : comboBoxes) {
		selectedIDs.append(x->currentText());
	}

	//unordered_map<string, course> allCoursesMap;
	//for (auto c : FilesClass::AllCourses) {
	//	allCoursesMap[c.second.getCourseID()] = c.second;
	//}

	int totalCredits = 0;
	for (const QString& qid : selectedIDs) {
		if (qid == "Select an option... ") {
			continue;
		}
		string courseID = qid.toStdString();
		if (courseID.empty()) continue;

		if (!student->CourseIsAvaliable(courseID, FilesClass::AllCourses)) {
			QMessageBox::warning(this, "Course Error", QString::fromStdString("Course not available: " + courseID));
			return;
		}

		if (!student->CheckPrerequisties(courseID, student->getCoursesCompleted(), FilesClass::AllCourses)) {
			QMessageBox::warning(this, "Prerequisite Error",
				QString::fromStdString("You must complete the required prerequisite before registering for " + courseID));
			return;
		}

		totalCredits += FilesClass::AllCourses[courseID].getCreditHours();
	}

	if (totalCredits > 21) {
		QMessageBox::warning(this, "Credit Limit Exceeded", "You cannot register for more than 21 credit hours.");
		return;
	}
	student->getCoursesPtr()->pop_back();
	for (QString qid : selectedIDs) {
		string courseID = qid.toStdString();
		
		if (!courseID.empty() && courseID != "Select an option... ") {
			student->CourseRegisteration(courseID, FilesClass::AllCourses, student->getCoursesCompleted());
		}
		qDebug() << student->getCourses();
	}

	QMessageBox::information(this, "Registration Complete", "Courses registered successfully!");
	Student::history.push("Courses Registeration");
	if (Student::history.size() > 5) {
		Student::history.pop(); 
	}
}



