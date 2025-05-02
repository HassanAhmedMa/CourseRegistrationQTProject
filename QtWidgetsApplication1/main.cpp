#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <RegisterPage.h>
#include "StudentMainMenu.h"
#include "CourseRegisterStudentPage.h" 
#include "reportStudent.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    StudentMainMenu h;
    reportStudent r;
    r.show();
    h.show();
    w.show();
    return a.exec();

}
