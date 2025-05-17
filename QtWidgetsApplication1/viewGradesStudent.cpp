
#include "viewGradesStudent.h"
#include "FilesClass.h"
#include <QString>
#include <QComboBox>
#include "reportStudent.h"
#include "StudentMainMenu.h"

viewGradesStudent::viewGradesStudent(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.Back, &QPushButton::clicked, this, &viewGradesStudent::on_backBtn_clicked);
    loadCompletedCourses();
    connect(ui.courseNames, &QComboBox::currentTextChanged, this, &viewGradesStudent::on_courseSelected);
    
    

}

viewGradesStudent::~viewGradesStudent()
{
}

void viewGradesStudent::loadCompletedCourses() {
    // Ensure a student is logged in
    if (!FilesClass::loggedInStudent)
        return;

    // Clear existing items in the combo box
    ui.courseNames->clear();

    // Get completed course IDs
    std::vector<std::string> completedCourses = FilesClass::loggedInStudent->getCoursesCompleted();

    // Add each course name to the combo box
    for (std::string courseID : completedCourses) {
        Grade* gradeObj = FilesClass::loggedInStudent->getGradeObject(courseID);
        if (gradeObj) {
            QString courseName = QString::fromStdString(gradeObj->getCourseName());
            ui.courseNames->addItem(courseName);
        }
    }
}

void viewGradesStudent::on_courseSelected(QString selectedCourseName) {
    // Make sure a student is logged in before proceeding
    if (!FilesClass::loggedInStudent)
        return;

    // Get the list of completed courses
    std::vector<std::string> completedCourses = FilesClass::loggedInStudent->getCoursesCompleted();

    // Go through each course to find the one matching the selected name
    for (std::string courseID : completedCourses) {
        Grade* gradeObj = FilesClass::loggedInStudent->getGradeObject(courseID);

        // If the grade object is found and the name matches, fill the fields
        if (gradeObj && QString::fromStdString(gradeObj->getCourseName()) == selectedCourseName) {
            ui.CourseNameLineEdit->setText(QString::fromStdString(gradeObj->getCourseName()));
            ui.semester->setText(QString::fromStdString(gradeObj->getSemester()));
            ui.SemesterGpa->setText(QString::number(gradeObj->getGradeValue(), 'f', 2));
            break;
        }
    }
    Student::history.push("view Student grade");
    if (Student::history.size() > 5) {
        Student::history.pop();
    }
}
void  viewGradesStudent::on_backBtn_clicked() {
    // Create and show the main menu

    // Close the current window
    this->close();
}