#pragma once

#include <QMainWindow>
#include "ui_CourseRegisterStudentPage.h"
#include "course.h"
#include <vector>
class CourseRegisterStudentPage : public QMainWindow
{
	Q_OBJECT

public:
	CourseRegisterStudentPage(QWidget *parent = nullptr);
	~CourseRegisterStudentPage();
	vector<course> allCourses;

private:
	Ui::CourseRegisterStudentPageClass ui;

private slots:
	void displayCourseName();
};
