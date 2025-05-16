#pragma once

#include <QMainWindow>
#include "ui_viewGradesStudent.h"

class viewGradesStudent : public QMainWindow
{
	Q_OBJECT

public:
	viewGradesStudent(QWidget *parent = nullptr);
	~viewGradesStudent();
	void loadCompletedCourses();
	void on_courseSelected(QString selectedCourseName);

private:
	Ui::viewGradesStudentClass ui;

};
