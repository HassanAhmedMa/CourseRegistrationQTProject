#pragma once

#include <QMainWindow>
#include "ui_RegisterPage.h"

class RegisterPage : public QMainWindow
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = nullptr);
	~RegisterPage();

private:
	Ui::RegisterPageClass ui;

private slots:
	void on_pushButton_clicked();
};
