#include <iostream>
#include "Student.h"
#include "Semester.h"
#include "Course.h"

int main() {
    Student s("Test Student", "12345");

    Semester fall("Fall 2024");
    fall.addCourse(Course("CSC101", "Intro to CS", 3, 4.0));
    fall.addCourse(Course("MAT202", "Calculus I", 4, 3.7));

    Semester spring("Spring 2025");
    spring.addCourse(Course("ENG101", "English Comp", 3, 3.0));
    spring.addCourse(Course("CSC223", "Data Structures", 4, 3.3));

    s.addSemester(fall);
    s.addSemester(spring);

    std::cout << "Cumulative GPA: " << s.computeCumulativeGPA() << std::endl;
    std::cout << "Total Credits: " << s.totalCredits() << std::endl;

    std::string filename = "transcript.csv";
    if (s.saveCSV(filename)) {
        std::cout << "Saved to " << filename << std::endl;
    }

    Student loaded;
    if (loaded.loadCSV(filename)) {
        std::cout << "Loaded student: " << loaded.getName() << " (" << loaded.getId() << ")\n";
        std::cout << "Loaded cumulative GPA: " << loaded.computeCumulativeGPA() << std::endl;
    }

    return 0;
}
