#include <iostream>
#include <fstream>
#include "course.h"
#include "person.h"
#include "Student.h"
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>  // Optional, for user-facing error display
#include <sstream>
class FilesClass {
public:
	vector<Student> AllStudents;


	void readStudentsData(string studentsFile = "Book1.csv") {
		ifstream file(studentsFile);
		string line;
		
		if (!file.is_open()) {
			qDebug() << "Error cannot open file : " + studentsFile << '\n';
		}
		else
		{
			qDebug() << "Read Successfully !";
		}
		int i = 0;
		while (getline(file, line)) {
			std::stringstream ss(line);
			if (i == 0) {
				i++;
				continue;
			}
			string username, password, id, name, registeredCoursesStr , CompletedCoursesStr;
			
			vector<string> tempRegisteredCourses;
			vector<string> tempCompletedCourses;
			Student student();

			getline(ss, name, ',');
			getline(ss, id, ',');
			getline(ss, username, ',');
			getline(ss, password, ',');
			getline(ss, registeredCoursesStr, ',');
			getline(ss, CompletedCoursesStr, ',');





		}

	}


};