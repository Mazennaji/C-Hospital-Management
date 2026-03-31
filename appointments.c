#include <stdio.h>
#include <string.h>
#include "appointments.h"
#include "patients.h"
#include "doctors.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void printSeparator(void) {
    printf("--------------------------------------------------\n");
}

static void printAppointment(const Appointment *a) {
    printSeparator();
    printf("  Appt ID       : %d\n",  a->id);
    printf("  Patient       : %s (ID: %d)\n", a->patientName, a->patientID);
    printf("  Doctor        : %s (ID: %d)\n", a->doctorName,  a->doctorID);
    printf("  Date          : %s\n",  a->date);
    printf("  Time          : %s\n",  a->time);
    printf("  Status        : %s\n",  a->status);
}

int loadAppointments(Appointment appointments[], int *count) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "rb");
    *count = 0;
    if (!fp) return 0;
    while (fread(&appointments[*count], sizeof(Appointment), 1, fp) == 1) {
        (*count)++;
        if (*count >= MAX_APPOINTMENTS) break;
    }
    fclose(fp);
    return 1;
}

void saveAppointments(Appointment appointments[], int count) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "wb");
    if (!fp) { printf("  [ERROR] Cannot open %s for writing.\n", APPOINTMENTS_FILE); return; }
    fwrite(appointments, sizeof(Appointment), count, fp);
    fclose(fp);
}

void bookAppointment(void) {
    Appointment appts[MAX_APPOINTMENTS];
    int apptCount = 0;
    loadAppointments(appts, &apptCount);

    if (apptCount >= MAX_APPOINTMENTS) { printf("  [ERROR] Appointment database is full.\n"); return; }

    Patient patients[MAX_PATIENTS];
    Doctor  doctors[MAX_DOCTORS];
    int pCount = 0, dCount = 0;
    loadPatients(patients, &pCount);
    loadDoctors(doctors, &dCount);

    if (pCount == 0) { printf("  [!] No patients registered.\n"); return; }
    if (dCount == 0) { printf("  [!] No doctors registered.\n");  return; }

    Appointment a;
    a.id = (apptCount == 0) ? 1 : appts[apptCount - 1].id + 1;

    printf("\n  --- Book Appointment (ID: %d) ---\n", a.id);

    int pid;
    printf("  Patient ID  : ");
    scanf("%d", &pid);
    int pFound = 0;
    for (int i = 0; i < pCount; i++) {
        if (patients[i].id == pid) {
            a.patientID = pid;
            strncpy(a.patientName, patients[i].name, sizeof(a.patientName));
            pFound = 1; break;
        }
    }
    if (!pFound) { printf("  [!] Patient ID %d not found.\n", pid); return; }

    int did;
    printf("  Doctor ID   : ");
    scanf("%d", &did);
    int dFound = 0;
    for (int i = 0; i < dCount; i++) {
        if (doctors[i].id == did) {
            a.doctorID = did;
            strncpy(a.doctorName, doctors[i].name, sizeof(a.doctorName));
            dFound = 1; break;
        }
    }
    if (!dFound) { printf("  [!] Doctor ID %d not found.\n", did); return; }

    clearInputBuffer();
    printf("  Date (DD/MM/YYYY): ");
    fgets(a.date, sizeof(a.date), stdin);
    a.date[strcspn(a.date, "\n")] = '\0';

    printf("  Time (HH:MM)     : ");
    fgets(a.time, sizeof(a.time), stdin);
    a.time[strcspn(a.time, "\n")] = '\0';

    strncpy(a.status, "Scheduled", sizeof(a.status));
    appts[apptCount++] = a;
    saveAppointments(appts, apptCount);

    printf("\n  [OK] Appointment booked: %s with %s on %s at %s\n",
           a.patientName, a.doctorName, a.date, a.time);
}

void viewAppointments(void) {
    Appointment appts[MAX_APPOINTMENTS];
    int count = 0;
    loadAppointments(appts, &count);

    printf("\n  === All Appointments (%d records) ===\n", count);
    if (count == 0) { printf("  No appointments found.\n"); return; }

    for (int i = 0; i < count; i++) printAppointment(&appts[i]);
    printSeparator();
}