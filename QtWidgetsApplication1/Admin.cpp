#include "Admin.h"

void Admin::setPreRequisites(map<string, course>& allCourses, string selectedCourseID, string preRequisiteCourseID) {
    
    auto it = allCourses.find(selectedCourseID); 

    if (it != allCourses.end()) {
        auto preReqIt = allCourses.find(preRequisiteCourseID);  
        if (preReqIt != allCourses.end()) {
            it->second.setPreRequisite(&(preReqIt->second));  
        }
        else {
            cout << "Prerequisite course not found!" << endl;  
        }
    }
    else {
        cout << "Selected course not found!" << endl;  
    }
}
void Admin::uploadCourse(map<string, course>& allCourses, string courseID, string courseTitle, string syllabus, int creditHours, string instructorName) {
    
    auto it = allCourses.find(courseID);

    if (it != allCourses.end()) {
        
        it->second.setCourseTitle(courseTitle);
        it->second.setSyllabus(syllabus);
        it->second.setCreditHours(creditHours);
        it->second.setInstructorName(instructorName);

    }
    else {
        
        course newCourse(courseTitle, courseID, syllabus, creditHours, instructorName, nullptr);
        allCourses[courseID] = newCourse;

       
    }
}