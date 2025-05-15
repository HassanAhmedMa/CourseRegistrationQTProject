#pragma once

#include <QMainWindow>
#include "ui_removeStudentFromCourse.h"

class removeStudentFromCourse : public QMainWindow
{
	Q_OBJECT

public:
	removeStudentFromCourse(QWidget *parent = nullptr);
	~removeStudentFromCourse();

private slots:
    void on_removeStudentFromCourseBtn_clicked();

    void on_backBtn_clicked();

private:
	Ui::removeStudentFromCourseClass ui;
	
};
