#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int main(int argc, char *argv[]){

    // Seed random number generator used for IBAN generation
    time_t t;
    srand((unsigned long long) (&t));

    // Validate received command line arguments
    if (argc != 3) {
        printf("Error parsing command line arguments: Pass 2 arguments as follows:\n");
        printf("./login [FIRST NAME] [LAST NAME]\n\n");
        printf("Press any key to continue.");
        return getchar();
    }

    char *first_name = argv[1], *last_name = argv[2];

    // Goal: remove user account limitation using C dynamic arrays (vectors)
    BankAccount *user_accounts = calloc(USER_ACCOUNT_LIMITATION, sizeof(BankAccount));
    int accounts_found = 0;

    switch(auth(first_name, last_name, user_accounts, &accounts_found)) {
        case 0:
            // Found 1 credential match
            auth_success(first_name, last_name, user_accounts, &accounts_found);
            break;

        case 1:
            // Found multiple credential matches
            auth_success(first_name, last_name, user_accounts, &accounts_found);
            break;

        case 2:
            // No matches found, user wants to create a new account
            new_account(first_name, last_name, user_accounts, &accounts_found, false);
            auth_success(first_name, last_name, user_accounts, &accounts_found);
            break;

        default:
            // No matches found, user requested exit / Error
            break;
        }

    free(user_accounts);

    return 0;

}