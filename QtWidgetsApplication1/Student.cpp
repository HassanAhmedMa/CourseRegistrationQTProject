#include "Student.h"
#include "course.h"
#include "Grade.h"
#include "vector"
#include<iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip> 
using namespace std;



Student::Student() {
	setUsername("");
	setPassword("");
	setName("");
	setId(0);
}


Student::Student(string username, string password, string name, int id) {
	this->setUsername(username);
	this->setPassword(password);
	this->setName(name);
	this->setId(id);
}

void Student::addCourse(string courseName) {
	MyCourses.push_back(courseName);
}


vector<string> Student::getCourses() {
	return MyCourses;
}

vector<string>* Student::getCoursesPtr()
{
	return &MyCourses;
}

void Student::addCourse(vector<string> coursesToAdd)
{
	for (auto cur : coursesToAdd) {
		MyCourses.push_back(cur);
	}
}

void Student::addCourseCompleted(vector<string> coursesToAdd)
{
	for (auto cur : coursesToAdd) {
		CompletedCourses.push_back(cur);
	}
}

void Student::addCourseCompleted(string courseName)
{
	CompletedCourses.push_back(courseName);
}

vector<string> Student::getCoursesCompleted()
{
	return CompletedCourses;
}


void Student::setCurrentCourses(vector<string>& c)
{
	MyCourses = c;
}





void Student::addGrade(string courseID, string courseName, string semester, double gradeValue) {
	Grade g(courseID, courseName, semester, gradeValue);
	grade[courseID] = g;
}


void Student::getGrade(string courseID) {
	auto it = grade.find(courseID);
	if (it != grade.end()) {
		cout << "Course ID: " << it->second.getCourseID() << endl;
		cout << "Course Name: " << it->second.getCourseName() << endl;
		cout << "Semester: " << it->second.getSemester() << endl;
		cout << "Grade: " << it->second.getGradeValue() << endl;
	}
	else {
		cout << "Grade not found for course ID: " << courseID << endl;
	}
}
string Student::GetGradeAsString(string courseID) {
	
	
	auto it = grade.find(courseID);
	if (it != grade.end()) {
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(1) << it->second.getGradeValue(); //remove extra 
		return stream.str();
	}
	else {
		return "-1";
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// HELPERS FOR ADMIN
bool Student::getGradeValue(string& courseID, float& gradeOut)
{
	auto it = grade.find(courseID);
	if (it != grade.end()) {
		gradeOut = it->second.getGradeValue();
		return true;
	}
	return false;
}

bool Student::getGradeDetails(string& courseID, string& titleOut, string& semesterOut, float& gradeOut)
{
	auto it = grade.find(courseID);
	if (it != grade.end()) {
		titleOut = it->second.getCourseName();
		semesterOut = it->second.getSemester();
		gradeOut = it->second.getGradeValue();
		return true;
	}
	return false;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// FUNCTIONS FOR STUDENT REGISTERATION
bool Student::CourseIsAvaliable(string searchedCourse, unordered_map<string, course> AllCourses)
{

	auto it = AllCourses.find((searchedCourse));
	if (it == AllCourses.end()) {
		return false;
	}
	return true;

}


bool Student::CheckPrerequisties(string searchedCourse, vector<string> CompletedCourses, unordered_map<string, course> AllCourses)
{//searchCourse da al mafrod course 3ndy fl files fa ana lazm ashof course.prereq bta3to w abtdy akrnha bl completedcourses bta3ty

	auto it = AllCourses.find(searchedCourse);
	if (it != AllCourses.end()) {
		course* prereq = it->second.getPrerequisite(); // Get pointer to prerequisite course

		if (prereq == nullptr) {
			// No prerequisite ll course da
			return true;
		}

		string prereqCourseID = prereq->getCourseID(); // da 3la asas en course id hwa esm al course


		for (int i = 0; i < CompletedCourses.size(); i++) {
			if (CompletedCourses[i] == prereqCourseID) {
				return true;
			}
		}

		cout << "Prerequisite " << prereqCourseID << " is not completed yet.\n";
		return false;
	}
	else {
		cout << "Course not found in the catalog.\n";
		return false;
	}
}


void Student::CourseRegisteration(string searchedCourse, unordered_map<string, course> AllCourses, vector<string> CompletedCourses)
{
	if (CourseIsAvaliable(searchedCourse, AllCourses)) {
		if (CheckPrerequisties(searchedCourse, CompletedCourses, AllCourses)) {
			addCourse(searchedCourse);
			cout << "Course registered successfully!\n";
		}
		else {
			cout << "You cannot register. Prerequisite not completed.\n";
		}
	}
	else {
		cout << "Course is not available at the university.\n";
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Student::ViewGrades(string courseID)
{
	auto it = find(CompletedCourses.begin(), CompletedCourses.end(), courseID);
	if (it != CompletedCourses.end()) {
		if (grade.find(courseID) != grade.end())
			cout << "Course ID: " << courseID << endl;
		cout << "Course Name: " << grade[courseID].getCourseName() << endl;
		cout << "Semester: " << grade[courseID].getSemester() << endl;
		cout << "Grade: " << grade[courseID].getGradeValue() << endl;
		return;
	}



	else {
		cout << "Course not found in the completed courses.\n";

	}

}


void Student::MakeReport()
{
	cout << "\n\n\n||------------------Student Report------------------||\n";
	cout << "Student Name: " << this->getName() << endl;
	cout << "Student ID: " << this->getId() << endl;
	cout << "completed courses: " << endl;
	for (string courseID : CompletedCourses) {
		ViewGrades(courseID);
	}
	cout << "Overall GPA: " << getOverallGPA() << endl;

}

float Student::getOverallGPA()
{
	overallGpa = 0;

	auto it = grade.begin();
	for (it; it != grade.end(); it++) {
		overallGpa += it->second.getGradeValue();
	}
	overallGpa /= grade.size();
	return overallGpa;
}
Grade* Student::getGradeObject(string courseID) {
	auto it = grade.find(courseID);
	if (it != grade.end())
		return &it->second;
	return nullptr; 
}




queue<string> Student::history; //helper for accessing the static queue 

