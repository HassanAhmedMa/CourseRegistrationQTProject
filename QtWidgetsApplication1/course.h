#pragma once

#ifndef COURSE_H
#define COURSE_H
using namespace std;
#include <string>
#include <vector>

class course {
private:
    string courseTitle;
    string courseID;
    string syllabus;
    int creditHours;
    string instructorName;
    course* preRequisite;

public:
    course();
    course(string title, string id, string syllabus, int CH, string instructorName, course* pre = nullptr);
    void setCourseTitle( string t);
    void setCourseID( string id);
    void setSyllabus( string s);
    void setCreditHours(int ch);
    void setInstructorName( string name);

    void setPreRequisite(course* preReq);
    string getCourseTitle();
    string getCourseID();
    string getSyllabus();
    int getCreditHours();
    string getInstructorName();
    course* getPrerequisite() const ;
    string getPreRequisuteID();
};

#endif