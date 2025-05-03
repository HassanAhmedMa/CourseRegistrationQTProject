#pragma once

#include <QMainWindow>
#include "ui_UploadEditStudentGradesPage.h"

class UploadEditStudentGradesPage : public QMainWindow
{
	Q_OBJECT

public:
	UploadEditStudentGradesPage(QWidget *parent = nullptr);
	~UploadEditStudentGradesPage();

private:
	Ui::UploadEditStudentGradesPageClass ui;
};
