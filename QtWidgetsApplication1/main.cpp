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
    c.readCoursesData();
    c.readStudentsData();
    displayAllStudentsDataFromFile(c);
    
    QApplication a(argc, argv);
    QtWidgetsApplication1 q;
    AdminMenu m;
   //StudentMainMenu n;
    q.show();
   //n.show();
   // 

   //
   //n.show();
   //CourseRegisterStudentPage p;
   //p.show();
   //m.show();
    m.show();
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, [&c]() {
        c.writeStudentData();
        c.writeCoursesData();
    });
   
    return a.exec();

}



void displayAllStudentsDataFromFile(FilesClass& c) {
    for (auto& stud : c.demoStudentsMap) {
        //qDebug() << stud.second.getCourses();
        //qDebug() << stud.second.getCoursesPtr();
        //qDebug() << stud.second.getCoursesCompleted();
        //qDebug() << stud.second.getName();
        //qDebug() << stud.second.getPassword();
        //qDebug() << stud.second.getUsername();
        //qDebug() << stud.second.getId();
        //qDebug() << c.AllCourses[stud.first].getCourseID();
        //qDebug() << c.AllCourses[stud.first].getCourseTitle();
        //qDebug() << c.AllCourses[stud.first].getInstructorName();
        //qDebug() << c.AllCourses[stud.first].getCreditHours();
        //qDebug() << c.AllCourses[stud.first].getSyllabus();
        //qDebug() << c.AllCourses[stud.first].getPreRequisuteID();



    }
}
