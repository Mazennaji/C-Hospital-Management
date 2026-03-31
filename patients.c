#include <stdio.h>
#include <string.h>
#include "patients.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void printSeparator(void) {
    printf("--------------------------------------------------\n");
}

static void printPatient(const Patient *p) {
    printSeparator();
    printf("  ID        : %d\n",  p->id);
    printf("  Name      : %s\n",  p->name);
    printf("  Age       : %d\n",  p->age);
    printf("  Gender    : %s\n",  p->gender);
    printf("  Phone     : %s\n",  p->phone);
    printf("  Diagnosis : %s\n",  p->diagnosis);
}

int loadPatients(Patient patients[], int *count) {
    FILE *fp = fopen(PATIENTS_FILE, "rb");
    *count = 0;
    if (!fp) return 0;
    while (fread(&patients[*count], sizeof(Patient), 1, fp) == 1) {
        (*count)++;
        if (*count >= MAX_PATIENTS) break;
    }
    fclose(fp);
    return 1;
}

void savePatients(Patient patients[], int count) {
    FILE *fp = fopen(PATIENTS_FILE, "wb");
    if (!fp) { printf("  [ERROR] Cannot open %s for writing.\n", PATIENTS_FILE); return; }
    fwrite(patients, sizeof(Patient), count, fp);
    fclose(fp);
}

void addPatient(void) {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    loadPatients(patients, &count);

    if (count >= MAX_PATIENTS) { printf("  [ERROR] Patient database is full.\n"); return; }

    Patient p;
    p.id = (count == 0) ? 1 : patients[count - 1].id + 1;

    printf("\n  --- Add New Patient (ID: %d) ---\n", p.id);

    printf("  Name      : ");
    clearInputBuffer();
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("  Age       : ");
    scanf("%d", &p.age);

    printf("  Gender    : ");
    clearInputBuffer();
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = '\0';

    printf("  Phone     : ");
    fgets(p.phone, sizeof(p.phone), stdin);
    p.phone[strcspn(p.phone, "\n")] = '\0';

    printf("  Diagnosis : ");
    fgets(p.diagnosis, sizeof(p.diagnosis), stdin);
    p.diagnosis[strcspn(p.diagnosis, "\n")] = '\0';

    patients[count++] = p;
    savePatients(patients, count);
    printf("\n  [OK] Patient \"%s\" added (ID: %d).\n", p.name, p.id);
}

void viewPatients(void) {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    loadPatients(patients, &count);

    printf("\n  === All Patients (%d records) ===\n", count);
    if (count == 0) { printf("  No patients found.\n"); return; }

    for (int i = 0; i < count; i++) printPatient(&patients[i]);
    printSeparator();
}