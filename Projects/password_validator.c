#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 20

// Function that checks if password is valid or not
// Prints error message
bool validatePassword(const char *password) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    bool hasSpace = false;
    int length = strlen(password);

    // Check for spaces or tabs
    for (int i = 0; i < length; i++) {
        if (isspace(password[i])) {
            hasSpace = true;
            break;
        }
    }
    if (hasSpace) {
        printf("No spaces allowed!\n");
        return false;
    }

    // Check length 
    if (length < 8) {
        printf("Must have at least 8 characters.\n");
        return false;
    }

    // Check character type
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else if (ispunct(password[i])) hasSpecial = true;
    }

    // Print any missing password requirements
    if (!hasUpper) printf("Must have at least 1 uppercase letter.\n");
    if (!hasLower) printf("Must have at least 1 lowercase letter.\n");
    if (!hasDigit) printf("Must have at least 1 number.\n");
    if (!hasSpecial) printf("Must have at least 1 special character.\n");

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main() {
    char password[MAX_LENGTH + 2]; // +2 to check for overflow

    printf("Please enter your password to test!\n");
    printf("Enter a string (max length %d): ", MAX_LENGTH);

    // Read input
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove newline if entered
    size_t len = strlen(password);
    if (len > 0 && password[len-1] == '\n') {
        password[len-1] = '\0';
        len--;
    }

    // Check for any overflow
    if (len >= MAX_LENGTH) {
        printf("Password entered is too long!\n");
        return 0;
    }

    // Check and print result
    if (validatePassword(password)) {
        printf("This is a valid password.\n");
    } else {
        printf("Invalid password!\n");
    }
    
    return 0;
}