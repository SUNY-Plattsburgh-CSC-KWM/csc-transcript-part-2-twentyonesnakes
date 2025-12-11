#include "Student.h"
#include <fstream>
#include <sstream>

Student::Student() {}
Student::Student(const std::string& name, const std::string& id) : name(name), id(id) {}

const std::string& Student::getName() const { return name; }
const std::string& Student::getId() const { return id; }

void Student::addSemester(const Semester& semester) {
    semesters.push_back(semester);
}

const std::vector<Semester>& Student::getSemesters() const {
    return semesters;
}

double Student::computeCumulativeGPA() const {
    double totalPoints = 0.0;
    int totalCred = 0;
    for (const auto& s : semesters) {
        for (const auto& c : s.getCourses()) {
            totalPoints += c.getGrade() * c.getCredits();
            totalCred += c.getCredits();
        }
    }
    return (totalCred == 0) ? 0.0 : totalPoints / totalCred;
}

int Student::totalCredits() const {
    int t = 0;
    for (const auto& s : semesters) t += s.totalCredits();
    return t;
}

bool Student::saveCSV(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;

    for (const auto& s : semesters) {
        for (const auto& c : s.getCourses()) {
            out << name << "," << id << "," << s.getName() << ","
                << c.getNumber() << "," << c.getName() << ","
                << c.getCredits() << "," << c.getGrade() << "\n";
        }
    }
    return true;
}

bool Student::loadCSV(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;

    semesters.clear();
    std::string line;
    std::unordered_map<std::string, Semester> semMap;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string sName, sId, semName, num, cname, creditsStr, gradeStr;

        std::getline(ss, sName, ',');
        std::getline(ss, sId, ',');
        std::getline(ss, semName, ',');
        std::getline(ss, num, ',');
        std::getline(ss, cname, ',');
        std::getline(ss, creditsStr, ',');
        std::getline(ss, gradeStr, ',');

        name = sName;
        id = sId;
        Course c(num, cname, std::stoi(creditsStr), std::stod(gradeStr));

        semMap[semName].addCourse(c);
    }

    for (auto& p : semMap) semesters.push_back(p.second);
    return true;
}
