#pragma once

#include <QMainWindow>
#include "ui_uploadStudentCompletedCourse.h"

#include<string>
#include"string"
using namespace std;

class uploadStudentCompletedCourse : public QMainWindow
{
	Q_OBJECT

public:
	uploadStudentCompletedCourse(QWidget* parent = nullptr);
	~uploadStudentCompletedCourse();

private slots:


	void on_uploadStudentCompletedCourseBtn_clicked();

	void on_backBtn_clicked();

	void setComboBoxItems(string studentId);

	void on_searchBtn_clicked();

private:
	Ui::uploadStudentCompletedCourseClass  ui;
};
