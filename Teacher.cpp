#include "Teacher.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Teacher::Teacher(std::string id, std::string n, std::string t, std::string dept, std::string pwd)
        : teacherId(id), name(n), title(t), department(dept), password(pwd) {}

void Teacher::addCourse(const std::string& courseId) {
    teachingCourses.push_back(courseId);
}

void Teacher::removeCourse(const std::string& courseId) {
    teachingCourses.erase(std::remove(teachingCourses.begin(), teachingCourses.end(), courseId), teachingCourses.end());
}

bool Teacher::verifyPassword(const std::string& pwd) const {
    return password == pwd;
}

void Teacher::displayInfo() const {
    std::cout << "Teacher ID: " << teacherId << "\n"
              << "Name: " << name << "\n"
              << "Title: " << title << "\n"
              << "Department: " << department << "\n"
              << "Teaching Courses: ";
    for (const auto& courseId : teachingCourses) {
        std::cout << courseId << " ";
    }
    std::cout << "\n";
}

std::string Teacher::serialize() const {
    std::ostringstream oss;
    oss << teacherId << "," << name << "," << title << "," << department << "," << password;
    for (const auto& courseId : teachingCourses) {
        oss << "," << courseId;
    }
    return oss.str();
}

Teacher Teacher::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string id, name, title, dept, pwd;
    std::getline(iss, id, ',');
    std::getline(iss, name, ',');
    std::getline(iss, title, ',');
    std::getline(iss, dept, ',');
    std::getline(iss, pwd, ',');
    Teacher teacher(id, name, title, dept, pwd);
    std::string courseId;
    while (std::getline(iss, courseId, ',')) {
        teacher.addCourse(courseId);
    }
    return teacher;
}
