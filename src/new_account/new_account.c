#include "new_account.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define RAND_MAX 9


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

    if(!authenticated) {
        printf("\nYou last entered the following credentials:\n");
        printf("First Name: %s\n", first_name);
        printf("Last Name: %s\n", last_name);

        printf("\nWould you like to keep this data for the new account creation [Y] or input new data [N]?\n[Y\\N]\n");
        scanf(" %c", &response);

        while((response != 'Y')&&(response != 'N')){
            printf("\nPlease enter a valid option.\n");
            printf("Yes [Y]\nNo [N]\n\n");
            scanf(" %c", &response);
        }
    }

    char *new_first_name = calloc(MAX_CHARS_FOR_NAME, sizeof(char));
    char *new_last_name = calloc(MAX_CHARS_FOR_NAME, sizeof(char));

    if (response == 'N') {
        printf("Enter first name: ");
        scanf(" %s", new_first_name);
        printf("Enter last name: ");
        scanf(" %s", new_last_name);
    }

    else {
        strcpy(new_first_name, first_name);
        strcpy(new_last_name, last_name);
    }

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

    while ((response != '1') && (response != '2') && (response != '3') && (response != '4') && (response != '5')) {
        printf("\n Please enter a valid option 1-5.\n");
        scanf(" %c", &response);
    }

    switch (response) {
        case '1':
            currency = "RON";
            break;
        case '2':
            currency = "EUR";
            break;
        case '3':
            currency = "GBP";
            break;
        case '4':
            currency = "USD";
            break;
        case '5':
            currency = "BTC";
            break;
        default:
            break;
    }

    FILE *file_ptr = fopen("../data/data.csv", "a");

    fprintf(file_ptr, "\n%s,%s,%s,%s,%d", new_first_name, new_last_name, iban, currency, 0);

    fclose(file_ptr);

    strcpy(user_accounts[*accounts_found].iban, iban);
    strcpy(user_accounts[*accounts_found].currency, currency);
    user_accounts[*accounts_found].balance = 0;
    (*accounts_found)++;

    free(new_first_name);
    free(new_last_name);
    free(iban);
//    free(currency);

    printf("\nYour new account has been created!\nYour balance is currently 0, so perform a transaction or edit account to add funds\n");

    // return

}