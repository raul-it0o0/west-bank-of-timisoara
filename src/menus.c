#include "menus.h"

void no_match_found_prompt(char *user_input) {

    clear_screen();
    wrong_credentials_prompt();

    scanf("%c", user_input);
    while ((*user_input != '1')&&(*user_input != '2')&&(*user_input != '3')) {
        printf("ERROR Invalid input. Please enter an option 1-3.\n");
        scanf("%c", user_input);
    }

}

int auth(char *first_name, char *last_name, BankAccount accounts_info[], int *accounts_found){

    clear_screen();

    // Open data file
    FILE *file_ptr = fopen("../data/data.csv", "r");

    if (file_ptr == NULL) {
        printf("Error opening CSV file\n");
        system("pause");
        return 3;
    }

    // Get number of accounts matching credentials
    *accounts_found = account_number(file_ptr, first_name, last_name, accounts_info);

    char user_input = 0;

    // If credentials don't match to an account in the DB
    if (*accounts_found == 0) {

        // Ask user for what to do next (Try again, Create new account or Exit)
        no_match_found_prompt(&user_input);

        // While user asks to 'TRY AGAIN' and no accounts were found
        while (user_input == '1' && *accounts_found == 0) {

            clear_screen();

            // Get credentials
            printf("Enter first name: ");
            scanf("%s", first_name);
            printf("Enter last name: ");
            scanf("%s", last_name);

            // Get number of accounts matching credentials
            *accounts_found = account_number(file_ptr, first_name, last_name, accounts_info);

            if (*accounts_found == 0)
                no_match_found_prompt(&user_input);
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

        clear_screen();
        options_menu(first_name);

        bool valid_input = true;
        int response;
        scanf("%d", &response);

        do {
            switch(response) {
                case 1:
                    valid_input = true;
                    // 'VIEW ACCOUNT INFORMATION'
                    view_accounts(first_name, user_accounts, accounts_found);
                    // Goal: Add options from this menu: edit account information, perform transaction,
                    // delete account, create new account and exit
                    // May be cleaner: Press any key to continue and return to the auth_success menu.
                    break;

                case 2:
                    valid_input = true;
                    // 'EDIT ACCOUNT INFORMATION'
                    printf("\nFeature not available yet.\n\n");

                    // Platform dependent (only on Windows)
                    system("pause");
                    // TODO: Use sleep() function for UNIX
                    break;

                case 3:
                    valid_input = true;
                    // 'PERFORM TRANSACTION'
                    printf("\nFeature not available yet.\n\n");

                    // Platform dependent (only on Windows)
                    system("pause");
                    // TODO: Use sleep() function for UNIX
                    break;

                case 4:
                    valid_input = true;
                    // 'DELETE ACCOUNT'
                    printf("\nFeature not available yet.\n\n");

                    // Platform dependent (only on Windows)
                    system("pause");
                    // TODO: Use sleep() function for UNIX
                    break;

                case 5:
                    valid_input = true;
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
                    scanf("%d", &response);
                    break;
            }

        } while(!valid_input);

    // Reprint menu until 'EXIT' is chosen
    } while(true);

}
