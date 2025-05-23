
#pragma once

#include <QMainWindow>
#include "ui_CourseRegisterStudentPage.h"
#include "course.h"
#include <vector>
#include "Student.h"
#include "FilesClass.h"
class CourseRegisterStudentPage : public QMainWindow
{
	Q_OBJECT

public:
	CourseRegisterStudentPage(QWidget* parent = nullptr);
	~CourseRegisterStudentPage();
	vector<QComboBox*> comboBoxes;
	Student* student = FilesClass::loggedInStudent;

private:
	Ui::CourseRegisterStudentPageClass ui;

private slots:
	void displayCourseName();
	void updateTotalCreditHours();
	void checkMaxCreditLimit(int total);
	void registerSelectedCourses();
	void on_backBtn_clicked();
};

