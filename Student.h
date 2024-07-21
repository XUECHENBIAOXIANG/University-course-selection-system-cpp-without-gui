
#ifndef SYSTEM_STUDENT_H
#define SYSTEM_STUDENT_H


#include <string>
#include <vector>

class Student {
public:
    std::string studentId;
    std::string name;
    std::string major;
    std::vector<std::string> enrolledCourses;

    Student(std::string id, std::string n, std::string m);

    void enroll(const std::string& courseId);
    void drop(const std::string& courseId);
    void displayInfo() const;
    std::string serialize() const;
    static Student deserialize(const std::string& data);
};


#endif //SYSTEM_STUDENT_H
