#pragma once

#include <QWidget>
#include "ui_StudentHistory.h"
#include<queue>
#include<string>

class StudentHistory : public QWidget
{
	Q_OBJECT

private slots:
	void backbtnclicked();

public:
	StudentHistory(QWidget *parent = nullptr);
	void displayStudentHistory(std::queue<std::string>historyqueue);
	
	~StudentHistory();

private:
	Ui::StudentHistoryClass ui;
};
