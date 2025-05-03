#pragma once

#include <QMainWindow>
#include "ui_StudentInfoPage.h"

class StudentInfoPage : public QMainWindow
{
	Q_OBJECT

public:
	StudentInfoPage(QWidget *parent = nullptr);
	~StudentInfoPage();

private:
	Ui::StudentInfoPageClass ui;
};
