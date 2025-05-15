#pragma once

#include <QMainWindow>
#include "ui_UploadEditStudentGradesPage.h"
#include <string>
#include <vector>
#include <Student.h>

class UploadEditStudentGradesPage : public QMainWindow
{
	Q_OBJECT

public:

	UploadEditStudentGradesPage( QWidget* parent = nullptr); //new constructor (ziad)
	vector<string> AdminGetCourses(string id);
	
	void adminSetStudentGrade(string studentId, bool isEdit);

	~UploadEditStudentGradesPage();

private slots:
	void onShowCoursesClicked(); //to display the list of registerded courses when the comboBox is clicked (ziad)
	void onUploadStudentGradeClicked();  // to upload the grade when the button is clicked (ziad)
	void onCourseSelected(); // Called when a course is selected
	void onEditStudentGradeClicked();
	void onBackToAdminMenuClicked();
	void loadStudentCourses(string studentId);


private:
	Ui::UploadEditStudentGradesPageClass ui;
	
};
