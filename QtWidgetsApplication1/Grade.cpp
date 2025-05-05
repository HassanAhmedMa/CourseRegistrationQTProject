#include "Grade.h"


Grade::Grade()
{

    courseID = "";
    courseName = "";
    semester = "";
    gradeValue = 0.0;
}

Grade::Grade(string id, string name, string sem, double grade) {
    courseID = id;
    courseName = name;
    semester = sem;
    gradeValue = grade;
}


void Grade::setCourseID(string id) {
    courseID = id;
}
void Grade::setCourseName(string name) {
    courseName = name;
}
void Grade::setSemester(string sem) {
    semester = sem;
}
void Grade::setGradeValue(double grade) {
    gradeValue = grade;
}



string Grade::getCourseID() {
    return courseID;
}
string Grade::getCourseName() {
    return courseName;
}
string Grade::getSemester() {
    return semester;
}
double Grade::getGradeValue() {
    return gradeValue;
}

