#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#define MAX_APPOINTMENTS 200
#define APPOINTMENTS_FILE "appointments.dat"

typedef struct {
    int  id;
    int  patientID;
    int  doctorID;
    char patientName[50];
    char doctorName[50];
    char date[15];
    char time[10];
    char status[20];
} Appointment;

void bookAppointment(void);
void viewAppointments(void);

int  loadAppointments(Appointment appointments[], int *count);
void saveAppointments(Appointment appointments[], int count);

#endif