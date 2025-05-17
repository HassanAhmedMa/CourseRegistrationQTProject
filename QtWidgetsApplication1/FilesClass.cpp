#include "FilesClass.h"

unordered_map<string, Student> FilesClass::demoStudentsMap;
unordered_map<string, course> FilesClass::AllCourses;
Student* FilesClass::loggedInStudent;
//Admin* FilesClass::currentAdmin;

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
		//qDebug() << "Error cannot open file : " + studentsFile << '\n';
	}
	else
	{
		//qDebug() << "Read Successfully !";
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
		vector<float> registeredGrades;
		string registeredGradesBeforeCleanUp = fields.at(7);

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
		////qDebug() << fields.at(6);



		if (!gradesBeforeCleanUp.empty() && gradesBeforeCleanUp.front() == '"' && gradesBeforeCleanUp.back() == '"') {
			gradesBeforeCleanUp = gradesBeforeCleanUp.substr(1, gradesBeforeCleanUp.length() - 2); // -2 because it we don't want the "
		}
		if (toLower(gradesBeforeCleanUp) != "none") {
			stringstream gradesStream(gradesBeforeCleanUp);
			string completedGrades;
			while (getline(gradesStream, completedGrades, ',')) {
				grades.push_back(stof(completedGrades));
			}
		}
		else {
			grades.push_back(-1.0); //To check if the student has no grades at all
		}

		if (!registeredGradesBeforeCleanUp.empty() && registeredGradesBeforeCleanUp.front() == '"' && registeredGradesBeforeCleanUp.back() == '"') {
			registeredGradesBeforeCleanUp = registeredGradesBeforeCleanUp.substr(1, registeredGradesBeforeCleanUp.length() - 2); // -2 because it we don't want the "
		}
		if (toLower(registeredGradesBeforeCleanUp) != "none") {
			stringstream registeredGradesStream(registeredGradesBeforeCleanUp);
			string registeredGrades;
			while (getline(registeredGradesStream, registeredGrades, ',')) {
				grades.push_back(stof(registeredGrades));
			}
		}
		else {
			grades.push_back(-1.0); //To check if the student has no grades at all
		}
		qDebug() << grades;




		Student stud(fields.at(2), fields.at(3), fields.at(0), stoi(fields.at(1)));
		stud.addCourse(registeredCourses);
		stud.addCourseCompleted(CompletedCourses);
		

		if (CompletedCourses.size() + registeredCourses.size() == grades.size()) { //if the student has grades and at the same time the number of grades = the number of completed courses
			int k = 0;
			/*for (auto grade : grades) {
				stud.addGrade(CompletedCourses.at(k), AllCourses[CompletedCourses.at(k)].getCourseTitle(), "fall", grade);
				k++;
			}*/
			for (auto x : CompletedCourses) {
				if (grades.at(k) != 5) {
					stud.addGrade(x, AllCourses[x].getCourseTitle(), "fall", grades.at(k));
					k++;
				}
				else {
					k++;
					continue;
				}
				
			}
			for (auto x : registeredCourses) {
				if (grades.at(k) != 5 ) {
					stud.addGrade(x, AllCourses[x].getCourseTitle(), "fall", grades.at(k));
					k++;
				}
				else
				{
					k++;
					continue;
				}
				
			}
		}
		else
		{
			qDebug() << "CRITICAL ERROR 1 OCCURED IN FILES"; //Number of completed courses != number of grades {Problem in files .csv}
		}
		
		//qDebug() << stud.getCoursesCompleted() << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

		/*for (auto x : stud.getCourses()) {
			//qDebug() << x;
		}*/

		
		demoStudentsMap[fields.at(1)] = stud;

		////qDebug() << fields.at(2) + ' ' + fields.at(3) + ' ' + fields.at(0) + ' ' + fields.at(1) + ' ' + registeredCourses.at(0) + ' ' + CompletedCourses.at(0);




	}

}

void FilesClass::readCoursesData(string location) {
	ifstream file(location);
	string line;

	if (!file.is_open()) {
		//qDebug() << "Error cannot open file : " + location << '\n';
	}
	else
	{
		//qDebug() << "Read " + location + " Successfully !";
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
		//qDebug() << preReq.size();




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

void FilesClass::writeStudentData()
{
	ofstream file("Book1.csv");
	if (!file.is_open()) {
		qDebug() << "Couldn't open " << "Book1.csv";
		return;
	}
	file << "Name,Seat Number ID,Username,Password,Registered Courses,Completed Courses,Completed grades,RegisteredGrades\n";

	for (auto x : demoStudentsMap) {
		qDebug() << x.second.getCourses();
		qDebug() << x.second.getCoursesCompleted();
		qDebug() << x.second.getName();


		string registeredCoursesStr = "none";
		string completedCoursesStr = "none";
		string usernameStr = x.second.getUsername();
		string passwordStr = x.second.getPassword();
		string idStr = to_string( x.second.getId());
		string nameStr =  x.second.getName();
		string completedCoursesGradesStr = "5";
		string RegisteredCoursesGradesStr = "5";

		//Reverse the parsing from the data in the static files
		if (toLower(x.second.getCourses().at(0)) != "none") { //"none" is the identifier if there is no course registered
			registeredCoursesStr = ""; //initialize the courseString with an empty string since it won't be none
			if (x.second.getCourses().size() > 1) { //if there is more than one course it will start adding " to the first of the string to parse into the csv file
				registeredCoursesStr = "\"";
				for (auto registeredCourse : x.second.getCourses()) {
					registeredCoursesStr.append(registeredCourse + ",");//add a comma after each addition of a course ID for the registered courses

				}
				registeredCoursesStr.pop_back(); //remove the last char which is ',' as a redundant char from the last for loop
				registeredCoursesStr.append("\"");
			}
			else {
				registeredCoursesStr = x.second.getCourses().at(0); //if there is only one field in the course (one registered course only) it will take it without the ""
			}
		}

		if (toLower(x.second.getCoursesCompleted().at(0)) != "none") {
			completedCoursesStr = "";
			if (x.second.getCoursesCompleted().size() > 1) {
				completedCoursesStr = "\"";
				for (auto completedCourse : x.second.getCoursesCompleted()) {
					completedCoursesStr.append(completedCourse + ",");

				}
				completedCoursesStr.pop_back();
				completedCoursesStr.append("\"");
			}
			else {
				completedCoursesStr = x.second.getCoursesCompleted().at(0);
			}
		}
		
		if (toLower(x.second.getCoursesCompleted().at(0))  != "none") {
			completedCoursesGradesStr = "";
			if (x.second.getCoursesCompleted().size() > 1) {
				completedCoursesGradesStr = "\"";
				for (auto completedCourseGrade : x.second.getCoursesCompleted()) {
					completedCoursesGradesStr.append(x.second.GetGradeAsString(completedCourseGrade) + ",");

				}
				completedCoursesGradesStr.pop_back();
				completedCoursesGradesStr.append("\"");
			}
			else {
				completedCoursesGradesStr = x.second.GetGradeAsString(x.second.getCoursesCompleted().at(0));
			}
		}
		if (toLower(x.second.getCourses().at(0)) != "none") {
			RegisteredCoursesGradesStr = "";
			if (x.second.getCourses().size() > 1) {
				RegisteredCoursesGradesStr = "\"";
				for (auto registeredCourse : x.second.getCourses()) {
					RegisteredCoursesGradesStr.append(x.second.GetGradeAsString(registeredCourse) + ",");

				}
				RegisteredCoursesGradesStr.pop_back();
				RegisteredCoursesGradesStr.append("\"");
			}
			else {
				RegisteredCoursesGradesStr = x.second.GetGradeAsString(x.second.getCourses().at(0));
			}
		}

		



		qDebug() << registeredCoursesStr;
		qDebug() << completedCoursesStr;
		qDebug() << nameStr;
		qDebug() << passwordStr;
		qDebug() << usernameStr;
		qDebug() << idStr;
		qDebug() << completedCoursesGradesStr;
		file << nameStr << ','
			<< idStr << ','
			<< usernameStr << ','
			<< passwordStr << ','
			<< registeredCoursesStr << ','
			<< completedCoursesStr << ','
			<< completedCoursesGradesStr << ','
			<< RegisteredCoursesGradesStr << "\n";



		//ofstream file2("testingwriteData.csv");
		//if (!file2.is_open()) {
		//	qDebug() << "Couldn't open " << "testingwriteData.csv";
		//	return;
		//}
		//file2 << "CourseID,CourseName,CreditHours,Instructor,Prerequisite,Syllabus\n";
		//for (auto x : AllCourses) {
		//	string CourseID = x.second.getCourseID();
		//	string CourseName = x.second.getCourseTitle();
		//	string CreditHours = to_string(x.second.getCreditHours());
		//	string Instructor = x.second.getInstructorName();
		//	string PrerequisiteCourse = x.second.getPrerequisite()->getCourseID();
		//	string Syllabus = x.second.getSyllabus();
		//
		//	
		//	
		//	
		//	
		//	
		//	











		


	}
	
}

void FilesClass::writeCoursesData()
{
	
	ofstream file("CoursesData.csv");
	if (!file.is_open()) {
		qDebug() << "Couldn't open " << "CoursesData.csv";
		return;
	}
	file << "CourseID,CourseName,CreditHours,Instructor,Prerequisite,Syllabus\n";
	
	for (auto x : AllCourses) {
		string CourseID = x.second.getCourseID();
		string CourseName = x.second.getCourseTitle();
		string CreditHours = to_string(x.second.getCreditHours());
		string Instructor = x.second.getInstructorName();
		string PrerequisiteCourse;
		if (x.second.getPrerequisite() != nullptr) {
			PrerequisiteCourse = x.second.getPrerequisite()->getCourseID();
		}
		else
		{
			PrerequisiteCourse = "None";
		}

		string Syllabus = x.second.getSyllabus();



		file << CourseID << ','
			<< CourseName << ','
			<< CreditHours << ','
			<< Instructor << ','
			<< PrerequisiteCourse << ','
			<< Syllabus << "\n";
	}
	

}
















