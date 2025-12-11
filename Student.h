#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Semester.h"

class Student {
public:
    Student();
    Student(const std::string& name, const std::string& id);

    const std::string& getName() const;
    const std::string& getId() const;

    void addSemester(const Semester& semester);
    const std::vector<Semester>& getSemesters() const;

    double computeCumulativeGPA() const;
    int totalCredits() const;

    // Save/load CSV
    bool saveCSV(const std::string& filename) const;
    bool loadCSV(const std::string& filename);

private:
    std::string name;
    std::string id;
    std::vector<Semester> semesters;
};

#endif
