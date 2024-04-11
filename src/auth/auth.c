#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"

const int user_account_limitation = 5;
const int max_chars_per_line = 1024;

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

void store_current_info_in_struct_array(struct account_info *single_account, struct account_info all_accounts[], int index) {
    strcpy(all_accounts[index].iban, single_account->iban);
    strcpy(all_accounts[index].currency, single_account->currency);
    all_accounts[index].balance = single_account->balance;
    all_accounts[index].line_in_file = single_account->line_in_file;
}

int search_store_credentials(FILE *file_ptr, char *first_name, char *last_name, struct account_info *current_user_account_info, struct account_info current_user_accounts_info[]) {

    char line_reader[max_chars_per_line] = {};

    fgets(line_reader,max_chars_per_line,file_ptr);
    // stores header row in line_reader
    // every call of fgets reads a new row (max 1024 chars or until \n)

    int line_counter = 1, account_counter = 0;

    while ((fgets(line_reader,max_chars_per_line,file_ptr) != NULL) && (account_counter < user_account_limitation)){

        char *row_entry = strtok(line_reader, ","); // get first column (first_name)
        // future: modify the name that was read from the csv in order to not be case-sensitive -> strcasecmp?

        if (strcmp(row_entry, first_name) == 0) {
            printf("LOG: first_name MATCH FOUND ON LINE %d", line_counter);

            row_entry = strtok(NULL, ",");

            if (strcmp(row_entry, last_name) == 0) {

                printf("LOG: COMPLETE MATCH FOUND ONE LINE %d", line_counter);
                account_counter++;

                if(account_counter > 1) {
                    // start storing the multiple accounts in struct array
                    if (account_counter == 2) {
                        store_current_info_in_struct_array(current_user_account_info, current_user_accounts_info, 0);
                    }

                    strcpy(current_user_account_info->iban, strtok(NULL, ","));
                    strcpy(current_user_account_info->currency, strtok(NULL, ","));
                    current_user_account_info->balance = atoi(strtok(NULL, ","));
                    current_user_account_info->line_in_file = line_counter;

                    store_current_info_in_struct_array(current_user_account_info, current_user_accounts_info, account_counter-1);

                }

                else {
                    strcpy(current_user_account_info->iban, strtok(NULL, ","));
                    strcpy(current_user_account_info->currency, strtok(NULL, ","));
                    current_user_account_info->balance = (unsigned long int)strtok(NULL, ",");
                    current_user_account_info->line_in_file = line_counter;
                }

                account_counter++;

            }

        }

        else {
            printf("NO MATCH FOUND ON LINE %d", line_counter);
        }

        line_counter++;

    }

    return account_counter;

}

char auth(char *first_name, char *last_name){

    FILE *file_pointer = fopen("../../data.csv","r");

    if (file_pointer == NULL) {
        printf("ERROR: DATA CSV FILE NOT FOUND");
        fflush(stdout);
    }

    struct account_info *current_user_account_info = NULL;
    struct account_info current_user_accounts_info[user_account_limitation];

    int accounts_found = 0;
    accounts_found = search_store_credentials(file_pointer, first_name, last_name, current_user_account_info, current_user_accounts_info);
    char user_input = 0;

    if (accounts_found == 0) {

        no_accounts_found_request_input(&user_input);

        while (user_input == 1 && accounts_found == 0) {

            printf("Enter first name: ");
            scanf("%s", first_name);
            printf("Enter last name: ");
            scanf("%s", last_name);

            accounts_found = search_store_credentials(file_pointer, first_name, last_name, current_user_account_info, current_user_accounts_info);

            if (accounts_found == 0) 
                no_accounts_found_request_input(&user_input);

        }

        if (user_input == 2) {
            return '1';
        }

        if (user_input == 3) {
            return '2';
        }

        if (accounts_found > 0) {
            return '0';
        }
        

        /* scan user input
        while (user input = 1 and accounts_found = 0)
            search_store_credentials

        // out of while: user input is different OR account found

        if (user input = 2 [create new account])
            return "option create new accounts" (exits auth, back to login)
        if user input = 3 [quit]
            return "option quit" (exits auth, back to login)
        
        if accounts_found>0
            return "success" (exits auth, back to login with logged in options)
        
        */
    }
}