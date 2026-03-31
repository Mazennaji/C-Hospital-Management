cmake_minimum_required(VERSION 3.25)
project(HospitalManagementSystem C)

set(CMAKE_C_STANDARD 99)

add_executable(HospitalManagementSystem
        main.c
        patients.c
        doctors.c
        appointments.c
        patients.h
        doctors.h
        appointments.h
        patients.c)