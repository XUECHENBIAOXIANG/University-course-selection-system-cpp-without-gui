//
// Created by 陈表祥 on 2024/7/3.
//

#include "Student.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Student::Student(std::string id, std::string n, std::string m) : studentId(id), name(n), major(m) {}

void Student::enroll(const std::string& courseId) {
    enrolledCourses.push_back(courseId);
}

void Student::drop(const std::string& courseId) {
    enrolledCourses.erase(std::remove(enrolledCourses.begin(), enrolledCourses.end(), courseId), enrolledCourses.end());
}

void Student::displayInfo() const {
    std::cout << "Student ID: " << studentId << "\n"
              << "Name: " << name << "\n"
              << "Major: " << major << "\n"
              << "Enrolled Courses: ";
    for (const auto& courseId : enrolledCourses) {
        std::cout << courseId << " ";
    }
    std::cout << "\n";
}

std::string Student::serialize() const {
    std::ostringstream oss;
    oss << studentId << "," << name << "," << major;
    for (const auto& courseId : enrolledCourses) {
        oss << "," << courseId;
    }
    return oss.str();
}

Student Student::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string id, name, major;
    std::getline(iss, id, ',');
    std::getline(iss, name, ',');
    std::getline(iss, major, ',');
    Student student(id, name, major);
    std::string courseId;
    while (std::getline(iss, courseId, ',')) {
        student.enroll(courseId);
    }
    return student;
}
