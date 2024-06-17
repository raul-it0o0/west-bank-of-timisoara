#include "new_account.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Eliminate the need for this function
char *char_to_str(char c) {
    char *str = calloc(2, sizeof(char));
    str[0] = c;

    return str;
}

char *generate_iban(char *first_name, char *last_name){
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

void new_account(char *first_name, char *last_name, struct account *user_accounts, int *accounts_found, bool authenticated) {

    if (*accounts_found == USER_ACCOUNT_LIMITATION) {
        printf("%s, you have %d accounts at our bank.\nYou cannot create any more accounts at our bank.\n", first_name, *accounts_found);
        return;
    }

    unsigned char response = 0;
    char *new_first_name = calloc(MAX_CHARS_FOR_NAME, sizeof(char));
    char *new_last_name = calloc(MAX_CHARS_FOR_NAME, sizeof(char));

    if(!authenticated) {
        printf("\nYou last entered the following credentials:\n");
        printf("First Name: %s\n", first_name);
        printf("Last Name: %s\n", last_name);

        printf("\nWould you like to keep this data for the new account creation [Y] or input new data [N]? [Y/N]\n");
        scanf(" %c", &response);

        if (response == 'Y') {
            strcpy(new_first_name, first_name);
            strcpy(new_last_name, last_name);
        }
        else {
            printf("Enter first name: ");
            scanf(" %s", new_first_name);

            printf("Enter last name: ");
            scanf(" %s", new_last_name);
        }

    }

    // Capitalize entered credentials
    capitalize_str(new_first_name);
    capitalize_str(new_last_name);

    char *iban = generate_iban(new_first_name, new_last_name);

    char *currency = malloc(3 * sizeof(char) + 1);

    printf("\nChoose your currency for your new account.\nOur bank only supports the following currencies:\n\n");
    printf("RON [1]\n");
    printf("EUR [2]\n");
    printf("GBP [3]\n");
    printf("USD [4]\n");
    printf("BTC [5]\n\n");
    printf("Choose an option 1-5:\n");

    scanf(" %c", &response);
    bool valid_input = true;

    do {
        switch (response) {
            case '1':
                currency = "RON";
                valid_input = true;
                break;
            case '2':
                currency = "EUR";
                valid_input = true;
                break;
            case '3':
                currency = "GBP";
                valid_input = true;
                break;
            case '4':
                currency = "USD";
                valid_input = true;
                break;
            case '5':
                currency = "BTC";
                valid_input = true;
                break;

            default:
                valid_input = false;
                printf("\n Please enter a valid option 1-5.\n");
                scanf(" %c", &response);
                break;
        }

    } while(!valid_input);

    // Append new account information to the data.csv file
    FILE *file_ptr = fopen("../data/data.csv", "a");

    fprintf(file_ptr, "\n%s,%s,%s,%s,%d", new_first_name, new_last_name, iban, currency, 0);

    fclose(file_ptr);

    // Add the new account information to user_accounts array
    strcpy(user_accounts[*accounts_found].iban, iban);
    strcpy(user_accounts[*accounts_found].currency, currency);
    user_accounts[*accounts_found].balance = 0;
    (*accounts_found)++;

    free(new_first_name);
    free(new_last_name);
    free(iban);

    printf("\nYour new account has been created!\nYour balance is currently 0, so perform a transaction or edit account to add funds\n");

}