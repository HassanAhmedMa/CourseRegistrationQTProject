#pragma once

#include <QMainWindow>
#include "ui_StudentMainMenu.h"

class StudentMainMenu : public QMainWindow
{
	Q_OBJECT

public:
	StudentMainMenu(QWidget *parent = nullptr);
	~StudentMainMenu();

private:
	Ui::StudentMainMenuClass ui;
};
