#include "course.h"
#include<iostream>
#include <unordered_map>
using namespace std;
course::course() {
    courseTitle = "";
    courseID = "";
    syllabus = "";
    creditHours = 0;
    instructorName = "";
    //unordered_map<string, course> courseCatalog;

}

course::course(string title, string id, string syllabus, int CH, string instructorName, course* pre)
{
    this->courseTitle = title;
    this->courseID = id;
    this->creditHours = CH;
    this->syllabus = syllabus;
    this->instructorName = instructorName;
    this->preRequisite = pre;


}

void course::setCourseTitle( string t) {
    courseTitle = t;

}

void course::setCourseID( string id) {
    courseID = id;
}

void course::setSyllabus( string s) {
    syllabus = s;
}

void course::setCreditHours(int ch) {
    creditHours = ch;
}

void course::setInstructorName( string name) {
    instructorName = name;
}



void course::setPreRequisite(course* preReq)
{
    preRequisite = preReq;
}

string course::getCourseTitle()  {
    return courseTitle;
}

string course::getCourseID()  {
    return courseID;
}

string course::getSyllabus()  {
    return syllabus;
}

int course::getCreditHours()  {
    return creditHours;
}

string course::getInstructorName()  {
    return instructorName;
}

course* course::getPrerequisite() const
{
    course* temp = this->preRequisite;
    return temp;
}

string course::getPreRequisuteID()
{

    return courseTitle;
}
