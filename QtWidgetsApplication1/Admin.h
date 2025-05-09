
#pragma once
#include "person.h"
#include<iostream>
#include<map>
#include "course.h"
#include "Student.h"
#include <vector>
#include <algorithm>
using namespace std;

class Admin : public Person
{
private:

    map<int, Student> Studs;
    map<string, course> allCourses;

public:
    Admin();
    Admin(int id, string name, string username, string password);
    void setPreRequisites(map<string, course>& allCourses, string selectedCourseID, string preRequisiteCourseID);
    void uploadCourse(map<string, course>& allCourses, string courseID, string courseTitle, string syllabus, int creditHours, string instructorName);
    void deleteCourse(map<string, course>& allCourses, string courseId);
    void uploadStudentGrades(int id, string courseId, int grade, string sem, map<int, Student>& Studs, map<string, course>& allCourses);
    void EditStudentGrades(int id, string courseId, int grade, string sem, map<int, Student>& Studs, map<string, course>& allCourses);
    void uploadStudentCompletedCourse(int id, string courseId, map<int, Student>& Studs, map<string, course>& allCourses);
    void displayStudentGrades(int id, map<int, Student>& Studs);
    void assignInstructorToCourse(string courseId, string instructorName, map<string, course>& allcourses);
    void removeStudentFromCourse(int studentId, string courseId, map<int, Student>& Studs);
    void setStudents(const map<int, Student>& students);
    void setAllCourses(const map<string, course>& courses);
    map<int, Student>& getStudents();
    map<string, course>& getAllCourses();


};

