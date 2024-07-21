

#ifndef SYSTEM_COURSE_H
#define SYSTEM_COURSE_H
#include <string>
#include <vector>

class Course {
public:
    std::string courseId;
    std::string courseName;
    std::string description;
    int credits;
    std::string schedule;
    std::string location;
    std::vector<std::string> studentIds;

    Course(std::string id, std::string name, std::string desc, int cr, std::string sched, std::string loc);

    void addStudent(const std::string& studentId);
    void removeStudent(const std::string& studentId);
    void displayInfo() const;
    std::string serialize() const;
    static Course deserialize(const std::string& data);
};

#endif //SYSTEM_COURSE_H
