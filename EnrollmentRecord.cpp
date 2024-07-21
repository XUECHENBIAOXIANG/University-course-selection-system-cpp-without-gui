

#include "EnrollmentRecord.h"
#include <iostream>
#include <sstream>

EnrollmentRecord::EnrollmentRecord(std::string sId, std::string cId, std::string eTime, std::string stat, std::string tId)
        : studentId(sId), courseId(cId), enrollmentTime(eTime), status(stat), teacherId(tId) {}

void EnrollmentRecord::displayInfo() const {
    std::cout << "Student ID: " << studentId << "\n"
              << "Course ID: " << courseId << "\n"
              << "Enrollment Time: " << enrollmentTime << "\n"
              << "Status: " << status << "\n"
              << "Teacher ID: " << teacherId << "\n";
}

void EnrollmentRecord::updateStatus(const std::string& newStatus) {
    status = newStatus;
}

std::string EnrollmentRecord::serialize() const {
    std::ostringstream oss;
    oss << studentId << "," << courseId << "," << enrollmentTime << "," << status << "," << teacherId;
    return oss.str();
}

EnrollmentRecord EnrollmentRecord::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string sId, cId, eTime, stat, tId;
    std::getline(iss, sId, ',');
    std::getline(iss, cId, ',');
    std::getline(iss, eTime, ',');
    std::getline(iss, stat, ',');
    std::getline(iss, tId, ',');
    return EnrollmentRecord(sId, cId, eTime, stat, tId);
}
