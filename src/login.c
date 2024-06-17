#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../src/auth/auth.h"
#include "../src/user_inputs/user_inputs.h"
#include "../src/auth_success/auth_success.h"
#include "../src/new_account/new_account.h"

int main(int argc, char *argv[]){

    // Seed random number generator used for IBAN generation
    time_t t;
    srand((unsigned long long) (&t));

    // Validate received command line arguments
    if (argc != 3) {
        printf("\nERROR: WRONG NUMBER OF ARGUMENTS\nPASS 2 ARGUMENTS AS FOLLOWS:\n./login [name] "
                      "[surname]\n\nPress any key to continue.");
        return getchar();
    }

    char *first_name = argv[1], *last_name = argv[2];

    BankAccount *user_accounts = calloc(USER_ACCOUNT_LIMITATION, sizeof(BankAccount));
    // Goal: remove user account limitation using C dynamic arrays (vectors)

    int accounts_found = 0;

    switch(auth(first_name, last_name, user_accounts, &accounts_found)) {
        case 0:
            // Found 1 credential match
            auth_success(first_name, last_name, user_accounts, &accounts_found);

        case 1:
            // Found multiple credential matches
            auth_success(first_name, last_name, user_accounts, &accounts_found);

        case 2:
            // No matches found, user wants to create a new account
            new_account(first_name, last_name, user_accounts, &accounts_found, false);
            auth_success(first_name, last_name, user_accounts, &accounts_found);

        default:
            // No matches found, user requested exit / Error
            free(user_accounts);
        }

    return 0;

}