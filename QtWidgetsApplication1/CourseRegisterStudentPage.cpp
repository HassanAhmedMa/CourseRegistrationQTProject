#include "CourseRegisterStudentPage.h"
#include "course.h"
#include "Student.h"
#include <qmessagebox.h>
#include <QComboBox>
#include "StudentMainMenu.h"
#include <vector>
#include "FilesClass.h"
#include <queue>
#include "reportStudent.h"

CourseRegisterStudentPage::CourseRegisterStudentPage(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.Back, &QPushButton::clicked, this, &CourseRegisterStudentPage::on_backBtn_clicked);
	// The courses are already stored globally in FilesClass::AllCourses

	// These are the dropdown menus for choosing courses
	comboBoxes.push_back(ui.AvailableCourses1);
	comboBoxes.push_back(ui.AvailableCourses2);
	comboBoxes.push_back(ui.AvailableCourses3);
	comboBoxes.push_back(ui.AvailableCourses4);
	comboBoxes.push_back(ui.AvailableCourses5);
	comboBoxes.push_back(ui.AvailableCourses6);

	
	for (auto x : comboBoxes) {
		x->addItem("Select an option...");// Initialize each comboBox with a default "Select an option..." item

		connect(x, SIGNAL(currentIndexChanged(int)), this, SLOT(displayCourseName()));// and connect its selection to displayCourseName() 
	}

	// Connect the submit button to the course registration function
	connect(ui.SubmitButtomForCourse, &QPushButton::clicked, this, &CourseRegisterStudentPage::registerSelectedCourses);

	// Fill all the comboboxes with available course IDs from the system
	for (auto c : FilesClass::AllCourses) {
		QString id = QString::fromStdString(c.second.getCourseID());
		for (auto comboBox : comboBoxes) {
			comboBox->addItem(id);
		}
	}
} // Mahmoud Function

CourseRegisterStudentPage::~CourseRegisterStudentPage() {
	// Nothing to delete here since we didn't allocate on heap explicitly
} // Mahmoud Function

void CourseRegisterStudentPage::displayCourseName() {
	QComboBox* senderCombo = qobject_cast<QComboBox*>(sender());
	if (!senderCombo) return;

	QString selectedCourseID = senderCombo->currentText();
	QString courseName = "Course Not Found";
	QString creditHours = "N/A";

	// Search for the course in the global AllCourses map
	for (auto c : FilesClass::AllCourses) {
		if (QString::fromStdString(c.second.getCourseID()) == selectedCourseID) {
			courseName = QString::fromStdString(c.second.getCourseTitle());
			creditHours = QString::number(c.second.getCreditHours());
			break;
		}
	}

	// Update the proper labels based on which combo box was changed
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

	// Recalculate the total credit hours and update the progress bar
	updateTotalCreditHours();
} // Mahmoud Function

void CourseRegisterStudentPage::checkMaxCreditLimit(int total) {
	if (total > 21) {
		QMessageBox::warning(this, "Registration Error", "You cannot register because total credit hours exceed 21.");
	}
} // Mahmoud Function

void CourseRegisterStudentPage::updateTotalCreditHours() {
	int total = 0;
	QStringList selectedIDs;

	// Get selected course IDs from all combo boxes
	for (auto x : comboBoxes) {
		selectedIDs.append(x->currentText());
	}

	// Add up the credit hours for each selected course
	for (const QString& id : selectedIDs) {
		for (auto c : FilesClass::AllCourses) {
			if (QString::fromStdString(c.second.getCourseID()) == id) {
				total += c.second.getCreditHours();
				break;
			}
		}
	}

	// Update progress bar and validate the limit
	ui.progressBarTotalCreditHours->setValue(total);
	checkMaxCreditLimit(total);
} // Mahmoud Function

void CourseRegisterStudentPage::registerSelectedCourses() {
	// Check if student has already registered (based on special "none" if it  is non so he has no reg courses)
	if (FilesClass::toLower(student->getCourses().at(0)) != "none") {
		QMessageBox::warning(this, "Already Registered", "You have already registered courses. You cannot register again.");
		return;
	}
	// Loop through all the course selection combo boxes,

	QStringList selectedIDs;
	for (auto x : comboBoxes) {
		selectedIDs.append(x->currentText()); // and collect the currently selected course IDs into a QStringList
	}

	int totalCredits = 0;

	// Loop through selected courses and validate each
	for (const QString& qid : selectedIDs) {
		if (qid == "Select an option... ") continue;// Because start of combo box is Select an option some one clould register only one course so it donot but it in list 

		string courseID = qid.toStdString();
		if (courseID.empty()) continue;

		// Check if the course is actually Available 
		if (!student->CourseIsAvaliable(courseID, FilesClass::AllCourses)) {
			QMessageBox::warning(this, "Course Error", QString::fromStdString("Course not available: " + courseID));
			return;
		}

		// Check if the prerequisites are met
		if (!student->CheckPrerequisties(courseID, student->getCoursesCompleted(), FilesClass::AllCourses)) {
			QMessageBox::warning(this, "Prerequisite Error",
				QString::fromStdString("You must complete the required prerequisite before registering for " + courseID));
			return;
		}

		// Add credit hours for total calculation
		totalCredits += FilesClass::AllCourses[courseID].getCreditHours();
	}

	// Prevent registration if total exceeds 21 credit hours
	if (totalCredits > 21) {
		QMessageBox::warning(this, "Credit Limit Exceeded", "You cannot register for more than 21 credit hours.");
		return;
	}

	// Remove the placeholder "none" from the courses list
	student->getCoursesPtr()->pop_back();// hassan file hand when he gets non 

	// Finally, register the selected courses
	for (QString qid : selectedIDs) {
		string courseID = qid.toStdString();

		if (!courseID.empty() && courseID != "Select an option... ") {
			student->CourseRegisteration(courseID, FilesClass::AllCourses, student->getCoursesCompleted());
		}
		
	}

	// message that course reg done 
	QMessageBox::information(this, "Registration Complete", "Courses registered successfully!");

	// Save the action into the student’s history queue
	Student::history.push("Courses Registeration");

	// Keep history size at 5 actions max
	if (Student::history.size() > 5) {
		Student::history.pop();// jo function 
	}
} // Mahmoud Function

void CourseRegisterStudentPage::on_backBtn_clicked() {
	// Create and show the main menu
	StudentMainMenu* mainMenu = new StudentMainMenu();
	mainMenu->show();

	// Close the current window
	this->close();
}
