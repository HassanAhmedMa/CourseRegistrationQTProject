//#include "reportStudent.h"
//#include "ui_reportStudent.h"
//#include "Student.h"
//#include "course.h"
//#include "Grade.h"
//
//reportStudent::reportStudent(QWidget* parent)
//    : QMainWindow(parent)
//{
//    ui.setupUi(this);
//
//
//    Student student("user1", "pass", "Mahmoud Bahaa", 1234);
//
//
//    student.addCourseCompleted("MATH101");
//    student.addGrade("MATH101", "Calculus I", "Fall 2023", 3.3);
//
//    student.addCourseCompleted("PHYS101");
//    student.addGrade("PHYS101", "Physics I", "Fall 2023", 3.0);
//
//    student.addCourseCompleted("CHEM101");
//    student.addGrade("CHEM101", "General Chemistry", "Fall 2023", 2.7);
//
//    student.addCourseCompleted("CS101");
//    student.addGrade("CS101", "Intro to Programming", "Spring 2024", 3.8);
//
//    student.addCourseCompleted("CS102");
//    student.addGrade("CS102", "Data Structures", "Spring 2024", 3.6);
//
//    student.addCourseCompleted("HIST201");
//    student.addGrade("HIST201", "Modern History", "Spring 2024", 2.9);
//
//    student.addCourseCompleted("ENG101");
//    student.addGrade("ENG101", "English Composition", "Fall 2024", 3.2);
//
//    student.addCourseCompleted("STAT202");
//    student.addGrade("STAT202", "Statistics", "Fall 2024", 3.4);
//
//    student.addCourseCompleted("CS201");
//    student.addGrade("CS201", "Algorithms", "Spring 2025", 3.9);
//
//    student.addCourseCompleted("ELEC220");
//    student.addGrade("ELEC220", "Digital Logic", "Spring 2025", 3.1);
//
//
//
//    ui.lineEdit_2->setText(QString::fromStdString(student.getName()));
//    ui.lineEdit_3->setText(QString::number(student.getId()));
//    ui.lineEdit->setText(QString::number(student.getOverallGPA(), 'f', 2));
//
//
//    ui.tableWidget->setColumnCount(3);
//    QStringList headers = { "Course Name", "Semester", "Grades" };
//    ui.tableWidget->setHorizontalHeaderLabels(headers);
//    ui.tableWidget->setRowCount(student.getCoursesCompleted().size());
//
//    // Fill rows with grades
//    int row = 0;
//    for (string courseID : student.getCoursesCompleted()) {
//        Grade g = student.getGradeObject(courseID);
//
//        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(g.getCourseName()));
//        QTableWidgetItem* semesterItem = new QTableWidgetItem(QString::fromStdString(g.getSemester()));
//        QTableWidgetItem* gradeItem = new QTableWidgetItem(QString::number(g.getGradeValue(), 'f', 2));
//
//        ui.tableWidget->setItem(row, 0, nameItem);
//        ui.tableWidget->setItem(row, 1, semesterItem);
//        ui.tableWidget->setItem(row, 2, gradeItem);
//        row++;
//    }
//}
//
//reportStudent::~reportStudent()
//{
//
//}
#include "reportStudent.h"
#include "ui_reportStudent.h"
#include "Student.h"
#include "course.h"
#include "Grade.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>




reportStudent::reportStudent(QWidget* parent)
    : QMainWindow(parent) 
{
    ui.setupUi(this);

    // Dummy student
    Student student("user1", "pass", "Mahmoud Bahaa", 1234);

    student.addCourseCompleted("MATH101");
    student.addGrade("MATH101", "Calculus I", "Fall 2023", 3.3);

    student.addCourseCompleted("PHYS101");
    student.addGrade("PHYS101", "Physics I", "Fall 2023", 3.0);

    student.addCourseCompleted("CHEM101");
    student.addGrade("CHEM101", "General Chemistry", "Fall 2023", 2.7);

    student.addCourseCompleted("CS101");
    student.addGrade("CS101", "Intro to Programming", "Spring 2024", 3.8);

    student.addCourseCompleted("CS102");
    student.addGrade("CS102", "Data Structures", "Spring 2024", 3.6);

    student.addCourseCompleted("HIST201");
    student.addGrade("HIST201", "Modern History", "Spring 2024", 2.9);

    student.addCourseCompleted("ENG101");
    student.addGrade("ENG101", "English Composition", "Fall 2024", 3.2);

    student.addCourseCompleted("STAT202");
    student.addGrade("STAT202", "Statistics", "Fall 2024", 3.4);

    student.addCourseCompleted("CS201");
    student.addGrade("CS201", "Algorithms", "Spring 2025", 3.9);

    student.addCourseCompleted("ELEC220");
    student.addGrade("ELEC220", "Digital Logic", "Spring 2025", 3.1);

    // Display in UI
    ui.lineEdit_2->setText(QString::fromStdString(student.getName()));
    ui.lineEdit_3->setText(QString::number(student.getId()));
    ui.lineEdit->setText(QString::number(student.getOverallGPA(), 'f', 2));
    

    // Table setup
    ui.tableWidget->setColumnCount(3);
    QStringList headers = { "Course Name", "Semester", "Grades" };
    ui.tableWidget->setHorizontalHeaderLabels(headers);
    ui.tableWidget->setRowCount(student.getCoursesCompleted().size());

    int row = 0;
    for (string courseID : student.getCoursesCompleted()) {
        Grade g = student.getGradeObject(courseID);

        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(g.getCourseName()));
        QTableWidgetItem* semesterItem = new QTableWidgetItem(QString::fromStdString(g.getSemester()));
        QTableWidgetItem* gradeItem = new QTableWidgetItem(QString::number(g.getGradeValue(), 'f', 2));

        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        semesterItem->setFlags(semesterItem->flags() & ~Qt::ItemIsEditable);
        gradeItem->setFlags(gradeItem->flags() & ~Qt::ItemIsEditable);

        ui.tableWidget->setItem(row, 0, nameItem);
        ui.tableWidget->setItem(row, 1, semesterItem);
        ui.tableWidget->setItem(row, 2, gradeItem);
        row++;
    }

    // Connect print button
    connect(ui.printButton, &QPushButton::clicked, this, &reportStudent::saveReportAsText);
}

reportStudent::~reportStudent()
{
    
}
void reportStudent::saveReportAsText()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Report", "", "Text Files (*.txt)");

    if (filePath.isEmpty())
        return;

    QFile file("C:\project ds final isa\QtWidgetsApplication1\printableReport.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file to write.");
        return;
    }

    QTextStream out(&file);

    // Header
    out << "==== Student Report ====\n";
    out << "Name: " << ui.lineEdit_2->text() << "\n";
    out << "ID: " << ui.lineEdit_3->text() << "\n";
    out << "GPA: " << ui.lineEdit->text() << "\n\n";

    // Table header
    out << "Course Name\tSemester\tGrade\n";
    out << "------------------------------------------\n";

    int rows = ui.tableWidget->rowCount();
    for (int i = 0; i < rows; ++i) {
        QString course = ui.tableWidget->item(i, 0)->text();
        QString semester = ui.tableWidget->item(i, 1)->text();
        QString grade = ui.tableWidget->item(i, 2)->text();
        out << course << "\t" << semester << "\t" << grade << "\n";
    }

    file.close();
    QMessageBox::information(this, "Saved", "Report saved successfully.");
}


// Printing function
//void reportStudent::printReport()
//{
//    QTextDocument doc;
//    QString html;
//
//    html += "<h2>Student Report</h2>";
//    html += "<p><b>Name:</b> " + ui.lineEdit_2->text() + "</p>";
//    html += "<p><b>ID:</b> " + ui.lineEdit_3->text() + "</p>";
//    html += "<p><b>GPA:</b> " + ui.lineEdit->text() + "</p>";
//    html += "<br><table border='1' cellspacing='0' cellpadding='4'>";
//    html += "<tr><th>Course Name</th><th>Semester</th><th>Grade</th></tr>";
//
//    int rowCount = ui.tableWidget->rowCount();
//    for (int i = 0; i < rowCount; ++i) {
//        QString course = ui.tableWidget->item(i, 0)->text();
//        QString semester = ui.tableWidget->item(i, 1)->text();
//        QString grade = ui.tableWidget->item(i, 2)->text();
//        html += "<tr><td>" + course + "</td><td>" + semester + "</td><td>" + grade + "</td></tr>";
//    }
//
//    html += "</table>";
//
//    doc.setHtml(html);
//
//    QPrinter printer;
//    QPrintDialog dialog(&printer, this);
//    if (dialog.exec() == QDialog::Accepted) {
//        doc.print(&printer);
//    }
//}
