#pragma once

#include <QMainWindow>
#include "ui_ViewStudentGradeAdminPage.h"
class ViewStudentGradeAdminPage : public QMainWindow
{
	Q_OBJECT

public:
	ViewStudentGradeAdminPage(QWidget *parent = nullptr);
	~ViewStudentGradeAdminPage();

private:
	Ui::ViewStudentGradeAdminPageClass* ui;


private slots:
	void displayGrades();
};
