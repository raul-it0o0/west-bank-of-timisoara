#include "auth_success.h"
#include <stdlib.h>
#include <stdio.h>

void view_accounts(char *first_name, struct account *user_accounts, const int *accounts_found) {
    printf("\n%s, you have %d account(s) at our bank:\n\n", first_name, *accounts_found);

    for (int i = 0; i < *accounts_found ; i++) {
        printf("Account %d\n", i+1);
        printf("IBAN: %s\n", user_accounts[i].iban);
        printf("Current Balance: %lu\n", user_accounts[i].balance);
        printf("Currency: %s\n", user_accounts[i].currency);
    }

    printf("\n");

}

void auth_success(char *first_name, char *last_name, struct account *user_accounts, int *accounts_found) {

    welcome_message(first_name);

    char response;

    options_menu_and_parse(&response);

    while (response != '6') {
        if (response == '1') {
            view_accounts(first_name, user_accounts, accounts_found);
            return;
        }
//        options_menu_and_parse(&response);
    }

//    if (response == 1) {
//        view_accounts()
//    }


}