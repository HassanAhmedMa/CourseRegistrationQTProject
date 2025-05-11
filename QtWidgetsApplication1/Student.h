#pragma once
#include "Person.h"
#include "vector"
#include <unordered_map>
#include "course.h"
#include "Grade.h"
class Student : public Person

{
private:
	//   ||--ATTRIBUTES--||
	vector<string> MyCourses; // still registerd courses
	vector<string> CompletedCourses;
	unordered_map<string, Grade> grade; // admin al mafrod hay4of al registered courses bta3ty w ydyha grades
	float overallGpa;

public:
	//   ||--FUNCTIONS--||
	Student();
	Student(string username, string password, string name, int id);

	void addCourse(string courseName); // setter for the list of courses of the student
	vector<string> getCourses();	// getter for the list of courses of the student

	void addCourseCompleted(string courseName); // setter for the list of completed courses of the student
	vector<string> getCoursesCompleted();	// getter for the list of completed courses of the student

	void addGrade(string courseID, string courseName, string semester, double gradeValue);

	void getGrade(string courseID);

	void setCurrentCourses(vector<string>& c);
	static bool CourseIsAvaliable(string searchedCourse, unordered_map<string, course> AllCourses);
	void SearchForAvaibleCourses(); //we need to use search tree
	void CourseRegisteration(string searchedCourse, unordered_map<string, course> AllCourses, vector<string> CompletedCourses); //will call SearchForAvaibleCourses() then will call  CheckPrerequisties()
	void ViewGrades(string courseID); //only for completed courses {the user should enter the name of the course }
	bool CheckPrerequisties(string searchedCourse, vector<string> CompletedCourses, unordered_map<string, course> AllCourses);// will take the name of the course and the list of completed courses and check if the prerequisite is completed or not
	float getOverallGPA();
	void MakeReport(); // generate priantable report
	//~Student();
};

