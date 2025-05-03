#pragma once

#include <QMainWindow>
#include "ui_AdminProfileInfoPage.h"

class AdminProfileInfoPage : public QMainWindow
{
	Q_OBJECT

public:
	AdminProfileInfoPage(QWidget *parent = nullptr);
	~AdminProfileInfoPage();

private:
	Ui::AdminProfileInfoPageClass ui;
};
