//#pragma once
//
//#include <QMainWindow>
//#include "ui_CourseRegisterStudentPage.h"
//#include "course.h"
//#include <vector>
//#include "Student.h"
//class CourseRegisterStudentPage : public QMainWindow
//{
//	Q_OBJECT
//
//public:
//	CourseRegisterStudentPage(QWidget* parent = nullptr);
//	~CourseRegisterStudentPage();
//	vector<course> allCourses;
//	Student* student;
//
//private:
//	Ui::CourseRegisterStudentPageClass ui;
//
//private slots:
//	void displayCourseName();
//	void updateTotalCreditHours();
//	void checkMaxCreditLimit(int total);
//	void registerSelectedCourses();
//
//	
//
//
//};
#pragma once

#include <QMainWindow>
#include "ui_CourseRegisterStudentPage.h"
#include "course.h"
#include <vector>
#include "Student.h"

class CourseRegisterStudentPage : public QMainWindow
{
	Q_OBJECT

public:
	CourseRegisterStudentPage(QWidget* parent = nullptr);
	~CourseRegisterStudentPage();
	vector<QComboBox*> comboBoxes;
	std::vector<course*> allCourses;
	Student* student;

private:
	Ui::CourseRegisterStudentPageClass ui;

private slots:
	void displayCourseName();
	void updateTotalCreditHours();
	void checkMaxCreditLimit(int total);
	void registerSelectedCourses();
};

