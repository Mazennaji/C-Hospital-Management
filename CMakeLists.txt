cmake_minimum_required(VERSION 3.20)
project(C_Hospital_Management C)

set(CMAKE_C_STANDARD 11)

add_executable(HospitalManagementSystem
        main.c
        patients.c
        patients.h
        doctors.c
        doctors.h
        appointments.c
        appointments.h
)