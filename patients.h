#ifndef PATIENTS_H
#define PATIENTS_H

#define MAX_PATIENTS 100
#define PATIENTS_FILE "patients.dat"

typedef struct {
    int    id;
    char   name[50];
    int    age;
    char   gender[10];
    char   phone[15];
    char   diagnosis[100];
} Patient;

void addPatient(void);
void viewPatients(void);
void searchPatientByID(void);
void editPatient(void);
void deletePatient(void);

int  loadPatients(Patient patients[], int *count);
void savePatients(Patient patients[], int count);

#endif