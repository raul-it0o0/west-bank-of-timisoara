#include "print.h"

void clear_screen() {
    fflush(stdout);
    system("CLS");
}

void options_menu() {
    printf("Welcome! What would you like to do today?\n\n");

    printf("Choose an option 1-6.\n");
    printf("[1] VIEW ACCOUNT INFORMATION\n");
    printf("[2] EDIT ACCOUNT INFORMATION\n");
    printf("[3] PERFORM TRANSACTION\n");
    printf("[4] DELETE ACCOUNT\n");
    printf("[5] CREATE NEW ACCOUNT\n");
    printf("[6] EXIT\n\n");
}

void wrong_credentials_prompt() {
    printf("No accounts found with the provided information.\n");
    printf("Please enter an option 1-3:\n\n");
    printf("[1] TRY AGAIN\n");
    printf("[2] CREATE NEW ACCOUNT\n");
    printf("[3] EXIT\n\n");
}

void pause() {
    system("pause");
    // TODO: UNIX support (sleep() command)
}