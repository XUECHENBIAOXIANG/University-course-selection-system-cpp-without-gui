
#ifndef SYSTEM_ENROLLMENTRECORD_H
#define SYSTEM_ENROLLMENTRECORD_H

#include <string>

class EnrollmentRecord {
public:
    std::string studentId;
    std::string courseId;
    std::string enrollmentTime;
    std::string status;
    std::string teacherId;

    EnrollmentRecord(std::string sId, std::string cId, std::string eTime, std::string stat, std::string tId);

    void displayInfo() const;
    void updateStatus(const std::string& newStatus);
    std::string serialize() const;
    static EnrollmentRecord deserialize(const std::string& data);
};

#endif //SYSTEM_ENROLLMENTRECORD_H
