#include <stdio.h>
#include <stdlib.h>
#include "patients.h"
#include "doctors.h"
#include "appointments.h"

static void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pressEnterToContinue(void) {
    printf("\n  Press Enter to continue...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

static void printMenu(void) {
    printf("\n");
    printf("  +================================================+\n");
    printf("  |       HOSPITAL MANAGEMENT SYSTEM  v1.0        |\n");
    printf("  |             Console Edition  [C]               |\n");
    printf("  +================================================+\n");
    printf("\n");
    printf("   PATIENT MANAGEMENT\n");
    printf("  ------------------------------------------------\n");
    printf("   1.  Add Patient\n");
    printf("   2.  View All Patients\n");
    printf("   3.  Search Patient by ID\n");
    printf("   4.  Edit Patient\n");
    printf("   5.  Delete Patient\n");
    printf("\n");
    printf("   DOCTOR MANAGEMENT\n");
    printf("  ------------------------------------------------\n");
    printf("   6.  Add Doctor\n");
    printf("   7.  View Doctors\n");
    printf("\n");
    printf("   APPOINTMENT MANAGEMENT\n");
    printf("  ------------------------------------------------\n");
    printf("   8.  Book Appointment\n");
    printf("   9.  View Appointments\n");
    printf("\n");
    printf("  ------------------------------------------------\n");
    printf("   0.  Exit\n");
    printf("  ------------------------------------------------\n");
    printf("\n  Enter your choice: ");
}

int main(void) {
    int choice;
    while (1) {
        clearScreen();
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:  addPatient();        pressEnterToContinue(); break;
            case 2:  viewPatients();      pressEnterToContinue(); break;
            case 3:  searchPatientByID(); pressEnterToContinue(); break;
            case 4:  editPatient();       pressEnterToContinue(); break;
            case 5:  deletePatient();     pressEnterToContinue(); break;
            case 6:  addDoctor();         pressEnterToContinue(); break;
            case 7:  viewDoctors();       pressEnterToContinue(); break;
            case 8:  bookAppointment();   pressEnterToContinue(); break;
            case 9:  viewAppointments();  pressEnterToContinue(); break;
            case 0:
                clearScreen();
                printf("\n  Goodbye! Stay healthy.\n\n");
                return 0;
            default:
                printf("\n  [!] Invalid choice. Enter 0-9.\n");
                pressEnterToContinue();
                break;
        }
    }
}