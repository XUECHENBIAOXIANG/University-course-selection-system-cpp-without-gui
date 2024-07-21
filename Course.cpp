

#include "Course.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Course::Course(std::string id, std::string name, std::string desc, int cr, std::string sched, std::string loc)
        : courseId(id), courseName(name), description(desc), credits(cr), schedule(sched), location(loc) {}

void Course::addStudent(const std::string& studentId) {
    studentIds.push_back(studentId);
}

void Course::removeStudent(const std::string& studentId) {
    studentIds.erase(std::remove(studentIds.begin(), studentIds.end(), studentId), studentIds.end());
}

void Course::displayInfo() const {
    std::cout << "Course ID: " << courseId << "\n"
              << "Course Name: " << courseName << "\n"
              << "Description: " << description << "\n"
              << "Credits: " << credits << "\n"
              << "Schedule: " << schedule << "\n"
              << "Location: " << location << "\n";
}

std::string Course::serialize() const {
    std::ostringstream oss;
    oss << courseId << "," << courseName << "," << description << "," << credits << "," << schedule << "," << location;
    return oss.str();
}

Course Course::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string id, name, desc, sched, loc;
    int cr;
    std::getline(iss, id, ',');
    std::getline(iss, name, ',');
    std::getline(iss, desc, ',');
    iss >> cr;
    iss.ignore(1, ',');
    std::getline(iss, sched, ',');
    std::getline(iss, loc, ',');
    return Course(id, name, desc, cr, sched, loc);
}
