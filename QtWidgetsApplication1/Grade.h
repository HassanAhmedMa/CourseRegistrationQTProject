#pragma once
#include<string>
using namespace std;
class Grade
{
private:
    string courseID;
    string courseName;
    string semester;
    double gradeValue;
public:
    Grade();
    Grade(string id, string name, string sem, double grade);

    // Setters
    void setCourseID(string id);
    void setCourseName(string name);
    void setSemester(string sem);
    void setGradeValue(double grade);

    // Getters
    string getCourseID();
    string getCourseName();
    string getSemester();
    double getGradeValue();

};

