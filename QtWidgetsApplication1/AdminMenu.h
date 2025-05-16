#pragma once

#include <QMainWindow>
#include "ui_AdminMenu.h"

class AdminMenu : public QMainWindow
{
	Q_OBJECT

public:
	AdminMenu(QWidget *parent = nullptr);
	~AdminMenu();

private slots:


    void on_viewProfile_Btn_clicked();

    void on_viewStudentGrades_Btn_clicked();

    void on_uploadGrades_Btn_clicked();

    void on_setPrerequisites_Btn_clicked();

	void on_UploadCourseAdminMenuBtn_clicked();

	void on_UploadCompletedCourseAdminMenuBtn_clicked();

private:
	Ui::AdminMenuClass ui;
};
