#include "Semester.h"

Semester::Semester() {}
Semester::Semester(const std::string& name) : name(name) {}

const std::string& Semester::getName() const { return name; }

void Semester::addCourse(const Course& course) {
    courses.push_back(course);
}

const std::vector<Course>& Semester::getCourses() const {
    return courses;
}

double Semester::computeGPA() const {
    double totalPoints = 0.0;
    int totalCred = 0;
    for (const auto& c : courses) {
        totalPoints += c.getGrade() * c.getCredits();
        totalCred += c.getCredits();
    }
    return (totalCred == 0) ? 0.0 : totalPoints / totalCred;
}

int Semester::totalCredits() const {
    int t = 0;
    for (const auto& c : courses) t += c.getCredits();
    return t;
}
