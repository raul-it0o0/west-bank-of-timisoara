#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../src/auth/auth.h"
#include "../src/user_inputs/user_inputs.h"
#include "../src/auth_success/auth_success.h"

// #include <ncurses>

/* void create_temp_csv(struct account_struct found_accounts[], int accounts_found) {

    FILE *temp_csv = fopen("temp.csv", "w");

    fprintf(temp_csv, "IBAN,Currency,Balance,LineInFile\n");

    for (int i=0; i < accounts_found; i++) {
        fprintf(temp_csv,"%s,%s,%lu,%u",found_accounts[i].iban,found_accounts[i].currency,found_accounts[i].balance,found_accounts[i].line_in_file);
    }

    fclose(temp_csv);
}

void state_found_accounts(char *user_input, char *first_name, char *last_name, struct account_struct accounts[], int accounts_found) {
    printf("LOG: >0 ACCOUNTS MATCHED, CREATING TEMP CSV\n");
    fflush(stdout);
    create_temp_csv(accounts, accounts_found);

    // logged in state function in a separate file?

    // center in terminal
    printf("~~~WEST BANK OF TIMISOARA~~~\n");
    printf("All rights reserved.\n");

    printf("\nWelcome %s! What would you like to do today?\n", first_name); // add name from csv file
    user_input = menu_print_and_parse(user_input);

    if (user_input == '1')

}

void state_no_accounts_found(char *user_input, FILE *file_ptr, char *first_name, char *last_name, struct account_struct accounts[]) {
    // no accounts found, try again OR create new account
    printf("\nNo accounts matching %s %s.\nSelect an option.");
    printf("TRY AGAIN [1]\n");
    printf("CREATE NEW ACCOUNT [2]\n");
    printf("EXIT [3]\n");

    scanf("%s", user_input);

    while ((user_input != (char*)1) || (user_input != (char*)2) || (user_input != (char*)3)) {
        printf("\nOption must be a number between 1 and 4. Try again.\n");
        fflush(stdout);
        scanf("%c", user_input);
    }

    if (user_input == (char*)1) {
        printf("Enter first name: ");
        scanf("%s", first_name);
        printf("Enter last name: ");
        scanf("%s", last_name);
        int accounts_found = 0;
        accounts_found = search_store_credentials(file_ptr, first_name, last_name, accounts);

        if (accounts_found > 0) {
            printf("")
        }


    }
} */


/* int search_store_credentials(FILE *file_ptr, char *first_name, char *last_name, struct account_struct accounts[]) {
    
    char line_reader[maxLineSize] = {};
    bool account_found = false;

    fgets(line_reader,maxLineSize,file_ptr);
    // stores header row in line_reader
    // every call of fgets reads a new row (max 1024 chars or until \n)

    int line_counter = 1, account_counter = 0;

    while ((fgets(line_reader,maxLineSize,file_ptr) != NULL) && (account_counter < user_account_limitation)){

        char *row_entry = strtok(line_reader, ","); // get first column (first_name)
        // future: modify the name that was read from the csv in order to not be case-sensitive -> strcasecmp?

        if (strcmp(row_entry, first_name) == 0) {
            printf("LOG: first_name MATCH FOUND ON LINE %d", line_counter);

            row_entry = strtok(NULL, ",");
            if (strcmp(row_entry, last_name) == 0) {
                printf("LOG: COMPLETE MATCH FOUND ONE LINE %d", line_counter);

                strcpy(accounts[account_counter].iban, strtok(NULL, ","));
                strcpy(accounts[account_counter].currency, strtok(NULL, ","));
                accounts[account_counter].balance = (unsigned long int)strtok(NULL, ",");
                accounts[account_counter].line_in_file = line_counter;

                account_counter++;
            }
        }

        else {
            printf("NO MATCH FOUND ON LINE %d", line_counter);
        }
            
        
        line_counter++;
    }

    return account_counter;

} */



int main(int argc, char *argv[]){

    if (argc != 3)
        return printf("\nERROR: WRONG NUMBER OF ARGUMENTS\nPASS 2 ARGUMENTS AS FOLLOWS:\n./login [name] [surname]\n");
    
    char *first_name = argv[1], *last_name = argv[2];

    struct account *singular_account = calloc(1, sizeof(struct account));
    struct account *user_accounts = calloc(USER_ACCOUNT_LIMITATION, sizeof(struct account));
    int accounts_found;
    char user_response = auth(first_name, last_name, singular_account, user_accounts, &accounts_found);

    if (user_response == '0') {
        printf("\nLog: FOUND 1 MATCHING ACCOUNT TO USER\n");
        free(user_accounts);
        auth_success(first_name, last_name, singular_account, &accounts_found);
        return 0;
    }

    else if (user_response == '1') {
        printf("\nLog: MULTIPLE ACCOUNTS FOUND FOR USER\n");
        free(singular_account);
        auth_success(first_name, last_name, user_accounts, &accounts_found);
        return 0;
    }

    else if (user_response == '2') {
        printf("\nLog: NO MATCHES FOUND. USER WANTS TO CREATE A NEW ACCOUNT\n");
        free(user_accounts);
        free(singular_account);
        return 0;
    }

    else if (user_response == '3') {
        printf("\nLog: NO MATCHES FOUND. USER REQUESTED EXIT / FATAL ERROR\n");
        free(user_accounts);
        free(singular_account);
        return 0;
    }

    return 0;
}