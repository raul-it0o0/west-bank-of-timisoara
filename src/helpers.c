#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
//#include "menus.h"

char* char_to_str(char c) {
    char *str = calloc(2, sizeof(char));
    str[0] = c;

    return str;
}

char* generate_iban(char *first_name, char *last_name){
    char *iban = calloc(15 + 1, sizeof(char));

    strncat(iban, char_to_str(first_name[0]),1);
    strncat(iban, char_to_str(last_name[0]),1);

    for (unsigned char i = 0; i < 13; i++) {
        char digit_str[1];

        char *generated_digit = calloc(2, sizeof(char));
        sprintf(generated_digit, "%d", (rand()%10));
        digit_str[0] = *generated_digit;
        strncat(iban, digit_str, 1);
    }

    return iban;
}

void capitalize_str(char *str) {
    if ((str[0] >= 'a') && (str[0] <= 'z'))
        str[0] -= 32;
}

int account_number(FILE *file_ptr, char *first_name, char *last_name,
                   BankAccount current_user_accounts_info[]) {

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