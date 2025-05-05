#include "course.h"
#include<iostream>
#include <unordered_map>
using namespace std;
//course::course() {
//    courseTitle = "";
//    courseID = "";
//    syllabus = "";
//    creditHours = 0;
//    instructorName = "";
//    unordered_map<string, course> courseCatalog;
//
//}

course::course(string title, string id, string syllabus, int CH, string instructorName, course* pre)
{
    this->courseTitle = title;
    this->courseID = id;
    this->creditHours = CH;
    this->syllabus = syllabus;
    this->instructorName = instructorName;
    this->preRequisite = pre;


}

void course::setCourseTitle(const string& t) {
    courseTitle = t;
   
}

void course::setCourseID(const string& id) {
    courseID = id;
}

void course::setSyllabus(const string& s) {
    syllabus = s;
}

void course::setCreditHours(int ch) {
    creditHours = ch;
}

void course::setInstructorName(const string& name) {
    instructorName = name;
}



void course::setPreRequisite(course* preReq)
{
    preRequisite = preReq;
}

string course::getCourseTitle() const {
    return courseTitle;
}

string course::getCourseID() const {
    return courseID;
}

string course::getSyllabus() const {
    return syllabus;
}

int course::getCreditHours() const {
    return creditHours;
}

string course::getInstructorName() const {
    return instructorName;
}

course course::getPrerequisite() const
{
    course temp = (*this->preRequisite);
    return temp;
}






    


