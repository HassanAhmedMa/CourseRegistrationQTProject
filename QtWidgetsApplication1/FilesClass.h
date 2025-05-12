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
class FilesClass { //~Full class by Hassan Ahmed
public:
	vector<Student> AllStudents;//----------> Saves all students Data in the system, Can be accessed by adminstrator and other classes to read data of students





	//-------------------------/CSV Parser/--------------------------------------------------------------------------------
	vector<string> parseCSVLine(const string& line) { //Function to return all parts of a csv File {Core function for file handling from csv Files) ~Hassan 
		vector<string> fields; //Fields to be returned as vector of strings
		string field; //temp  Field
		bool inQuotes = false; //initialized with false so when typing inQuotes = ~inQuotes it switches the statment without usage of checking

		for (size_t i = 0; i < line.size(); ++i) { //pass over each char in the row of columns ~ Hassan
			char c = line[i]; //read each char in the row

			if (c == '"') { //Check if going to enter a string between "" marks
				inQuotes = !inQuotes; // Toggle quote mode
			}
			else if (c == ',' && !inQuotes) {//if not in qoutations mode it will push each field separated by a ','
				fields.push_back(field);
				field.clear(); //resets the field to hold a new colum value in the next iteration
			}
			else {
				field += c; //pushes all chars if not a comma (behind commas) 
			}
		}

		fields.push_back(field); // Add the last field
		return fields;
	}




	//----------READ STUDENT DATA FUNCTION--------------------------------
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
			//Student student(fields.at(3), fields.at(4), fields.at(0), fields.at(1), )
			vector<string> fields = parseCSVLine(line);												//Temp data
			vector<string> registeredCourses;														//Temp data
			vector<string> CompletedCourses;														//Temp data
			string coursesBeforeCleanUp = fields.at(4);												//Temp data
			string CompletedCoursesBeforeCleanUp = fields.at(5);									//Temp data
			

			//Splitting Data in the multiAttribute Columns-------------\/\/\/
			if (!coursesBeforeCleanUp.empty() && coursesBeforeCleanUp.front() == '"' && coursesBeforeCleanUp.back() == '"') {
				coursesBeforeCleanUp = coursesBeforeCleanUp.substr(1, coursesBeforeCleanUp.length() - 2); // -2 because it we don't want the '"' from the whole string
			}
			if (toLower(coursesBeforeCleanUp) != "none") { //convert case insensitive data into lower case to compare and avoid any input errors from the csv file ~Hassan
				stringstream registeredCoursesStream(coursesBeforeCleanUp); // make file stream to split data between each , and save it as course
				string tempCourse;
				while (getline(registeredCoursesStream, tempCourse, ',')) {
					registeredCourses.push_back(tempCourse);
				}
			}
			else {
				registeredCourses.push_back("none");
			}


			//Same for CompletedCourses
			if (!CompletedCoursesBeforeCleanUp.empty() && CompletedCoursesBeforeCleanUp.front() == '"' && CompletedCoursesBeforeCleanUp.back() == '"') {
				CompletedCoursesBeforeCleanUp = CompletedCoursesBeforeCleanUp.substr(1, CompletedCoursesBeforeCleanUp.length() - 2); // -2 because it we don't want the "
			}
			if (toLower(CompletedCoursesBeforeCleanUp) != "none") {
				stringstream completedCoursesStream(CompletedCoursesBeforeCleanUp); 
				string tempCourse;
				while (getline(completedCoursesStream, tempCourse, ',')) {
					CompletedCourses.push_back(tempCourse);
				}
			}
			else {
				CompletedCourses.push_back("none");
			}

			Student stud(fields.at(2), fields.at(3), fields.at(0), stoi( fields.at(1)));
			stud.addCourse(registeredCourses);
			stud.addCourseCompleted(CompletedCourses);
			
			AllStudents.push_back(stud);

		
			//qDebug() << fields.at(2) + ' ' + fields.at(3) + ' ' + fields.at(0) + ' ' + fields.at(1) + ' ' + registeredCourses.at(0) + ' ' + CompletedCourses.at(0);
			



		}

	}




	static string toLower(string s) {
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		return s;

	}


};