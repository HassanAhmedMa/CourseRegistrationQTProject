#pragma once

#include <QMainWindow>
#include "ui_ViewStudentGradeAdminPage.h"
#include <string>
#include <vector>
#include <Student.h>
#include <iostream>	
#include <QPushbutton>
#include <qmessagebox.h>
class ViewStudentGradeAdminPage : public QMainWindow
{
	Q_OBJECT

public:
	ViewStudentGradeAdminPage(QWidget *parent = nullptr);
	vector<string> getStudentCourses(string studentId);
	~ViewStudentGradeAdminPage();




private slots:
//	void displayGrades();
	void onSearchClicked();
	void onShowGradeClicked();
	void onBackToAdminMenuClicked();

private:
	Ui::ViewStudentGradeAdminPageClass* ui;
};
