#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Define the Student structure
typedef struct {
    char name[50];
    char dateOfBirth[11];
    char registrationNumber[6];
    char programCode[4];
    float annualTuition;
    int isActive; // Flag to check if the slot is active
} Student;

// Array to hold student records
Student students[MAX_STUDENTS];

// Function declarations
int findEmptySlot();
int findStudentByRegNum(const char* regNum);
void addStudent();
void listStudents();
void updateStudent();
void deleteStudent();
void searchStudent();
void sortStudents();
void exportToCSV();
void displayMenu();

int main() {
    int choice;

    // Initialize all student slots as inactive
    for (int i = 0; i < MAX_STUDENTS; i++) {
        students[i].isActive = 0;
    }

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                listStudents();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                exportToCSV();
                break;
            case 8:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n--- Student Management System Menu ---\n");
    printf("1. Add Student\n");
    printf("2. List All Students\n");
    printf("3. Update Student\n");
    printf("4. Delete Student\n");
    printf("5. Search Student by Registration Number\n");
    printf("6. Sort Students\n");
    printf("7. Export Students to CSV\n");
    printf("8. Exit\n");
}

// Implementations of all functions

int findEmptySlot() {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (!students[i].isActive) {
            return i;
        }
    }
    return -1;
}

int findStudentByRegNum(const char* regNum) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].isActive && strcmp(students[i].registrationNumber, regNum) == 0) {
            return i;
        }
    }
    return -1;
}

void addStudent() {
    int slot = findEmptySlot();
    if (slot == -1) {
        printf("No available slot. Maximum number of students reached.\n");
        return;
    }
    printf("Enter name: ");
    scanf("%s", students[slot].name);

    printf("Enter date of birth (YYYY-MM-DD): ");
    scanf("%s", students[slot].dateOfBirth);

    printf("Enter registration number (6 digits): ");
    scanf("%s", students[slot].registrationNumber);

    printf("Enter program code: ");
    scanf("%s", students[slot].programCode);

    printf("Enter annual tuition: ");
    scanf("%f", &students[slot].annualTuition);

    students[slot].isActive = 1;
    printf("Student added successfully!\n");
}

void listStudents() {
    printf("Active students:\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].isActive) {
            printf("Name: %s, DOB: %s, regNum: %s, Program: %s, Tuition: %.2f\n",
                students[i].name, students[i].dateOfBirth, students[i].registrationNumber,
                students[i].programCode, students[i].annualTuition);
        }
    }
}

void updateStudent() {
    char regNum[7];
    printf("Enter registration number of the student to update: ");
    scanf("%s", regNum);
    int index = findStudentByRegNum(regNum);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }
    printf("Enter new name: ");
    scanf("%s", students[index].name);
    printf("Enter new date of birth (YYYY-MM-DD): ");
    scanf("%s", students[index].dateOfBirth);
    printf("Enter new registration number (6 digits): ");
    scanf("%s", students[index].registrationNumber);
    printf("Enter new program code: ");
    scanf("%s", students[index].programCode);
    printf("Enter new annual tuition: ");
    scanf("%f", &students[index].annualTuition);
    printf("Student information updated successfully!\n");
}

void deleteStudent() {
    char regNum[7];
    printf("Enter registration number of the student to delete: ");
    scanf("%s", regNum);
    int index = findStudentByRegNum(regNum);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }
    students[index].isActive = 0;
    printf("Student record deleted successfully.\n");
}

void searchStudent() {
    char regNum[7];
    printf("Enter registration number to search: ");
    scanf("%s", regNum);
    int index = findStudentByRegNum(regNum);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }
    printf("Student found: Name: %s, DOB: %s, RegNum: %s, Program: %s, Tuition: %.2f\n",
        students[index].name, students[index].dateOfBirth, students[index].registrationNumber,
        students[index].programCode, students[index].annualTuition);
}

void sortStudents() {
    // Simple bubble sort by name
    int i, j;
    for (i = 0; i < MAX_STUDENTS - 1; i++) {
        for (j = 0; j < MAX_STUDENTS - i - 1; j++) {
            if (students[j].isActive && students[j + 1].isActive && strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted by name.\n");
}

void exportToCSV() {
    FILE *fp = fopen("students.csv", "a");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].isActive) {
            fprintf(fp, "%s,%s,%s,%s,%.2f\n",
                students[i].name, students[i].dateOfBirth, students[i].registrationNumber,
                students[i].programCode, students[i].annualTuition);
        }
    }
    fclose(fp);
    printf("Data exported successfully to 'students.csv'\n");
}
