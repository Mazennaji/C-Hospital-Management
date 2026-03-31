#include <stdio.h>
#include <string.h>
#include "doctors.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void printSeparator(void) {
    printf("--------------------------------------------------\n");
}

static void printDoctor(const Doctor *d) {
    printSeparator();
    printf("  ID          : %d\n",  d->id);
    printf("  Name        : %s\n",  d->name);
    printf("  Specialty   : %s\n",  d->specialty);
    printf("  Phone       : %s\n",  d->phone);
    printf("  Available   : %s\n",  d->available);
}

int loadDoctors(Doctor doctors[], int *count) {
    FILE *fp = fopen(DOCTORS_FILE, "rb");
    *count = 0;
    if (!fp) return 0;
    while (fread(&doctors[*count], sizeof(Doctor), 1, fp) == 1) {
        (*count)++;
        if (*count >= MAX_DOCTORS) break;
    }
    fclose(fp);
    return 1;
}

void saveDoctors(Doctor doctors[], int count) {
    FILE *fp = fopen(DOCTORS_FILE, "wb");
    if (!fp) { printf("  [ERROR] Cannot open %s for writing.\n", DOCTORS_FILE); return; }
    fwrite(doctors, sizeof(Doctor), count, fp);
    fclose(fp);
}

void addDoctor(void) {
    Doctor doctors[MAX_DOCTORS];
    int count = 0;
    loadDoctors(doctors, &count);

    if (count >= MAX_DOCTORS) { printf("  [ERROR] Doctor database is full.\n"); return; }

    Doctor d;
    d.id = (count == 0) ? 1 : doctors[count - 1].id + 1;

    printf("\n  --- Add New Doctor (ID: %d) ---\n", d.id);
    clearInputBuffer();

    printf("  Name        : ");
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = '\0';

    printf("  Specialty   : ");
    fgets(d.specialty, sizeof(d.specialty), stdin);
    d.specialty[strcspn(d.specialty, "\n")] = '\0';

    printf("  Phone       : ");
    fgets(d.phone, sizeof(d.phone), stdin);
    d.phone[strcspn(d.phone, "\n")] = '\0';

    printf("  Available (Yes/No): ");
    fgets(d.available, sizeof(d.available), stdin);
    d.available[strcspn(d.available, "\n")] = '\0';

    doctors[count++] = d;
    saveDoctors(doctors, count);
    printf("\n  [OK] Dr. \"%s\" added (ID: %d).\n", d.name, d.id);
}

void viewDoctors(void) {
    Doctor doctors[MAX_DOCTORS];
    int count = 0;
    loadDoctors(doctors, &count);

    printf("\n  === All Doctors (%d records) ===\n", count);
    if (count == 0) { printf("  No doctors found.\n"); return; }

    for (int i = 0; i < count; i++) printDoctor(&doctors[i]);
    printSeparator();
}