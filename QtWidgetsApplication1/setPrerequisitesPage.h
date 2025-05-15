#pragma once

#include <QMainWindow>
#include "ui_setPrerequisitesPage.h"


class setPrerequisitesPage : public QMainWindow
{
	Q_OBJECT

public:
	setPrerequisitesPage(QWidget *parent = nullptr);
	~setPrerequisitesPage();
	void onCourseChanged();
	void onPrereqChanged();
	void onSubmitClicked();
private slots:
    void on_Back_clicked();

private:
	Ui::setPrerequisitesPageClass ui;
};
