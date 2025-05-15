#pragma once

#include <QMainWindow>
#include "ui_AdminProfileInfoPage.h"

class AdminProfileInfoPage : public QMainWindow
{
	Q_OBJECT

public:
	AdminProfileInfoPage(QWidget *parent = nullptr);
	~AdminProfileInfoPage();

private slots:
    void on_backBtn_clicked();

    void on_editInfoBtn_clicked();

private:
	Ui::AdminProfileInfoPageClass ui;
};
