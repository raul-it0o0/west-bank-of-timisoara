#include "auth_success.h"
#include <stdlib.h>
#include <stdio.h>
#include "../new_account/new_account.h"
#include "../auth/auth.h"

void view_accounts(char *first_name, struct account *user_accounts, int *accounts_found) {
    printf("\n%s, you have %d account(s) at our bank:\n\n", first_name, *accounts_found);

    for (int i = 0; i < *accounts_found ; i++) {
        printf("Account %d\n", i+1);
        printf("IBAN: %s\n", user_accounts[i].iban);
        printf("Current Balance: %lu\n", user_accounts[i].balance);
        printf("Currency: %s\n\n", user_accounts[i].currency);
    }

}

void auth_success(char *first_name, char *last_name, struct account *user_accounts, int *accounts_found) {

    welcome_message(first_name);
    options_menu();

    unsigned short int response;
    scanf("%hu", &response);

    while ((response != 1) && (response != 2) && (response != 3) && (response != 4) && (response != 5) && (response != 6)) { // better validation condition
        printf("\nOption must be a number between 1 and 6. Try again.\n");
        scanf(" %hu", &response);
    }

    while (response != 6) {
        if (response == 1) {
            view_accounts(first_name, user_accounts, accounts_found);
        }

        if (response == 2) {
            printf("\nFeature not available yet.\n");
        }

        if (response == 3) {
            printf("\nFeature not available yet.\n");
        }

        if (response == 4) {
            printf("\nFeature not available yet.\n");
        }

        if (response == 5) {
            new_account(first_name, last_name, user_accounts, accounts_found, true);
        }

        options_menu();
        scanf("%hu", &response);

        while ((response != 1) && (response != 2) && (response != 3) && (response != 4) && (response != 5) && (response != 6)) { // better validation condition
            printf("\nOption must be a number between 1 and 6. Try again.\n");
            scanf(" %hu", &response);
        }
    }

    // exit while loop means user_input = 6
    // return, exit auth_success

}