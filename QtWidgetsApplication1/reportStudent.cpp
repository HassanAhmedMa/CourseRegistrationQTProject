#include "reportStudent.h"
#include "ui_reportStudent.h"
#include "Student.h"
#include "course.h"
#include "Grade.h"
#include "StudentMainMenu.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include "FilesClass.h"

reportStudent::reportStudent(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Grab the currently logged-in student (ya3ni el user el da5al w 3ayez yshof el report)
    Student* student = FilesClass::loggedInStudent;

    // Fill in the top fields with name, ID, and GPA — basic info
    ui.lineEdit_2->setText(QString::fromStdString(student->getName()));
    ui.lineEdit_3->setText(QString::number(student->getId()));
    ui.lineEdit->setText(QString::number(student->getOverallGPA(), 'f', 2));

    // Set up the table to show course name, semester, and grade
    ui.tableWidget->setColumnCount(3);
    QStringList headers = { "Course Name", "Semester", "Grades" };
    ui.tableWidget->setHorizontalHeaderLabels(headers);

    // We set the number of rows depending on how many completed courses the student has
    ui.tableWidget->setRowCount(student->getCoursesCompleted().size());

    // Make sure they’ve actually completed courses (none howa ano ma3ndoosh coursat completed 3shan kda bnshouf hwa kda wla la2 )
    if (FilesClass::toLower(student->getCoursesCompleted().at(0)) != "none") {
        int row = 0;

        // Loop over each completed course and drop it into the table
        for (string courseID : student->getCoursesCompleted()) {
            Grade* g = student->getGradeObject(courseID);

            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(g->getCourseName()));
            QTableWidgetItem* semesterItem = new QTableWidgetItem(QString::fromStdString(g->getSemester()));
            QTableWidgetItem* gradeItem = new QTableWidgetItem(QString::number(g->getGradeValue(), 'f', 2));

            // by5ele user  me3dlesh fe gadwal 
            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
            semesterItem->setFlags(semesterItem->flags() & ~Qt::ItemIsEditable);
            gradeItem->setFlags(gradeItem->flags() & ~Qt::ItemIsEditable);

            // Stuff the items into the table
            ui.tableWidget->setItem(row, 0, nameItem);
            ui.tableWidget->setItem(row, 1, semesterItem);
            ui.tableWidget->setItem(row, 2, gradeItem);
            row++;
        }
    }

    // When the user clicks "Print", we’ll call the saveReportAsText function
    connect(ui.printButton, &QPushButton::clicked, this, &reportStudent::saveReportAsText);
    connect(ui.backButton, &QPushButton::clicked, this, &reportStudent::on_backBtn_clicked);// Back Buttom Funtion
} // Mahmoud Function 

reportStudent::~reportStudent()
{
    
} 

// This function handles exporting the report to a .txt file that the user chooses
void reportStudent::saveReportAsText()
{
    // ask usser where would yo like to save 
    QString filePath = QFileDialog::getSaveFileName(this, "Save Report", "", "Text Files (*.txt)");

    if (filePath.isEmpty())
        return; // user changed their mind and cancelled 

   
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file to write.");
        return;
    }

    QTextStream out(&file);

    // allingment of Report 
    out << "==== Student Report ====\n";
    out << "Name: " << ui.lineEdit_2->text() << "\n";
    out << "ID: " << ui.lineEdit_3->text() << "\n";
    out << "GPA: " << ui.lineEdit->text() << "\n\n";

    out << "Course Name\tSemester\tGrade\n";
    out << "------------------------------------------\n";

    int rows = ui.tableWidget->rowCount();
    for (int i = 0; i < rows; ++i) {
        QString course = ui.tableWidget->item(i, 0)->text();
        QString semester = ui.tableWidget->item(i, 1)->text();
        QString grade = ui.tableWidget->item(i, 2)->text();
        out << course << "\t" << semester << "\t" << grade << "\n";
    }

    file.close(); // Always close the file or Windows donot make a problem in windwos 
    QMessageBox::information(this, "Saved", "Report saved successfully.");

    // Push the action to student history (el tracking beta3 el student el 3amal eh)
    Student::history.push("Report generation");
    if (Student::history.size() > 5) {
        Student::history.pop(); // keep it at max 5 items// jooo function
    }
} //Mahmoud Function (AI helped us align the report formatting )

void reportStudent::on_backBtn_clicked() {
    // Create and show the main menu


    // Close the current window
    this->close();
}


