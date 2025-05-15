#include "UploadEditStudentGradesPage.h"
#include <Student.h>
#include <iostream>
#include <QPushButton>
#include <QMessageBox>
#include <AdminMenu.h>
#include <FilesClass.h>

using namespace std;

UploadEditStudentGradesPage::UploadEditStudentGradesPage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Fill semester combobox
    ui.SemstersComboBox->addItem("Spring");
    ui.SemstersComboBox->addItem("Summer");
    ui.SemstersComboBox->addItem("Fall");

    // Fill years combobox
    for (int year = 1990; year <= 2100; ++year) {
        ui.yearsComboBox->addItem(QString::number(year));
    }

    connect(ui.showCourses, &QPushButton::clicked, this, &UploadEditStudentGradesPage::onShowCoursesClicked);
    //connect(ui.showCourses, &QPushButton::clicked, this, &UploadEditStudentGradesPage::loadStudentCourses);
    connect(ui.UploadStudentGradeBtn, &QPushButton::clicked, this, &UploadEditStudentGradesPage::onUploadStudentGradeClicked);
    connect(ui.comboBoxCourse, &QComboBox::currentTextChanged, this, &UploadEditStudentGradesPage::onCourseSelected);
    connect(ui.EditStudentGradeBtn, &QPushButton::clicked, this, &UploadEditStudentGradesPage::onEditStudentGradeClicked);
    connect(ui.BackPushBtn, &QPushButton::clicked, this, &UploadEditStudentGradesPage::onBackToAdminMenuClicked);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UploadEditStudentGradesPage::onCourseSelected() {
    string studentId = ui.UploadEditIDTextField->text().toStdString();
    if (FilesClass::demoStudentsMap.find(studentId) == FilesClass::demoStudentsMap.end()) return;

    QString courseID = ui.comboBoxCourse->currentText();
    if (courseID.isEmpty()) return;

    Student* student = &FilesClass::demoStudentsMap[studentId];
    string courseIDStr = courseID.toStdString();

    string title, semester;
    float grade;
    bool hasGrade = student->getGradeDetails(courseIDStr, title, semester, grade);

    if (hasGrade) {
        ui.UploadEditGradeTextField->setText(QString::number(grade));
        ui.UploadStudentGradeBtn->setEnabled(false);
        ui.EditStudentGradeBtn->setEnabled(true);

        QStringList parts = QString::fromStdString(semester).split(" ");
        if (parts.size() == 2) {
            ui.SemstersComboBox->setCurrentText(parts[0]);
            ui.yearsComboBox->setCurrentText(parts[1]);
        }
    }
    else {
        ui.UploadEditGradeTextField->clear();
        ui.SemstersComboBox->setCurrentIndex(-1);
        ui.yearsComboBox->setCurrentIndex(-1);
        ui.UploadStudentGradeBtn->setEnabled(true);
        ui.EditStudentGradeBtn->setEnabled(false);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UploadEditStudentGradesPage::onEditStudentGradeClicked()
{
    string studentId = ui.UploadEditIDTextField->text().toStdString();
    adminSetStudentGrade(studentId, true);
    cout << "Edit button clicked!" << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UploadEditStudentGradesPage::onBackToAdminMenuClicked()
{
    AdminMenu* adminMenu = new AdminMenu(this);
    adminMenu->show();
    this->close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> UploadEditStudentGradesPage::AdminGetCourses(string id)
{
    vector<string> temp;
    for (auto x : FilesClass::demoStudentsMap) {
        if (x.first == id) {
            QMessageBox::information(this, "Success", "Found Student");
            return x.second.getCourses();
        }
    }
    QMessageBox::warning(this, "Failure", "Student not found !");
    return temp;
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UploadEditStudentGradesPage::loadStudentCourses(string studentId) {
    vector<string> courseList = AdminGetCourses(studentId);
    ui.comboBoxCourse->clear();
    if (!courseList.empty()) {
        qDebug() << courseList;
    }
    for (auto x : courseList) {
        ui.comboBoxCourse->addItem(QString::fromStdString(x));
    }
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UploadEditStudentGradesPage::onUploadStudentGradeClicked() {
    string studentId = ui.UploadEditIDTextField->text().toStdString();
    if (ui.UploadEditGradeTextField->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the new grade.");
        return;
    }
    adminSetStudentGrade(studentId, false);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UploadEditStudentGradesPage::adminSetStudentGrade(string studentId, bool isEdit)
{
    if (FilesClass::demoStudentsMap.find(studentId) == FilesClass::demoStudentsMap.end()) {
        cout << "Student not found." << endl;
        return;
    }

    QString courseID = ui.comboBoxCourse->currentText();
    QString semester = ui.SemstersComboBox->currentText();
    QString year = ui.yearsComboBox->currentText();
    QString gradeStr = ui.UploadEditGradeTextField->text();

    if (courseID.isEmpty() || semester.isEmpty() || year.isEmpty() || gradeStr.isEmpty()) {
        cout << "Please fill all fields." << endl;
        return;
    }

    bool ok;
    double gradeValue = gradeStr.toDouble(&ok);
    if (!ok || gradeValue < 0 || gradeValue > 100) {
        QMessageBox::warning(this, "Invalid Grade", "Grade must be a number between 0 and 100");
        return;
    }

    string semesterYear = semester.toStdString() + " " + year.toStdString();
    string courseIDStr = courseID.toStdString();
    string courseTitle = "Unknown Course";

    if (FilesClass::AllCourses.find(courseIDStr) == FilesClass::AllCourses.end()) {
        QMessageBox::warning(this, "Invalid Course", "Course ID not found.");
        return;
    }

    courseTitle = FilesClass::AllCourses[courseIDStr].getCourseTitle();
    Student* student = &FilesClass::demoStudentsMap[studentId];
    student->addGrade(courseIDStr, courseTitle, semesterYear, gradeValue);

    if (isEdit) {
        QMessageBox::information(this, "Success", "Grade edited successfully.");
    }
    else {
        QMessageBox::information(this, "Success", "Grade uploaded successfully.");
    }

    ui.UploadEditGradeTextField->clear();
    ui.UploadEditIDTextField->clear();
    ui.comboBoxCourse->clear();
    ui.SemstersComboBox->setCurrentIndex(-1);
    ui.yearsComboBox->setCurrentIndex(-1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UploadEditStudentGradesPage::onShowCoursesClicked() {

    string id = ui.UploadEditIDTextField->text().toStdString();
    loadStudentCourses(id);
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UploadEditStudentGradesPage::~UploadEditStudentGradesPage() {}
