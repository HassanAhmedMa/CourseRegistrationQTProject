#pragma once

#ifndef COURSE_H
#define COURSE_H
using namespace std;
#include <string>
#include <vector>

class course{
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
    void setCourseTitle(const string& t);
    void setCourseID(const string& id);
    void setSyllabus(const string& s);
    void setCreditHours(int ch);
    void setInstructorName(const string& name);
    
    void setPreRequisite(course* preReq);
    string getCourseTitle() const;
    string getCourseID() const;
    string getSyllabus() const;
    int getCreditHours() const;
    string getInstructorName() const;
    course getPrerequisite() const;
};

#endif


