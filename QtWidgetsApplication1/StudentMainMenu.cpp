#include "StudentMainMenu.h"
#include "ui_StudentMainMenu.h"
#include "CourseRegisterStudentPage.h"  // Include the header for the course registration page
#include "QtWidgetsApplication1.h"
#include "viewGradesStudent.h"
#include "reportStudent.h"




StudentMainMenu::StudentMainMenu(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);  // Set up the UI

    // Initialize the coursePage pointer to nullptr
    coursePage = nullptr;
    viewGradesPage = nullptr;
    reportPage = nullptr;

    // Connect the "Course Registration" button to the slot
    connect(ui.CourseRegisterationButton, &QPushButton::clicked, this, &StudentMainMenu::openCourseRegistrationPage);
    connect(ui.LogoutInStudentMenu, &QPushButton::clicked, this, &StudentMainMenu::logoutInStudentMenu);
    connect(ui.ViewGradeButtonStudentMainPage, &QPushButton::clicked, this, &StudentMainMenu::openViewGradesPage);
    connect(ui.MakeReport, &QPushButton::clicked, this, &StudentMainMenu::openreport);
    
}

StudentMainMenu::~StudentMainMenu()
{

}

void StudentMainMenu::openCourseRegistrationPage()
{
    // If the course page is not already open, create it and show it
    if (!coursePage) {
        coursePage = new CourseRegisterStudentPage(this);  // Create the course registration page
    }

    // Show the course registration page
    coursePage->show();
}
void StudentMainMenu::logoutInStudentMenu()
{

    this->close();
    QtWidgetsApplication1* newWindow = new QtWidgetsApplication1();  // Assuming this is your new window class
    newWindow->show();
}
void StudentMainMenu::openViewGradesPage()
{
    // Create the viewGradesStudent page if it's not already created
    if (!viewGradesPage) {
        viewGradesPage = new viewGradesStudent(this);  // Create the grades page
    }

    // Show the grades page
    viewGradesPage->show();
}
void StudentMainMenu::openreport()
{
    // Create the viewGradesStudent page if it's not already created
    if (!reportPage) {
        reportPage = new reportStudent(this);  // Correct class name
        
    }

    // Show the report page
    reportPage->show();
}
