#pragma once
#include "person.h"
#include<iostream>
#include<map>
#include "course.h"
using namespace std;

class Admin : public Person
{
private:
    // second is student obj
    map<int, int> Studs;
    map<string, course> allCourses; // first is courseID (string), second is course obj

public:
    // Function to set prerequisites for a course
    void setPreRequisites(map<string, course>& allCourses, string selectedCourse, string preRequisite);
};


