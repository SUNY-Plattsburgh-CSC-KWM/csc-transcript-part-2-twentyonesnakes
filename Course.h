#ifndef COURSE_H
#define COURSE_H
#include <string>

class Course {
public:
    Course();
    Course(const std::string& number, const std::string& name, int credits, double grade);

    const std::string& getNumber() const;
    const std::string& getName() const;
    int getCredits() const;
    double getGrade() const;

    void setNumber(const std::string& number);
    void setName(const std::string& name);
    void setCredits(int credits);
    void setGrade(double grade);

private:
    std::string number;
    std::string name;
    int credits;
    double grade; // 0.0 - 4.0
};

#endif
