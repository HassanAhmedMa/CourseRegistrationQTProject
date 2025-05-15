#pragma once

#include <QMainWindow>
#include "ui_uploadCourse.h"

class uploadCourse : public QMainWindow
{
	Q_OBJECT

public:
	uploadCourse(QWidget *parent = nullptr);
	~uploadCourse();

private slots:
    void on_uploadEditCourseBtn_clicked();

    void on_backBtn_clicked();

private:
	Ui::uploadCourseClass ui;
};
