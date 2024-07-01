#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_TITLE_LENGTH 50
#define MAX_CONTENT_LENGTH 500

// Structure to represent a diary entry
struct Entry {
    char date[20];
    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
};

// Function prototypes
void printMenu();
void addEntry(struct Entry diary[], int *count);
void editEntry(struct Entry diary[], int count);
void deleteEntry(struct Entry diary[], int *count);
void saveEntries(struct Entry diary[], int count);
void loadEntries(struct Entry diary[], int *count);

int main() {
    struct Entry diary[MAX_ENTRIES];
    int count = 0;
    int choice;

    // Load existing entries from file
    loadEntries(diary, &count);

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch(choice) {
            case 1:
                addEntry(diary, &count);
                break;
            case 2:
                editEntry(diary, count);
                break;
            case 3:
                deleteEntry(diary, &count);
                break;
            case 4:
                saveEntries(diary, count);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}

// Function to print the menu
void printMenu() {
    printf("\n====== Diary Management System Menu ======\n");
    printf("1. Add Entry\n");
    printf("2. Edit Entry\n");
    printf("3. Delete Entry\n");
    printf("4. Save Entries\n");
    printf("5. Exit\n");
    printf("==========================================\n");
}

// Function to add a new entry
void addEntry(struct Entry diary[], int *count) {
    if (*count < MAX_ENTRIES) {
        printf("\nEnter date (dd/mm/yyyy): ");
        scanf("%19s", diary[*count].date);
        getchar(); // Consume newline character left by scanf

        printf("Enter title: ");
        fgets(diary[*count].title, MAX_TITLE_LENGTH, stdin);
        diary[*count].title[strcspn(diary[*count].title, "\n")] = '\0'; // Remove newline from fgets

        printf("Enter content: ");
        fgets(diary[*count].content, MAX_CONTENT_LENGTH, stdin);
        diary[*count].content[strcspn(diary[*count].content, "\n")] = '\0'; // Remove newline from fgets

        (*count)++;
        printf("Entry added successfully.\n");
    } else {
        printf("Diary is full. Cannot add more entries.\n");
    }
}

// Function to edit an existing entry
void editEntry(struct Entry diary[], int count) {
    int index;
    printf("\nEnter the index of the entry to edit (1-%d): ", count);
    scanf("%d", &index);
    getchar(); // Consume newline character left by scanf

    if (index > 0 && index <= count) {
        printf("Enter new title: ");
        fgets(diary[index - 1].title, MAX_TITLE_LENGTH, stdin);
        diary[index - 1].title[strcspn(diary[index - 1].title, "\n")] = '\0'; // Remove newline from fgets

        printf("Enter new content: ");
        fgets(diary[index - 1].content, MAX_CONTENT_LENGTH, stdin);
        diary[index - 1].content[strcspn(diary[index - 1].content, "\n")] = '\0'; // Remove newline from fgets

        printf("Entry edited successfully.\n");
    } else {
        printf("Invalid entry index. Please try again.\n");
    }
}

// Function to delete an entry
void deleteEntry(struct Entry diary[], int *count) {
    int index;
    printf("\nEnter the index of the entry to delete (1-%d): ", *count);
    scanf("%d", &index);
    getchar(); // Consume newline character left by scanf

    if (index > 0 && index <= *count) {
        for (int i = index - 1; i < *count - 1; i++) {
            strcpy(diary[i].date, diary[i + 1].date);
            strcpy(diary[i].title, diary[i + 1].title);
            strcpy(diary[i].content, diary[i + 1].content);
        }
        (*count)--;
        printf("Entry deleted successfully.\n");
    } else {
        printf("Invalid entry index. Please try again.\n");
    }
}

// Function to save entries to a file
void saveEntries(struct Entry diary[], int count) {
    FILE *fp = fopen("diary_entries.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n%s\n%s\n", diary[i].date, diary[i].title, diary[i].content);
    }

    fclose(fp);
    printf("Entries saved to file successfully.\n");
}

// Function to load entries from a file
void loadEntries(struct Entry diary[], int *count) {
    FILE *fp = fopen("diary_entries.txt", "r");
    if (fp == NULL) {
        printf("No existing entries found.\n");
        return;
    }

    while (fscanf(fp, "%s", diary[*count].date) == 1) {
        fgetc(fp); // Consume newline left by fscanf

        fgets(diary[*count].title, MAX_TITLE_LENGTH, fp);
        diary[*count].title[strcspn(diary[*count].title, "\n")] = '\0'; // Remove newline from fgets

        fgets(diary[*count].content, MAX_CONTENT_LENGTH, fp);
        diary[*count].content[strcspn(diary[*count].content, "\n")] = '\0'; // Remove newline from fgets

        (*count)++;
    }

    fclose(fp);
    printf("Entries loaded successfully.\n");
}
