#pragma once

#include <QMainWindow>
#include "ui_setPrerequisitesPage.h"

class setPrerequisitesPage : public QMainWindow
{
	Q_OBJECT

public:
	setPrerequisitesPage(QWidget *parent = nullptr);
	~setPrerequisitesPage();

private:
	Ui::setPrerequisitesPageClass ui;
};
