#pragma once
#include <iostream>
#include <fstream>
#include "course.h"
#include "person.h"
#include "Student.h"
#include <string>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>  // Optional, for user-facing error display
#include <sstream>
#include <algorithm>
#include <cctype>
#include <unordered_map>


class FilesClass { //~Full class by Hassan Ahmed
public:
	//vector<Student> AllStudents;//----------> Saves all students Data in the system, Can be accessed by adminstrator and other classes to read data of students
	static unordered_map<string, Student> demoStudentsMap;
	static unordered_map<string, course> AllCourses;
	unordered_map<string, string> preReq;
	static Student* loggedInStudent;


	vector<string> parseCSVLine(string& line);
	void readStudentsData(string studentsFile = "Book1.csv");
	void readCoursesData(string location = "CoursesData.csv");
	static string toLower(string s);
	void writeStudentData();
	void writeCoursesData();

	


};