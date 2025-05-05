#pragma once
#include "person.h"
#include<iostream>
#include<map>
#include "course.h"
using namespace std;

class Admin : public Person
{
private:
    
    map<int, int> Studs;
    map<string, course> allCourses; 

public:
    
    void setPreRequisites(map<string, course>& allCourses, string selectedCourseID, string preRequisiteCourseID);
    void uploadCourse(map<string, course>& allCourses, string courseID, string courseTitle, string syllabus, int creditHours, string instructorName);
};


