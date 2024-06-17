#include "menus.h"

void no_accounts_found_request_input(char *user_input) {

    wrong_credentials_prompt();

    scanf("%c", user_input);
    while ((*user_input != '1')&&(*user_input != '2')&&(*user_input != '3')) {
        printf("ERROR Invalid input. Please enter an option 1-3.\n");
        scanf("%c", user_input);
    }

}

int auth(char *first_name, char *last_name, BankAccount accounts_info[], int *accounts_found){

    // Open data file
    FILE *file_ptr = fopen("../data/data.csv", "r");

    if (file_ptr == NULL) {
        printf("Error opening CSV file");
        return 3;
    }

    // Get number of accounts matching credentials
    *accounts_found = account_number(file_ptr, first_name, last_name, accounts_info);

    char user_input = 0;

    // If credentials don't match to an account in the DB
    if (*accounts_found == 0) {

        // Ask user for what to do next (Try again, Create new account or Exit)
        no_accounts_found_request_input(&user_input);

        // While user asks to 'TRY AGAIN' and no accounts were found
        while (user_input == '1' && *accounts_found == 0) {

            // Get credentials
            printf("Enter first name: ");
            scanf("%s", first_name);
            printf("Enter last name: ");
            scanf("%s", last_name);

            // Get number of accounts matching credentials
            *accounts_found = account_number(file_ptr, first_name, last_name, accounts_info);

            if (*accounts_found == 0)
                no_accounts_found_request_input(&user_input);
        }

        if (user_input == '2') {
            // 'CREATE NEW ACCOUNT'
            return 2;
        }

        if (user_input == '3') {
            // 'EXIT'
            return 3;
        }

        if (*accounts_found == 1) {
            // 1 account matching credentials after initial wrong input(s)
            return 0;
        }

        if (*accounts_found > 1) {
            // Multiple accounts matching credentials after initial wrong input(s)
            return 1;
        }
    }

    else {

        if (*accounts_found == 1)
            // 1 account matching credentials
            return 0;

        else /* if (*accounts_found > 1) */
            return 1;

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
