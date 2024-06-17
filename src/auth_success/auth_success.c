#include "auth_success.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

    do {

        welcome_message(first_name);
        options_menu();

        bool valid_input = true;
        // Goal: receive string input, clear buffer
        unsigned short int response;
        scanf("%hu", &response);

        do {
            switch(response) {
                case 1:
                    // 'VIEW ACCOUNT INFORMATION'
                    view_accounts(first_name, user_accounts, accounts_found);
                    // Goal: Add options from this menu: edit account information, perform transcation, delete account, create new account and exit
                    // May be cleaner: Press any key to continue and return to the auth_success menu.
                    break;

                case 2:
                    // 'EDIT ACCOUNT INFORMATION'
                    printf("\nFeature not available yet.\n");
                    break;
                
                case 3:
                    // 'PERFORM TRANSACTION'
                    printf("\nFeature not available yet.\n");
                    break;

                case 4:
                    // 'DELETE ACCOUNT'
                    printf("\nFeature not available yet.\n");
                    break;

                case 5:
                    // 'CREATE NEW ACCOUNT'
                    new_account(first_name, last_name, user_accounts, accounts_found, true);
                    break;

                case 6:
                    // 'EXIT'
                    return;

                default:
                    // Wrong input
                    valid_input = false;
                    printf("\nOption must be a number between 1 and 6. Try again.\n");
                    scanf("%hu", &response);
                    break;
            }

        } while(!valid_input);

    // Reprint menu until 'EXIT' is chosen
    } while(true);

}