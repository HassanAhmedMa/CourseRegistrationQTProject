#include "setPrerequisitesPage.h"
#include "course.h"
#include "Student.h"
#include"Admin.h"
#include <qmessagebox.h>
#include <map>
#include <iostream>
#include <qpushbutton.h>
#include <unordered_set>
#include<QtWidgetsApplication1.h>
#include "FilesClass.h" 
using namespace std;
map<string, course> allCourses;
setPrerequisitesPage::setPrerequisitesPage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*course* phy101 = new course("physics 101", "PHY101", "Basic Physics Course", 3, "Dr. Smith", nullptr);
	course* phy201 = new course("physics 201", "PHY201", "Intermediate Physics", 4, "Dr. Johnson", phy101);
	course* sp301 = new course("SP 301", "SP301", "Advanced Programming", 3, "Dr. Lee", phy201);
	course* OOP401 = new course("OOP 401", "OOP301", "Intermediate Programming", 3, "Dr. Lee", sp301);
	QList<course*> courseList;
	courseList << phy101 << phy201 << sp301<< OOP401;
	for (course* c : courseList) {
		QString id = QString::fromStdString(c->getCourseID());
		ui.comboBoxSelectCoursePrereq->addItem(id);
		ui.comboBoxAddCourseprereq->addItem(id);
	}*/



	/*unordered_set<string> addedCourses;
	QList<course*> courseList;

	for (const auto& [studentID, studentPtr] : Filesclass::AllStudents) {
		for (course* c : studentPtr->getCourses()) {
			if (c && addedCourses.find(c->getCourseID()) == addedCourses.end()) {
				addedCourses.insert(c->getCourseID());
				courseList.append(c);
			}
		}*/
	//}

	Admin* admin = new Admin(1231, "System Admin", "Admin", "Admin123");
	/*for (const auto& pair : courses) {
		std::string courseID = pair.first;
		ui.comboBoxSelectCoursePrereq->addItem(QString::fromStdString(courseID));
		ui.comboBoxAddCourseprereq->addItem(QString::fromStdString(courseID));

	}*/

	for (auto pair : FilesClass::AllCourses) {
		string courseID = pair.first;
		QString qCourseID = QString::fromStdString(courseID);
		ui.comboBoxSelectCoursePrereq->addItem(qCourseID);
		ui.comboBoxAddCourseprereq->addItem(qCourseID);
	}
	

	connect(ui.comboBoxSelectCoursePrereq, &QComboBox::currentIndexChanged, this, &setPrerequisitesPage::onCourseChanged);
	connect(ui.comboBoxAddCourseprereq, SIGNAL(currentIndexChanged(int)), this, SLOT(onPrereqChanged()));
	connect(ui.SubmitPrerequisiteBtn, &QPushButton::clicked, this, &setPrerequisitesPage::onSubmitClicked);

	if ((FilesClass::AllCourses[ui.comboBoxSelectCoursePrereq->currentText().toStdString()].getPrerequisite() != nullptr)) {

		
		ui.CurrentCourseLabel->setText("prerequisite Course : " + QString::fromStdString(FilesClass::AllCourses[ui.comboBoxSelectCoursePrereq->currentText().toStdString()].getPrerequisite()->getCourseID()));
	}
	else

	{
		ui.CurrentCourseLabel->setText("prerequisite Course : No prerequisite ");
	}
}

setPrerequisitesPage::~setPrerequisitesPage()
{}
void setPrerequisitesPage::onCourseChanged()
{
	QString selected = ui.comboBoxSelectCoursePrereq->currentText();
	qDebug() << "Selected course:" << selected;
	if ((FilesClass::AllCourses[selected.toStdString()].getPrerequisite() != nullptr)) {

		ui.CurrentCourseLabel->setText("prerequisite Course : " + QString::fromStdString(FilesClass::AllCourses[selected.toStdString()].getPrerequisite()->getCourseID()));
	}
	else

	{
		ui.CurrentCourseLabel->setText("prerequisite Course : No prerequisite " );
	}
}	

void setPrerequisitesPage::onPrereqChanged()
{
	QString selected = ui.comboBoxAddCourseprereq->currentText();

}

void setPrerequisitesPage::onSubmitClicked()
{
	QString selectedID = ui.comboBoxSelectCoursePrereq->currentText();
	QString prerequisiteID = ui.comboBoxAddCourseprereq->currentText();


	if (selectedID == prerequisiteID) {
		QMessageBox::warning(this, "Invalid", "A course cannot be its own prerequisite.");
		return;
	}

	qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	Admin* admin = new Admin(1231, "System Admin", "Admin", "Admin123");
	admin->setPreRequisites(FilesClass::AllCourses, selectedID.toStdString(), prerequisiteID.toStdString());
	ui.CurrentCourseLabel->setText("prerequisite Course : " + QString::fromStdString(FilesClass::AllCourses[ui.comboBoxSelectCoursePrereq->currentText().toStdString()].getPrerequisite()->getCourseID()));
	QMessageBox::information(this, "Success", "Prerequisite set successfully.");
}


void setPrerequisitesPage::on_Back_clicked()
{
	this->close();
}

