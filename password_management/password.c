#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PASSWORDS 100
#define MAX_LENGTH 50

typedef struct {
    char website[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} PasswordEntry;

PasswordEntry passwords[MAX_PASSWORDS];
int numPasswords = 0;


void removeNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void addPassword() {
    if (numPasswords >= MAX_PASSWORDS) {
        printf("Database is full. Cannot add more passwords.\n");
        return;
    }

    PasswordEntry newEntry;
    printf("Enter website: ");
    fgets(newEntry.website, MAX_LENGTH, stdin);
    printf("Enter username: ");
    fgets(newEntry.username, MAX_LENGTH, stdin);
    printf("Enter password: ");
    fgets(newEntry.password, MAX_LENGTH, stdin);

    // Remove trailing newline characters
    removeNewline(newEntry.website);
    removeNewline(newEntry.username);
    removeNewline(newEntry.password);

    passwords[numPasswords++] = newEntry;
    printf("Password added successfully.\n");
}

void viewPasswords() {
    if (numPasswords == 0) {
        printf("No passwords stored.\n");
        return;
    }

    printf("Website\t\tUsername\t\tPassword\n");
    for (int i = 0; i < numPasswords; i++) {
        printf("%s\t\t%s\t\t%s\n", passwords[i].website, passwords[i].username, passwords[i].password);
    }
}

void searchPasswords(char *searchWebsite) {

    removeNewline(searchWebsite);

    printf("Website\t\tUsername\t\tPassword\n");
    bool found = false;
    for (int i = 0; i < numPasswords; i++) {
        if (strcmp(passwords[i].website, searchWebsite) == 0) {
            printf("%s\t\t%s\t\t%s\n", passwords[i].website, passwords[i].username, passwords[i].password);
            found = true;
        }
    }
    if (!found) {
        printf("Password not found for the specified website.\n");
    }
}

int main() {
    int choice;
    char searchWebsite[MAX_LENGTH];

    do {
        printf("\n\n-------------------------------*_*----------Password Management Application----------*_*-------------------------------\n\n");
        printf("1.  Add Password\n\n");
        printf("2.  View Passwords\n\n");
        printf("3.  Search Passwords\n\n");
        printf("4.  Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                addPassword();
                break;
            case 2:
                viewPasswords();
                break;
            case 3:
                printf("Enter website to search: ");
                fgets(searchWebsite, MAX_LENGTH, stdin);
                searchPasswords(searchWebsite);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
