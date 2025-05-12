#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <RegisterPage.h>
#include "StudentMainMenu.h"
#include "CourseRegisterStudentPage.h" 
#include "reportStudent.h"
#include "AdminMenu.h"
#include "course.h"
#include "FilesClass.h"
void displayAllStudentsDataFromFile(FilesClass& c);
int main(int argc, char *argv[])
{
    
    
    FilesClass c;
    c.readStudentsData();
    displayAllStudentsDataFromFile(c);
    QApplication a(argc, argv);
    QtWidgetsApplication1 q;
   // AdminMenu m;
   // StudentMainMenu n;
    q.show();
  // n.show();
    
    /////////////AdminMenu m;
    /////////////StudentMainMenu n;
    /////////////n.show();
    /////////////CourseRegisterStudentPage p; commented out by ~Hassan
    /////////////p.show();
    /////////////m.show();
    //m.show();
   
    return a.exec();

}



void displayAllStudentsDataFromFile(FilesClass& c) {
    for (auto stud : c.AllStudents) {
        qDebug() << stud.getCourses();
        qDebug() << stud.getCoursesCompleted();
        qDebug() << stud.getName();
        qDebug() << stud.getPassword();
        qDebug() << stud.getUsername();
        qDebug() << stud.getId();



    }
}
