#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100

// Structure to hold student data
struct Student {
    char name[50];
    int rollNumber;
    int marks;
    int semester;
    char department[20];
};

// Function to print a border for the table
void printBorder(int numColumns) {
    for (int i = 0; i < numColumns; i++) {
        printf("-------------");
    }
    printf("\n");
}

// Function to get an integer input with validation
int getIntegerInput() {
    int value;
    while (1) {
        printf("Enter a valid integer: ");
        if (scanf("%d", &value) == 1) {
            while (getchar() != '\n'); // Clear input buffer
            break;
        } else {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input. Please enter an integer.\n");
        }
    }
    return value;
}

// Function to get a string input containing only alphabets
void getStringInputAlphaOnly(char *str, int maxLen) {
    while (1) {
        printf("Enter a string (max %d characters, alphabets only): ", maxLen - 1);
        if (fgets(str, maxLen, stdin) != NULL) {
            size_t len = strlen(str);
            if (len > 0 && str[len - 1] == '\n') {
                str[len - 1] = '\0'; // Remove newline character
            }

            int validInput = 1;
            for (size_t i = 0; i < len - 1; i++) {
                if (!isalpha((unsigned char)str[i])) {
                    validInput = 0;
                    break;
                }
            }

            if (validInput) {
                break;
            } else {
                printf("Invalid input. Please enter a string containing only alphabets.\n");
            }
        } else {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input. Please enter a valid string.\n");
        }
    }
}

// Function to add a new student record
void addRecord(struct Student *students, int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    printf("Enter student name: ");
    getStringInputAlphaOnly(students[*numStudents].name, sizeof(students[*numStudents].name));

    printf("Enter roll number: ");
    students[*numStudents].rollNumber = getIntegerInput();

    printf("Enter semester: ");
    students[*numStudents].semester = getIntegerInput();

    printf("Enter department: ");
    getStringInputAlphaOnly(students[*numStudents].department, sizeof(students[*numStudents].department));

    printf("Enter marks: ");
    students[*numStudents].marks = getIntegerInput();

    (*numStudents)++;
    printf("Record added successfully.\n");
}

// Function to display all student records
void displayRecords(const struct Student *students, int numStudents) {
    if (numStudents == 0) {
        printf("No records available.\n");
        return;
    }

    int numColumns = 5; // Number of columns in the table
    printBorder(numColumns);

    printf("| %-10s | %-10s | %-10s | %-10s | %-10s \n", "Name", "Roll Number", "Semester", "Department", "Marks/500");

    printBorder(numColumns);

    for (int i = 0; i < numStudents; i++) {
        printf("| %-10s | %-10d | %-10d | %-10s | %-10d\n", students[i].name, students[i].rollNumber, students[i].semester, students[i].department, students[i].marks);
    }

    printBorder(numColumns);
}

// Function to search for a student record by roll number
void searchRecord(const struct Student *students, int numStudents) {
    int rollNumber;
    printf("Enter roll number to search: ");
    rollNumber = getIntegerInput();

    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            printBorder(5);
            printf("| %-10s | %-10s | %-10s | %-10s | %-10s \n", "Name", "Roll Number", "Semester", "Department", "Marks/500");
            printBorder(5);
            printf("| %-10s | %-10d | %-10d | %-10s | %-10d\n", students[i].name, students[i].rollNumber, students[i].semester, students[i].department, students[i].marks);
            printBorder(5);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }
}

// Function to delete a student record by roll number
void deleteRecord(struct Student *students, int *numStudents) {
    int rollNumber;
    printf("Enter roll number to delete: ");
    rollNumber = getIntegerInput();

    int found = 0;
    for (int i = 0; i < *numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < *numStudents - 1; j++) {
                strcpy(students[j].name, students[j + 1].name);
                students[j].rollNumber = students[j + 1].rollNumber;
                students[j].semester = students[j + 1].semester;
                strcpy(students[j].department, students[j + 1].department);
                students[j].marks = students[j + 1].marks;
            }
            (*numStudents)--;
            printf("Record deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }
}

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    do {
        printf("\nStudent Record System\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice = getIntegerInput();

        switch (choice) {
            case 1:
                addRecord(students, &numStudents);
                break;
            case 2:
                displayRecords(students, numStudents);
                break;
            case 3:
                searchRecord(students, numStudents);
                break;
            case 4:
                deleteRecord(students, &numStudents);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
