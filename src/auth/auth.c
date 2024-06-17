#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"

void no_accounts_found_request_input(char *user_input) {
        
    printf("\nNo accounts found with the provided information.\n");
    printf("Please enter an option 1-3:\n\n");
    printf("TRY AGAIN [1]\n");
    printf("CREATE NEW ACCOUNT [2]\n");
    printf("EXIT [3]\n\n");

    scanf("%c", user_input);
    while ((*user_input != '1')&&(*user_input != '2')&&(*user_input != '3')) {
        printf("ERROR Invalid input. Please enter an option 1-3.\n");
        scanf("%c", user_input);
    }
    
}

int search_store_credentials(FILE *file_ptr, char *first_name, char *last_name, BankAccount
current_user_accounts_info[]) {

    char row_reader[MAX_CHARS_PER_LINE];

    fgets(row_reader,MAX_CHARS_PER_LINE,file_ptr);
    // Store (and ignores, i.e. does not process) header row in row_reader
    // Every call of fgets reads a new row (max 1024 chars or until \n)

    int line_counter = 1, account_counter = 0;

    while ((fgets(row_reader,MAX_CHARS_PER_LINE,file_ptr) != NULL) && (account_counter < USER_ACCOUNT_LIMITATION)){

        char *row_entry = strtok(row_reader, ","); // get first column (first_name)
        // future: modify the name that was read from the csv in order to not be case-sensitive -> strcasecmp?

        // If entry matches first name
        if (strcmp(row_entry, first_name) == 0) {

            row_entry = strtok(NULL, ",");

            // If entry matches last name -> Match found
            if (strcmp(row_entry, last_name) == 0) {

                account_counter++;

                // Store IBAN (length: 15)  
                strncpy(current_user_accounts_info[account_counter-1].iban, strtok(NULL, ","), 15);
                // Add string null terminator
                current_user_accounts_info[account_counter-1].iban[15] = '\0';

                // Store currency (why length 3?)
                strncpy(current_user_accounts_info[account_counter-1].currency, strtok(NULL, ","), 3);

                // Convert string read into float number and store as balance
                current_user_accounts_info[account_counter-1].balance = strtol(strtok(NULL, ","), NULL, 0);

            }

        }

        line_counter++; // is this variable helpful?

    }

    // Close file that was opened in the auth() function
    fclose(file_ptr);

    // Return the number of accounts found for entered credentials
    return account_counter;

}

int auth(char *first_name, char *last_name, BankAccount accounts_info[], int *accounts_found){

    // Open data file
    FILE *file_ptr = fopen("../data/data.csv","r");

    if (file_ptr == NULL) {
        printf("ERROR: DATA CSV FILE NOT FOUND");
        return '3';
    }

    // Get number of accounts matching credentials
    *accounts_found = search_store_credentials(file_ptr, first_name, last_name, accounts_info);

    char user_input = 0;

    // If credentials don't match to an account in the DB
    if (*accounts_found == 0) {

        // Ask user for what to do next (Try again, Create new account or Exit)
        no_accounts_found_request_input(&user_input);

        // While user asks to 'TRY AGAIN' and no accounts were found
        while (user_input == '1' && *accounts_found == 0) {

            // Get credentials
            printf("Enter first name: ");
            scanf("%s", first_name);
            printf("Enter last name: ");
            scanf("%s", last_name);

            // Get number of accounts matching credentials
            *accounts_found = search_store_credentials(file_ptr, first_name, last_name, accounts_info);

            if (*accounts_found == 0)
                no_accounts_found_request_input(&user_input);
        }

        if (user_input == '2') {
            // 'CREATE NEW ACCOUNT'
            return 2;
        }

        if (user_input == '3') {
            // 'EXIT'
            return 3;
        }

        if (*accounts_found == 1) {
            // 1 account matching credentials after initial wrong input(s)
            return 0;
        }

        if (*accounts_found > 1) {
            // Multiple accounts matching credentials after initial wrong input(s)
            return 1;
        }
    }

    else {
        
        if (*accounts_found == 1)
            // 1 account matching credentials
            return 0;

        else /* if (*accounts_found > 1) */
            return 1;
        
    }
    
}