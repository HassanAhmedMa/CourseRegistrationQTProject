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
    
    AdminMenu m;
    StudentMainMenu n;
    n.show();
    
    m.show();
   
    return a.exec();

}
