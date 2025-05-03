#include "Admin.h"

void Admin::setPreRequisites(map<string, course>& allCourses, string selectedCourse, string preRequisite) {
    
    auto it = allCourses.find(selectedCourse);

    if (it != allCourses.end()) {
        it->second.setPrerequisiteCourseIDs(preRequisite);
    }
    else {
        
    }
}
