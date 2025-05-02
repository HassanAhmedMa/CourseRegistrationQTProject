#pragma once

#include <QMainWindow>
#include "ui_viewGradesStudent.h"

class viewGradesStudent : public QMainWindow
{
	Q_OBJECT

public:
	viewGradesStudent(QWidget *parent = nullptr);
	~viewGradesStudent();

private:
	Ui::viewGradesStudentClass ui;
};
