#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Course.h"
#include "EnrollmentRecord.h"

std::unordered_map<std::string, Student> students;
std::unordered_map<std::string, Teacher> teachers;
std::unordered_map<std::string, Admin> admins;
std::unordered_map<std::string, Course> courses;
std::vector<EnrollmentRecord> enrollmentRecords;

void loadStudents(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        Student student = Student::deserialize(line);
        students.insert({student.studentId, student});
    }
}

void loadTeachers(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        Teacher teacher = Teacher::deserialize(line);
        teachers.insert({teacher.teacherId, teacher});
    }
}

void loadAdmins(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        Admin admin = Admin::deserialize(line);
        admins.insert({admin.adminId, admin});
    }
}

void loadCourses(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        Course course = Course::deserialize(line);
        courses.insert({course.courseId, course});
    }
}

void loadEnrollmentRecords(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        EnrollmentRecord record = EnrollmentRecord::deserialize(line);
        enrollmentRecords.push_back(record);
    }
}

void saveStudents(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : students) {
        file << pair.second.serialize() << "\n";
    }
}

void saveTeachers(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : teachers) {
        file << pair.second.serialize() << "\n";
    }
}

void saveAdmins(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : admins) {
        file << pair.second.serialize() << "\n";
    }
}

void saveCourses(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : courses) {
        file << pair.second.serialize() << "\n";
    }
}

void saveEnrollmentRecords(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& record : enrollmentRecords) {
        file << record.serialize() << "\n";
    }
}

bool studentLogin(const std::string& id) {
    return students.find(id) != students.end();
}

bool teacherLogin(const std::string& id, const std::string& password) {
    auto it = teachers.find(id);
    return it != teachers.end() && it->second.verifyPassword(password);
}

bool adminLogin(const std::string& id, const std::string& password) {
    auto it = admins.find(id);
    return it != admins.end() && it->second.verifyPassword(password);
}

int main() {
    loadStudents("D:\\system\\students.txt");
    loadTeachers("D:\\system\\teachers.txt");
    loadAdmins("admins.txt");
    loadCourses("D:\\system\\courses.txt");
    loadEnrollmentRecords("D:\\system\\enrollment_records.txt");
    //打印admins
//    for (const auto& pair : admins) {
//        pair.second.displayInfo();
//    }
//    for (const auto& pair : students) {
//        pair.second.displayInfo();
//    }
//    for (const auto& pair : teachers) {
//        pair.second.displayInfo();
//    }
//    for (const auto& pair : courses) {
//        pair.second.displayInfo();
//
//    }
//    for (const auto& record : enrollmentRecords) {
//        record.displayInfo();
//    }

    std::string userType;
    std::cout << "Select user type (student/teacher/admin): ";
    std::cin >> userType;

    if (userType == "student") {
        std::string studentId;
        std::cout << "Enter student ID: ";
        std::cin >> studentId;
        if (studentLogin(studentId)) {
            std::cout << "Login successful!\n";
            int choice;
            do {
                std::cout << "1. View Personal Info\n2. Enroll in Course\n3. Drop Course\n4. View Courses\n5. View Enrolled Courses\n6. Exit\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;
                if (choice == 1) {
                    auto it = students.find(studentId);
                    it->second.displayInfo();
                } else if (choice == 2) {
                    std::string courseId;
                    std::cout << "Enter course ID to enroll: ";
                    std::cin >> courseId;
                    if (courses.find(courseId) != courses.end()) {
                        auto it = students.find(studentId);
                        it->second.enroll(courseId);
                        auto it2 = courses.find(courseId);
                        it2->second.addStudent(studentId);

                        enrollmentRecords.push_back(EnrollmentRecord(studentId, courseId, "now", "enrolled", "teacherId")); // You may want to update this
                        std::cout << "Enrolled successfully!\n";
                    } else {
                        std::cout << "Course not found!\n";
                    }
                } else if (choice == 3) {
                    std::string courseId;
                    std::cout << "Enter course ID to drop: ";
                    std::cin >> courseId;
                    auto it = students.find(studentId);
                    it->second.drop(courseId);
                    auto it2 = courses.find(courseId);
                    it2->second.removeStudent(studentId);
                    std::cout << "Dropped successfully!\n";
                } else if (choice == 4) {
                    for (const auto& pair : courses) {
                        pair.second.displayInfo();
                    }
                } else if (choice == 5) {
                    auto it = students.find(studentId);
                    it->second.displayInfo();
                }
            } while (choice != 6);
        } else {
            std::cout << "Login failed!\n";
        }
    } else if (userType == "teacher") {
        std::string teacherId, password;
        std::cout << "Enter teacher ID: ";
        std::cin >> teacherId;
        std::cout << "Enter password: ";
        std::cin >> password;
        if (teacherLogin(teacherId, password)) {
            std::cout << "Login successful!\n";
            int choice;
            do {
                std::cout << "1. View Personal Info\n2. Add Course\n3. Remove Course\n4. View Courses\n5. View Student Enrollments\n6. Exit\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;
                if (choice == 1) {
                    auto it = teachers.find(teacherId);
                    it->second.displayInfo();
                } else if (choice == 2) {
                    std::string courseId, name, desc, schedule, location;
                    int credits;
                    std::cout << "Enter course ID: ";
                    std::cin >> courseId;
                    std::cout << "Enter course name: ";
                    std::cin >> name;
                    std::cout << "Enter course description: ";
                    std::cin >> desc;
                    std::cout << "Enter course credits: ";
                    std::cin >> credits;
                    std::cout << "Enter course schedule: ";
                    std::cin >> schedule;
                    std::cout << "Enter course location: ";
                    std::cin >> location;
                    auto it = teachers.find(teacherId);
                    if (it != teachers.end()) {
                        // 创建并添加课程
                        Course newCourse(courseId, name, desc, credits, schedule, location);
                        courses.insert({courseId, newCourse});
                        it->second.addCourse(courseId);
                        std::cout << "Course added successfully!\n";
                    } else {
                        std::cout << "Teacher not found!\n";
                    }
                } else if (choice == 3) {
                    std::string courseId;
                    std::cout << "Enter course ID to remove: ";
                    std::cin >> courseId;
                    courses.erase(courseId);
                    if (courses.find(courseId) != courses.end()) {
                        // 检查教师ID是否存在
                        auto it = teachers.find(teacherId);
                        if (it != teachers.end()) {
                            // 移除课程并更新教师信息
                            courses.erase(courseId);
                            it->second.removeCourse(courseId);
                            std::cout << "Course removed successfully!\n";
                        } else {
                            std::cout << "Teacher not found!\n";
                        }
                    } else {
                        std::cout << "Course not found!\n";
                    }
                } else if (choice == 4) {
                    for (const auto& pair : courses) {
                        pair.second.displayInfo();
                    }
                } else if (choice == 5) {
                    for (const auto& record : enrollmentRecords) {
                        if (record.teacherId == teacherId) {
                            record.displayInfo();
                        }
                    }
                }
            } while (choice != 6);
        } else {
            std::cout << "Login failed!\n";
        }
    } else if (userType == "admin") {
        std::string adminId, password;
        std::cout << "Enter admin ID: ";
        std::cin >> adminId;
        std::cout << "Enter password: ";
        std::cin >> password;
        if (adminLogin(adminId, password)) {
            std::cout << "Login successful!\n";
            int choice;
            do {
                std::cout << "1. View Personal Info\n2. Add User\n3. Remove User\n4. Add Course\n5. Remove Course\n6. View Courses\n7. View Enrollments\n8. Exit\n";
                std::cout << "Enter choice: ";
                std::cin >> choice;
                if (choice == 1) {
                    auto it = admins.find(adminId);
                    it->second.displayInfo();
                } else if (choice == 2) {
                    std::string userType, id, name, major, title, department, password;
                    std::cout << "Enter user type (student/teacher/admin): ";
                    std::cin >> userType;
                    if (userType == "student") {
                        std::cout << "Enter student ID: ";
                        std::cin >> id;
                        if (students.find(id) != students.end()) {
                            std::cout << "Student ID already exists!\n";
                        } else {
                            std::cout << "Enter student name: ";
                            std::cin >> name;
                            std::cout << "Enter student major: ";
                            std::cin >> major;
                            students.insert({id, Student(id, name, major)});
                            std::cout << "Student added successfully!\n";
                        }
                    } else if (userType == "teacher") {
                        std::cout << "Enter teacher ID: ";
                        std::cin >> id;
                        if (teachers.find(id) != teachers.end()) {
                            std::cout << "Teacher ID already exists!\n";
                        } else {
                            std::cout << "Enter teacher name: ";
                            std::cin >> name;
                            std::cout << "Enter teacher title: ";
                            std::cin >> title;
                            std::cout << "Enter teacher department: ";
                            std::cin >> department;
                            std::cout << "Enter teacher password: ";
                            std::cin >> password;
                            teachers.insert({id, Teacher(id, name, title, department, password)});
                            std::cout << "Teacher added successfully!\n";
                        }
                    } else if (userType == "admin") {
                        std::cout << "Enter admin ID: ";
                        std::cin >> id;
                        if (admins.find(id) != admins.end()) {
                            std::cout << "Admin ID already exists!\n";
                        } else {
                            std::cout << "Enter admin name: ";
                            std::cin >> name;
                            std::cout << "Enter admin password: ";
                            std::cin >> password;
                            admins.insert({id, Admin(id, name, password)});
                            std::cout << "Admin added successfully!\n";
                        }
                    }
                } else if (choice == 3) {
                    std::string userType, id;
                    std::cout << "Enter user type (student/teacher/admin): ";
                    std::cin >> userType;
                    if (userType == "student") {
                        std::cout << "Enter student ID: ";
                        std::cin >> id;
                        students.erase(id);
                        std::cout << "Student removed successfully!\n";
                    } else if (userType == "teacher") {
                        std::cout << "Enter teacher ID: ";
                        std::cin >> id;
                        teachers.erase(id);
                        std::cout << "Teacher removed successfully!\n";
                    } else if (userType == "admin") {
                        std::cout << "Enter admin ID: ";
                        std::cin >> id;
                        admins.erase(id);
                        std::cout << "Admin removed successfully!\n";
                    }
                } else if (choice == 4) {
                    std::string courseId, name, desc, schedule, location;
                    int credits;
                    std::cout << "Enter course ID: ";
                    std::cin >> courseId;

                    if (courses.find(courseId) != courses.end()) {
                        std::cout << "Course ID already exists!\n";
                    } else {
                        std::cout << "Enter course name: ";
                        std::cin >> name;
                        std::cout << "Enter course description: ";
                        std::cin >> desc;
                        std::cout << "Enter course credits: ";
                        std::cin >> credits;
                        std::cout << "Enter course schedule: ";
                        std::cin >> schedule;
                        std::cout << "Enter course location: ";
                        std::cin >> location;

                        courses.insert({courseId, Course(courseId, name, desc, credits, schedule, location)});
                        std::cout << "Course added successfully!\n";
                    }

                } else if (choice == 5) {
                    std::string courseId;
                    std::cout << "Enter course ID to remove: ";
                    std::cin >> courseId;
                    courses.erase(courseId);
                    std::cout << "Course removed successfully!\n";
                } else if (choice == 6) {
                    for (const auto& pair : courses) {
                        pair.second.displayInfo();
                    }
                } else if (choice == 7) {
                    for (const auto& record : enrollmentRecords) {
                        record.displayInfo();
                    }
                }
            } while (choice != 8);
        } else {
            std::cout << "Login failed!\n";
        }
    } else {
        std::cout << "Invalid user type!\n";
    }

    saveStudents("D:\\system\\students.txt");
    saveTeachers("D:\\system\\teachers.txt");
    saveAdmins("D:\\system\\admins.txt");
    saveCourses("D:\\system\\courses.txt");
    saveEnrollmentRecords("D:\\system\\enrollment_records.txt");

    return 0;
}
