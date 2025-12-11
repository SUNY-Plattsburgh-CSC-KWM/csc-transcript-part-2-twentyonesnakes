#ifndef SEMESTER_H
#define SEMESTER_H

#include <string>
#include <vector>
#include "Course.h"

class Semester {
public:
    Semester();
    Semester(const std::string& name);

    const std::string& getName() const;
    void addCourse(const Course& course);
    const std::vector<Course>& getCourses() const;

    double computeGPA() const;
    int totalCredits() const;

private:
    std::string name;
    std::vector<Course> courses;
};

#endif
