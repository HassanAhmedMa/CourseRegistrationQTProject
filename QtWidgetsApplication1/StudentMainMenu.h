#pragma once

#include <QMainWindow>
#include "ui_StudentMainMenu.h"
#include "CourseRegisterStudentPage.h"  // Include the course registration page header
#include "QtWidgetsApplication1.h" 
class StudentMainMenu : public QMainWindow
{
    Q_OBJECT

public:
    StudentMainMenu(QWidget* parent = nullptr);  // Constructor
    ~StudentMainMenu();  // Destructor

private slots:
    void openCourseRegistrationPage();  
    void logoutInStudentMenu(); 

private:
    Ui::StudentMainMenuClass ui;  // UI for the main menu
    CourseRegisterStudentPage* coursePage;  // Pointer to the course registration page
};

