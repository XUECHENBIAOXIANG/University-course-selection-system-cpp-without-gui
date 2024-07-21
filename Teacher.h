
#ifndef SYSTEM_TEACHER_H
#define SYSTEM_TEACHER_H

#include <string>
#include <vector>

class Teacher {
public:
    std::string teacherId;
    std::string name;
    std::string title;
    std::string department;
    std::string password;
    std::vector<std::string> teachingCourses;

    Teacher(std::string id, std::string n, std::string t, std::string dept, std::string pwd);

    void addCourse(const std::string& courseId);
    void removeCourse(const std::string& courseId);
    bool verifyPassword(const std::string& pwd) const;
    void displayInfo() const;
    std::string serialize() const;
    static Teacher deserialize(const std::string& data);
};




#endif //SYSTEM_TEACHER_H
