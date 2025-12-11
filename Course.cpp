#include "Course.h"

Course::Course() : credits(0), grade(0.0) {}

Course::Course(const std::string& number, const std::string& name, int credits, double grade)
    : number(number), name(name), credits(credits), grade(grade) {}

const std::string& Course::getNumber() const { return number; }
const std::string& Course::getName() const { return name; }
int Course::getCredits() const { return credits; }
double Course::getGrade() const { return grade; }

void Course::setNumber(const std::string& number) { this->number = number; }
void Course::setName(const std::string& name) { this->name = name; }
void Course::setCredits(int credits) { this->credits = credits; }
void Course::setGrade(double grade) { this->grade = grade; }
