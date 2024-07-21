cmake_minimum_required(VERSION 3.26)
project(system)

set(CMAKE_CXX_STANDARD 17)

add_executable(system main.cpp
        Course.h
        Course.cpp
        Teacher.h
        Teacher.cpp
        Student.h
        Student.cpp
        Admin.h
        Admin.cpp
        EnrollmentRecord.h
        EnrollmentRecord.cpp)
