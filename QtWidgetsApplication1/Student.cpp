#include "Student.h"
#include "course.h"
#include "Grade.h"
#include "vector"
#include<iostream>
using namespace std;




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

void Student::addCourseCompleted(string courseName)
{
	CompletedCourses.push_back(courseName);
}

vector<string> Student::getCoursesCompleted()
{
	return CompletedCourses;
}






bool Student::CourseIsAvaliable(string searchedCourse, unordered_map<string, course> AllCourses)
{

	auto it = AllCourses.find((searchedCourse));
	if (it == AllCourses.end()) {
		return false;
	}
	return true;

}

void Student::SearchForAvaibleCourses()
{

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
	for (it;it != grade.end();it++) {
		overallGpa += it->second.getGradeValue();
	}
	overallGpa /= grade.size();
	return overallGpa;
}




