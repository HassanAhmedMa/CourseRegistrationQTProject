#pragma once

#include <QMainWindow>
#include "ui_reportStudent.h"

class reportStudent : public QMainWindow
{
	Q_OBJECT

public:
	reportStudent(QWidget *parent = nullptr);
	~reportStudent();

private:
	Ui::reportStudentClass ui;
};
