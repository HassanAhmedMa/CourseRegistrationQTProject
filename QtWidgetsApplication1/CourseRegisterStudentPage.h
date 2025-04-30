#pragma once

#include <QMainWindow>
#include "ui_CourseRegisterStudentPage.h"

class CourseRegisterStudentPage : public QMainWindow
{
	Q_OBJECT

public:
	CourseRegisterStudentPage(QWidget *parent = nullptr);
	~CourseRegisterStudentPage();

private:
	Ui::CourseRegisterStudentPageClass ui;
};
