
#pragma once
#include "person.h"
#include<iostream>
#include<map>
#include "course.h"
#include "Student.h"
#include <vector>
#include <algorithm>
#include "FilesClass.h"
#include <string>
#include <unordered_map>
using namespace std;

class Admin : public Person
{
private:

    unordered_map<int, Student> Studs;
    unordered_map<string, course>* allCourses = &FilesClass::AllCourses;

public:
    Admin();
    Admin(int id, string name, string username, string password);
    void setPreRequisites(unordered_map<string, course>& allcourses, string selectedCourseID, string preRequisiteCourseID);
    void uploadCourse(unordered_map<string, course>& allCourses, string courseID, string courseTitle, string syllabus, int creditHours, string instructorName);
    void deleteCourse(unordered_map<string, course>& allCourses, string courseId);
    void uploadStudentGrades(int id, string courseId, int grade, string sem, unordered_map<int, Student>& Studs, unordered_map<string, course>& allCourses);
    void EditStudentGrades(int id, string courseId, int grade, string sem, unordered_map<int, Student>& Studs, unordered_map<string, course>& allCourses);
    void uploadStudentCompletedCourse(string id, string courseId, unordered_map<string, Student> Studs, unordered_map<string, course> allCourses);
    void displayStudentGrades(int id, unordered_map<int, Student>& Studs);
    void assignInstructorToCourse(string courseId, string instructorName, unordered_map<string, course>& allcourses);
    void removeStudentFromCourse(int studentId, string courseId, unordered_map<int, Student>& Studs);
    void setStudents( unordered_map<int, Student>& students);
    void setAllCourses( unordered_map<string, course>& courses);
    unordered_map<int, Student>& getStudents();
    unordered_map<string, course>& getAllCourses();


};

