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

    time_t t;
    srand((unsigned long long) (&t));

    if (argc != 3)
        return printf("\nERROR: WRONG NUMBER OF ARGUMENTS\nPASS 2 ARGUMENTS AS FOLLOWS:\n./login [name] [surname]\n");
    
    char *first_name = argv[1], *last_name = argv[2];

    struct account *user_accounts = calloc(USER_ACCOUNT_LIMITATION, sizeof(struct account));
    int accounts_found = 0;
    char user_response = auth(first_name, last_name, user_accounts, &accounts_found);

    if (user_response == '0') {
//        printf("\nLog: FOUND 1 MATCHING ACCOUNT TO USER\n");
        auth_success(first_name, last_name, user_accounts, &accounts_found);
        return 0;
    }

    else if (user_response == '1') {
//        printf("\nLog: MULTIPLE ACCOUNTS FOUND FOR USER\n");
        auth_success(first_name, last_name, user_accounts, &accounts_found);
        return 0;
    }

    else if (user_response == '2') {
//        printf("\nLog: NO MATCHES FOUND. USER WANTS TO CREATE A NEW ACCOUNT\n");
        new_account(first_name, last_name, user_accounts, &accounts_found, false);
        auth_success(first_name, last_name, user_accounts, &accounts_found);
        return 0;
    }

    else if (user_response == '3') {
//        printf("\nLog: NO MATCHES FOUND. USER REQUESTED EXIT / FATAL ERROR\n");
        free(user_accounts);
        return 0;
    }

    return 0;
}