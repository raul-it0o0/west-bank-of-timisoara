#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int main(int argc, char *argv[]){

    // Seed random number generator used for IBAN generation
    time_t t;
    srand((unsigned long long) (&t));

    // Validate received command line arguments
    if (argc != 3) {
        clear_screen();
        printf("Error parsing command line arguments: Pass 2 arguments as follows:\n");
        printf("./login [FIRST NAME] [LAST NAME]\n\n");
        pause();
    }

    char* first_name = argv[1];
    char* last_name = argv[2];
    User* session_user = user_init(first_name, last_name);

    switch(auth(session_user)) {
        case 0:
            // Found match
            auth_success(session_user);
            break;

        case 1:
            // No matches found, user wants to create a new account
            new_account(session_user, false);
            auth_success(session_user);
            break;

        default:
            // No matches found, user requested exit / Error
            break;
        }

    user_destroy(session_user);

    return 0;

}