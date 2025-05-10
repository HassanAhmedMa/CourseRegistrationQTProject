#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <RegisterPage.h>
#include "StudentMainMenu.h"
#include "CourseRegisterStudentPage.h" 
#include "reportStudent.h"
#include "AdminMenu.h"
#include "course.h"
int main(int argc, char *argv[])
{
    
    

    QApplication a(argc, argv);
    QtWidgetsApplication1 q;
   // AdminMenu m;
   // StudentMainMenu n;
    q.show();
  // n.show();
    
    AdminMenu m;
    StudentMainMenu n;
    n.show();
    CourseRegisterStudentPage p;
    p.show();
    m.show();
    //m.show();
   
    return a.exec();

}
