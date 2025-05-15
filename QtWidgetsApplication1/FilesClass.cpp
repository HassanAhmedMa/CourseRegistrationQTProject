#include "FilesClass.h"

unordered_map<string, Student> FilesClass::demoStudentsMap;
unordered_map<string, course> FilesClass::AllCourses;
Student* FilesClass::loggedInStudent;

//-------------------------/CSV Parser/--------------------------------------------------------------------------------


vector<string> FilesClass::parseCSVLine(string& line) { //Function to return all parts of a csv File {Core function for file handling from csv Files) ~Hassan 
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
void FilesClass::readStudentsData(string studentsFile) {
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
		string gradesBeforeCleanUp = fields.at(6);
		vector<float> grades;

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
		//qDebug() << fields.at(6);



		if (!gradesBeforeCleanUp.empty() && gradesBeforeCleanUp.front() == '"' && gradesBeforeCleanUp.back() == '"') {
			gradesBeforeCleanUp = gradesBeforeCleanUp.substr(1, gradesBeforeCleanUp.length() - 2); // -2 because it we don't want the "
		}
		if (toLower(gradesBeforeCleanUp) != "none") {
			stringstream gradesStream(gradesBeforeCleanUp);
			string tempCourse;
			while (getline(gradesStream, tempCourse, ',')) {
				grades.push_back(stof(tempCourse));
			}
		}
		else {
			grades.push_back(-1.0); //To check if the student has no grades at all
		}


		




		Student stud(fields.at(2), fields.at(3), fields.at(0), stoi(fields.at(1)));
		stud.addCourse(registeredCourses);
		stud.addCourseCompleted(CompletedCourses);
		

		if (CompletedCourses.size() == grades.size() && grades.at(0) != -1) { //if the student has grades and at the same time the number of grades = the number of completed courses
			int k = 0;
			for (auto grade : grades) {
				stud.addGrade(CompletedCourses.at(k), AllCourses[CompletedCourses.at(k)].getCourseTitle(), "fall", grade);
				k++;
				
				

			}
		}
		else
		{
			qDebug() << "CRITICAL ERROR 1 OCCURED IN FILES"; //Number of completed courses != number of grades {Problem in files .csv}
		}
		

		
		demoStudentsMap[fields.at(2)] = stud;

		//qDebug() << fields.at(2) + ' ' + fields.at(3) + ' ' + fields.at(0) + ' ' + fields.at(1) + ' ' + registeredCourses.at(0) + ' ' + CompletedCourses.at(0);




	}

}

void FilesClass::readCoursesData(string location) {
	ifstream file(location);
	string line;

	if (!file.is_open()) {
		qDebug() << "Error cannot open file : " + location << '\n';
	}
	else
	{
		qDebug() << "Read " + location + " Successfully !";
	}
	int i = 0; //used to skip the headers

	while (getline(file, line)) {
		if (i == 0) {
			i++;
			continue;
		}
		vector<string> fields = parseCSVLine(line);
		
		
		preReq[fields.at(0)] = fields.at(4);
		course tempCourse = course(fields.at(1), fields.at(0), fields.at(5), stoi(fields.at(2)), fields.at(3));
		AllCourses[fields.at(0)] = tempCourse;
		qDebug() << preReq.size();




	}

	for (auto cur : preReq) {
		if (cur.second == "None") {
			continue;
		}
		else {
			AllCourses[cur.first].setPreRequisite(&AllCourses[cur.second]);
		}
	}
}





string FilesClass::toLower(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;

}












