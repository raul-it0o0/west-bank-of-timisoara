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

int search_store_credentials(FILE *file_ptr, char *first_name, char *last_name, struct account current_user_accounts_info[]) {

    char row_reader[MAX_CHARS_PER_LINE];

    fgets(row_reader,MAX_CHARS_PER_LINE,file_ptr);
    // stores header row in row_reader
    // every call of fgets reads a new row (max 1024 chars or until \n)

    int line_counter = 1, account_counter = 0;

    while ((fgets(row_reader,MAX_CHARS_PER_LINE,file_ptr) != NULL) && (account_counter < USER_ACCOUNT_LIMITATION)){

        char *row_entry = strtok(row_reader, ","); // get first column (first_name)
        // future: modify the name that was read from the csv in order to not be case-sensitive -> strcasecmp?

        if (strcmp(row_entry, first_name) == 0) {
//            printf("\nLog: first_name MATCH FOUND ON LINE %d\n", line_counter);

            row_entry = strtok(NULL, ",");

            if (strcmp(row_entry, last_name) == 0) {

//                printf("\nLog: COMPLETE MATCH FOUND ONE LINE %d\n", line_counter);
                account_counter++;

                strncpy(current_user_accounts_info[account_counter-1].iban, strtok(NULL, ","), 15);
                current_user_accounts_info[account_counter-1].iban[15] = '\0';
                strncpy(current_user_accounts_info[account_counter-1].currency, strtok(NULL, ","), 3);
                current_user_accounts_info[account_counter-1].balance = strtol(strtok(NULL, ","), NULL, 0);

            }

        }

        else {
//            printf("\nLog: NO MATCH FOUND ON LINE %d\n", line_counter);
        }

        line_counter++;

    }

    fclose(file_ptr);

    return account_counter;

}

char auth(char *first_name, char *last_name, struct account accounts_info[], int *accounts_found){

    FILE *file_ptr = fopen("../data/data.csv","r");

    if (file_ptr == NULL) {
        printf("ERROR: DATA CSV FILE NOT FOUND");
        return '3';
    }

    *accounts_found = search_store_credentials(file_ptr, first_name, last_name, accounts_info);

    char user_input = 0;

    if (*accounts_found == 0) {

        no_accounts_found_request_input(&user_input);

        while (user_input == '1' && *accounts_found == 0) {

            printf("Enter first name: ");
            scanf("%s", first_name);
            printf("Enter last name: ");
            scanf("%s", last_name);

            *accounts_found = search_store_credentials(file_ptr, first_name, last_name, accounts_info);

            if (*accounts_found == 0)
                no_accounts_found_request_input(&user_input);
        }

        if (user_input == '2') {
            return '2';
        }

        if (user_input == '3') {
            return '3';
        }

        if (*accounts_found == 1) {
            return '0';
        }

        if (*accounts_found > 1) {
            return '1';
        }
    }

    else {
        if (*accounts_found == 1)
            return '0';
        else /* if (*accounts_found > 1) */ {
            return '1';
        }
    }
    
}