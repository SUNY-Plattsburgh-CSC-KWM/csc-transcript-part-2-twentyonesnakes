// Jacob Gilbert

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Course
class Course {
private:
    string designation;
    string name;
    int credits;
    string grade;

public:
    Course(string des, string nm, int cr, string gr)
        : designation(des), name(nm), credits(cr), grade(gr) {}

    string getDesignation() const { return designation; }
    int getCredits() const { return credits; }
    string getGrade() const { return grade; }

    float getGradePoints() const {
        if (grade == "A") return 4.0;
        if (grade == "A-") return 3.7;
        if (grade == "B+") return 3.3;
        if (grade == "B") return 3.0;
        if (grade == "B-") return 2.7;
        if (grade == "C+") return 2.3;
        if (grade == "C") return 2.0;
        if (grade == "D") return 1.0;
        return 0.0;
    }
};


// Semester
class Semester {
private:
    int semesterCode;
    vector<Course> courses;

public:
    Semester(int code) : semesterCode(code) {}

    int getCode() const { return semesterCode; }

    void addCourse(const Course &c) {
        courses.push_back(c);
    }

    void removeCourse(const string &designation) {
        courses.erase(
            remove_if(courses.begin(), courses.end(),
                [&](const Course &c) { return c.getDesignation() == designation; }),
            courses.end()
        );
    }

    void sortCourses(const string &by) {
        if (by == "number") {
            sort(courses.begin(), courses.end(),
                 [](const Course &a, const Course &b) {
                     return a.getDesignation() < b.getDesignation();
                 });
        } else if (by == "grade") {
            sort(courses.begin(), courses.end(),
                 [](const Course &a, const Course &b) {
                     return a.getGradePoints() > b.getGradePoints();
                 });
        }
    }

    float calculateGPA() const {
        float totalPoints = 0;
        int totalCredits = 0;

        for (const auto &c : courses) {
            totalPoints += c.getGradePoints() * c.getCredits();
            totalCredits += c.getCredits();
        }
        return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0f;
    }

    int getTotalCredits() const {
        int sum = 0;
        for (const auto &c : courses)
            sum += c.getCredits();
        return sum;
    }

    const vector<Course>& getCourses() const {
        return courses;
    }
};

// Student
class Student {
private:
    string name;
    vector<Semester> semesters;

public:
    Student(string n) : name(n) {}

    void addSemester(int year, int termCode) {
        int code = year * 100 + termCode;
        semesters.emplace_back(code);
    }

    void removeSemester(int code) {
        semesters.erase(
            remove_if(semesters.begin(), semesters.end(),
                [&](const Semester &s) { return s.getCode() == code; }),
            semesters.end()
        );
    }

    Semester* getSemester(int code) {
        for (auto &s : semesters)
            if (s.getCode() == code)
                return &s;
        return nullptr;
    }

    float calculateCumulativeGPA() {
        float totalPoints = 0;
        int totalCredits = 0;

        unordered_map<string, Course> latestAttempt;

        for (const auto &sem : semesters) {
            for (const auto &c : sem.getCourses()) {
                latestAttempt[c.getDesignation()] = c;
            }
        }

        for (auto &[key, c] : latestAttempt) {
            totalPoints += c.getGradePoints() * c.getCredits();
            totalCredits += c.getCredits();
        }

        return (totalCredits > 0) ? totalPoints / totalCredits : 0.0f;
    }

// CSV Save 
    void saveToCSV(const string &filename) {
        ofstream file(filename);
        file << "Semester,Designation,Name,Credits,Grade\n";

        for (auto &sem : semesters) {
            for (auto &c : sem.getCourses()) {
                file << sem.getCode() << ","
                     << c.getDesignation() << ","
                     << c.getCredits() << ","
                     << c.getGrade() << "\n";
            }
        }
        file.close();
    }

// CSV Load
    void loadFromCSV(const string &filename) {
        ifstream file(filename);
        string line;

        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string semCodeStr, des, nm, credStr, grade;

            getline(ss, semCodeStr, ',');
            getline(ss, des, ',');
            getline(ss, nm, ',');
            getline(ss, credStr, ',');
            getline(ss, grade, ',');

            int code = stoi(semCodeStr);
            int credits = stoi(credStr);

            Semester *semester = getSemester(code);
            if (!semester) {
                semesters.emplace_back(code);
                semester = getSemester(code);
            }

            semester->addCourse(Course(des, nm, credits, grade));
        }
    }
};

// Example Usage
int main() {
    Student s("Jacob");

    s.addSemester(2024, 40);  // Fall 2024
    Semester* fall = s.getSemester(202440);

    fall->addCourse(Course("CSC 319", "Algorithms", 3, "A"));
    fall->addCourse(Course("MAT 250", "Calculus", 4, "B+"));

    cout << "Fall GPA: " << fall->calculateGPA() << endl;
    cout << "Cumulative GPA: " << s.calculateCumulativeGPA() << endl;

    return 0;
}