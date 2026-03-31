#include <stdio.h>
#include <stdlib.h>
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

void searchPatientByID(void) {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    loadPatients(patients, &count);

    int id;
    printf("\n  Enter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("\n  === Patient Found ===\n");
            printPatient(&patients[i]);
            printSeparator();
            return;
        }
    }
    printf("  [!] No patient found with ID %d.\n", id);
}

void editPatient(void) {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    loadPatients(patients, &count);

    int id;
    printf("\n  Enter Patient ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("\n  Editing Patient ID %d - press Enter to keep current value.\n", id);
            char buf[100];
            clearInputBuffer();

            printf("  Name      [%s]: ", patients[i].name);
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';
            if (strlen(buf) > 0) strncpy(patients[i].name, buf, sizeof(patients[i].name));

            printf("  Age       [%d]: ", patients[i].age);
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';
            if (strlen(buf) > 0) patients[i].age = atoi(buf);

            printf("  Gender    [%s]: ", patients[i].gender);
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';
            if (strlen(buf) > 0) strncpy(patients[i].gender, buf, sizeof(patients[i].gender));

            printf("  Phone     [%s]: ", patients[i].phone);
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';
            if (strlen(buf) > 0) strncpy(patients[i].phone, buf, sizeof(patients[i].phone));

            printf("  Diagnosis [%s]: ", patients[i].diagnosis);
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';
            if (strlen(buf) > 0) strncpy(patients[i].diagnosis, buf, sizeof(patients[i].diagnosis));

            savePatients(patients, count);
            printf("\n  [OK] Patient ID %d updated.\n", id);
            return;
        }
    }
    printf("  [!] No patient found with ID %d.\n", id);
}

void deletePatient(void) {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    loadPatients(patients, &count);

    int id;
    printf("\n  Enter Patient ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("  Deleting \"%s\" (ID: %d). Confirm? (y/n): ",
                   patients[i].name, id);
            char c;
            clearInputBuffer();
            scanf("%c", &c);
            if (c != 'y' && c != 'Y') {
                printf("  Deletion cancelled.\n");
                return;
            }
            for (int j = i; j < count - 1; j++)
                patients[j] = patients[j + 1];
            count--;
            savePatients(patients, count);
            printf("\n  [OK] Patient ID %d deleted.\n", id);
            return;
        }
    }
    printf("  [!] No patient found with ID %d.\n", id);
}