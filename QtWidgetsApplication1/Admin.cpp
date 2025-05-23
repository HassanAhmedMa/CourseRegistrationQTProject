#include "Admin.h"


Admin::Admin()
{
}

Admin::Admin(int id, string name, string username, string password)
{
    this->setId(id);
    this->setName(name);
    this->setUsername(username);
    this->setPassword(password);
}

void Admin::setPreRequisites(unordered_map<string, course>& allcourses, string selectedCourseID, string preRequisiteCourseID) {

    auto it = FilesClass::AllCourses.find(selectedCourseID);

    if (it != FilesClass::AllCourses.end()) {
        auto preReqIt = FilesClass::AllCourses.find(preRequisiteCourseID);
        if (preReqIt != FilesClass::AllCourses.end()) {
            qDebug() << "ADDING COURSE PREREQUISUTE";
            /*it->second.setPreRequisite(FilesClass::AllCourses.find(preRequisiteCourseID)->second);*/
            FilesClass::AllCourses[selectedCourseID].setPreRequisite(&FilesClass::AllCourses[preRequisiteCourseID]);
            qDebug() << FilesClass::AllCourses[selectedCourseID].getPrerequisite()->getCourseID();

        }
        else {
            qDebug() << "Prerequisite course not found!";
        }
    }
    else {
        qDebug() << "Selected course not found!";
    }
}


void Admin::uploadCourse(unordered_map<string, course>& allCourses, string courseID, string courseTitle, string syllabus, int creditHours, string instructorName) {

    auto it = allCourses.find(courseID);

    if (it != allCourses.end()) {

        it->second.setCourseTitle(courseTitle);
        it->second.setSyllabus(syllabus);
        it->second.setCreditHours(creditHours);
        it->second.setInstructorName(instructorName);
        return;

    }
    else {
        // ta3deel baseet 3ashan law 7sal moshkela fel inputs
        if (courseID.empty() || courseTitle.empty() || instructorName.empty() || creditHours <= 0) {
            cout << "Error: Failed to upload course. Make sure all fields are filled and credit hours are positive.";
            return;
        }

        course newCourse(courseTitle, courseID, syllabus, creditHours, instructorName, nullptr);
        allCourses[courseID] = newCourse;
        return;


    }
}


void Admin::deleteCourse(unordered_map<string, course>& allCourses, string courseId) {

    auto it = allCourses.find(courseId);
    if (it == allCourses.end()) {
        cout << "Course not found. Course cannot be deleted. ";
        return;
    }

    allCourses.erase(it->first); // removes the whole pair, key and value from map
    cout << "Course has been deleted Successfully";
    return;
}


void Admin::uploadStudentGrades(int id, string courseId, int grade, string sem, unordered_map<int, Student>& Studs, unordered_map<string, course>& allCourses)
{
    auto it = Studs.find(id);
    if (it == Studs.end()) {
        cout << "Student Not Found";
        return;
    }

    Student& stud = it->second;
    vector <string> studentCourses = stud.getCourses();
    auto it2 = find(studentCourses.begin(), studentCourses.end(), courseId);

    if (it2 == studentCourses.end()) {
        cout << "Student does not have this course registered.";
        return;
    }

    auto it3 = allCourses.find(courseId);
    if (it3 == allCourses.end()) {
        cout << "Course not found.";
        return;
    }

    course& currentCourse = it3->second;

    stud.addGrade(courseId, currentCourse.getCourseTitle(), sem, grade);


    cout << "Grade uploaded successfully.";
}

void Admin::EditStudentGrades(int id, string courseId, int grade, string sem, unordered_map<int, Student>& Studs, unordered_map<string, course>& allCourses)
{
    auto it = Studs.find(id);
    if (it == Studs.end()) {
        cout << "Student Not Found.";
        return;
    }

    Student& stud = it->second;
    vector <string> studentCompletedCourses = stud.getCoursesCompleted();

    auto it2 = find(studentCompletedCourses.begin(), studentCompletedCourses.end(), courseId);
    if (it2 == studentCompletedCourses.end()) {
        cout << "Student does not have this course registered.";
        return;
    }

    auto it3 = allCourses.find(courseId);
    if (it3 == allCourses.end()) {
        cout << "course not found. ";
        return;
    }

    course& currentCourse = it3->second;

    stud.addGrade(courseId, currentCourse.getCourseTitle(), sem, grade);
    cout << "Grade uploaded successfully.";
}

void Admin::uploadStudentCompletedCourse(string id, string courseId, unordered_map<string, Student> Studs, unordered_map<string, course> allCourses)
{
    Student* studentToUpdate = nullptr;
    bool studentFound = false;
    for (auto x : Studs) {
        if (x.first == id) {
            studentToUpdate = &FilesClass::demoStudentsMap[id];
            studentFound = true;
            qDebug() << "Found Student !";
        }
    }
    if (!studentFound) {
        return;
    }
    bool courseFound = false;
    for (auto x : allCourses) {
        if (x.first == courseId) {
            courseFound = true;
            qDebug() << "Found Course !";
        }
    }
    if (!courseFound) {
        return;
    }
    if (FilesClass::toLower(studentToUpdate->getCoursesCompleted().at(0)) == "none") {
        qDebug() << studentToUpdate->getCoursesCompleted();
        studentToUpdate->getCoursesCompletedPtr().clear();
        qDebug() << studentToUpdate->getCoursesCompleted();
        qDebug() << studentToUpdate->getCoursesCompleted().size();

    }

    studentToUpdate->addCourseCompleted(courseId);
    vector<string> registeredCourses = studentToUpdate->getCourses();
    qDebug() << registeredCourses;
    auto it3 = find(registeredCourses.begin(), registeredCourses.end(), courseId);
    if (it3 != registeredCourses.end()) {
        registeredCourses.erase(it3);
        studentToUpdate->setCurrentCourses(registeredCourses);
        qDebug() << "Course Removed Succecsfully !";
    }
    if (studentToUpdate->getCourses().size() == 0) {
        studentToUpdate->addCourse("none");
    }
    qDebug() << studentToUpdate->getCoursesCompleted();




    //vector<string>* courses = studentToUpdate->getCoursesPtr();  // Get the vector by reference









   /* auto it = Studs.find(id);
    if (it == Studs.end()) {
        qDebug() << "Student Not Found.";
        return;
    }

    Student* stud = &it->second;
    auto it2 = allCourses.find(courseId);
    if (it2 == allCourses.end()) {
        qDebug() << "Course not found and therefore cannot be added.";
        return;
    }

    course* completedCourse = &it2->second;
    if () {
        stud->getCoursesCompleted().pop_back();
        stud->addCourseCompleted(completedCourse->getCourseID());
    }*/

    
}

//void Admin::uploadStudentCompletedCourse(int id, string courseId, unordered_map<int, Student>& Studs, unordered_map<string, course>& allCourses)
//{
//    auto it = Studs.find(id);
//    if (it == Studs.end()) {
//        cout << "Student Not Found.";
//        return;
//    }
//
//    Student& stud = it->second;
//    auto it2 = allCourses.find(courseId);
//    if (it2 == allCourses.end()) {
//        cout << "Course not found and therefore cannot be added.";
//        return;
//    }
//
//    string completedCourse = it2->first;
//    stud.addCourseCompleted(completedCourse);
//    cout << "Course has been added successfully to student's completed courses.";
//}


void Admin::displayStudentGrades(int id, unordered_map<int, Student>& Studs) {

    auto it = Studs.find(id);
    if (it == Studs.end()) {
        cout << "Student not found. Cannot display Student Grades.";
        return;
    }

    Student& stud = it->second;
    /*
    * NOTE: This variable is only by value and not by reference as it
    * will only be used to display the student grades or attributes
    */


    // logic to display indiviual completed courses gardes for specific student
    // momken ne7ot fo2eeha zay Student Current GPA bardo 

    vector<string> studCourses = stud.getCoursesCompleted();
    auto it2 = studCourses.begin();
    while (it2 != studCourses.end()) {
        string courseId = *it2;
        stud.getGrade(courseId);
        ++it2;

    }

    cout << "Student Grade displayed successfully." << endl;
}

void Admin::assignInstructorToCourse(string courseId, string instructorName, unordered_map<string, course>& allCourses)
{

    auto it = allCourses.find(courseId);
    if (it == allCourses.end()) {
        cout << "Course not found, cannot assign Instructor. ";
    }

    course& currentCourse = it->second;
    currentCourse.setInstructorName(instructorName);
}

void Admin::removeStudentFromCourse(int studentId, string courseId, unordered_map<int, Student>& Studs)
{
    auto it = Studs.find(studentId);
    if (it == Studs.end()) {
        cout << "Student Not Found.";
        return;
    }

    Student& stud = it->second;
    vector <string> registeredCourses = stud.getCourses();

    auto it2 = find(registeredCourses.begin(), registeredCourses.end(), courseId);
    if (it2 == registeredCourses.end()) {
        cout << "The student doesn't have the course registered.";
    }
    else {
        registeredCourses.erase(it2);
        stud.setCurrentCourses(registeredCourses);
        // changed in class student
    }

}

// SETTERS AND GETTERS
unordered_map<int, Student>& Admin::getStudents() {
    return Studs;
}

unordered_map<string, course>& Admin::getAllCourses() {
    return FilesClass::AllCourses;
}

void Admin::setStudents(unordered_map<int, Student>& students) {
    Studs = students;
}

void Admin::setAllCourses(unordered_map<string, course>& courses) {
    allCourses = &courses;
}
