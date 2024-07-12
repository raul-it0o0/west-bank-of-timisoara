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

int auth(User* session_user) {

    clear_screen();

    // Get number of accounts matching credentials
    get_matches(session_user);

    // If credentials don't match to an account in the DB
    if (arrlen(session_user->owned_bank_accounts) == 0) {

        // Ask user for what to do next (Try again, Create new account or Exit)
        char user_input = 0;
        no_match_found_prompt(&user_input);

        // While user asks to 'TRY AGAIN' and no accounts were found
        while (user_input == '1' && arrlen(session_user->owned_bank_accounts) == 0) {

            clear_screen();

            // Get credentials
            printf("Enter first name: ");
            scanf(" %s", session_user->first_name);
            printf("Enter last name: ");
            scanf(" %s", session_user->last_name);

            // Get number of accounts matching credentials
            get_matches(session_user);

            if (arrlen(session_user->owned_bank_accounts) == 0)
                no_match_found_prompt(&user_input);
        }

        switch (user_input) {
            case '2':
                // 'CREATE NEW ACCOUNT'
                return 1;

            case '3':
                // 'EXIT'
                return 2;

            default:
                // A match was eventually found after multiple tries
                return 0;
        }
    }

    else
        return 0;
}

void auth_success(User* session_user) {

    capitalize_str(session_user->first_name);
    capitalize_str(session_user->last_name);

    do {

        clear_screen();
        options_menu();

        bool valid_input = true;
        int response;
        scanf("%d", &response);

        do {
            switch(response) {
                case 1:
                    valid_input = true;
                    // 'VIEW ACCOUNT INFORMATION'
                    view_accounts(session_user);
                    break;

                case 2:
                    valid_input = true;
                    // 'EDIT ACCOUNT INFORMATION'
                    printf("\nFeature not available yet.\n\n");
                    pause();
                    break;

                case 3:
                    valid_input = true;
                    // 'PERFORM TRANSACTION'
                    printf("\nFeature not available yet.\n\n");
                    pause();
                    break;

                case 4:
                    valid_input = true;
                    // 'DELETE ACCOUNT'
                    printf("\nFeature not available yet.\n\n");
                    pause();
                    break;

                case 5:
                    valid_input = true;
                    // 'CREATE NEW ACCOUNT'
                    new_account(session_user, true);
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
