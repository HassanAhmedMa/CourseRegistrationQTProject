#pragma once

#include <QMainWindow>
#include "ui_StudentInformation.h"

class StudentInformation : public QMainWindow
{
	Q_OBJECT

public:
	StudentInformation(QWidget *parent = nullptr);
	~StudentInformation();
	void closeEvent(QCloseEvent* event);
private:
	Ui::StudentInformationClass ui;
};
