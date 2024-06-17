#include "account_operations.h"

void view_accounts(char *first_name, struct account *user_accounts, int *accounts_found) {

    printf("\n%s, you have %d account(s) at our bank:\n\n", first_name, *accounts_found);

    for (int i = 0; i < *accounts_found ; i++) {
        printf("Account %d\n", i+1);
        printf("IBAN: %s\n", user_accounts[i].iban);
        printf("Current Balance: %lu\n", user_accounts[i].balance);
        printf("Currency: %s\n\n", user_accounts[i].currency);
    }

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

        if (response != 'Y') {
            printf("Enter first name: ");
            scanf(" %s", new_first_name);

            printf("Enter last name: ");
            scanf(" %s", new_last_name);
        }
        else {
            strcpy(new_first_name, first_name);
            strcpy(new_last_name, last_name);
        }

        // Capitalize new entered credentials
        capitalize_str(new_first_name);
        capitalize_str(new_last_name);

    }
    else {
        strcpy(new_first_name, first_name);
        strcpy(new_last_name, last_name);
    }

    char *iban = generate_iban(new_first_name, new_last_name);

    char *currency;

    printf("\nChoose your currency for your new account.\nOur bank only supports the following currencies:\n\n");
    printf("RON [1]\n");
    printf("EUR [2]\n");
    printf("GBP [3]\n");
    printf("USD [4]\n");
    printf("BTC [5]\n\n");
    printf("Choose an option 1-5:\n");

    int input;
    scanf("%d", &input);
    bool valid_input = true;

    do {
        switch (input) {
            case 1:
                currency = "RON";
                valid_input = true;
                break;
            case 2:
                currency = "EUR";
                valid_input = true;
                break;
            case 3:
                currency = "GBP";
                valid_input = true;
                break;
            case 4:
                currency = "USD";
                valid_input = true;
                break;
            case 5:
                currency = "BTC";
                valid_input = true;
                break;

            default:
                valid_input = false;
                printf("\n Please enter a valid option 1-5.\n");
                scanf("%d", &input);
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