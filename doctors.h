#ifndef DOCTORS_H
#define DOCTORS_H

#define MAX_DOCTORS 50
#define DOCTORS_FILE "doctors.dat"

typedef struct {
    int  id;
    char name[50];
    char specialty[50];
    char phone[15];
    char available[4];
} Doctor;

void addDoctor(void);
void viewDoctors(void);

int  loadDoctors(Doctor doctors[], int *count);
void saveDoctors(Doctor doctors[], int count);

#endif