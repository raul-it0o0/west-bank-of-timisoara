#include "print.h"

void clear_screen() {
    fflush(stdout);
    system("CLS");
}

void options_menu(char *first_name) {
    printf("\nWEST BANK OF TIMISOARA\n");
    printf("All rights reserved.\n");
    printf("Welcome %s! What would you like to do today?\n\n", first_name);

    printf("Choose an option 1-6.\n");
    printf("VIEW ACCOUNT INFORMATION [1]\n");
    printf("EDIT ACCOUNT INFORMATION [2]\n");
    printf("PERFORM TRANSACTION [3]\n");
    printf("DELETE ACCOUNT [4]\n");
    printf("CREATE NEW ACCOUNT [5]\n");
    printf("EXIT [6]\n\n");
}

void wrong_credentials_prompt() {
    printf("\nNo accounts found with the provided information.\n");
    printf("Please enter an option 1-3:\n\n");
    printf("TRY AGAIN [1]\n");
    printf("CREATE NEW ACCOUNT [2]\n");
    printf("EXIT [3]\n\n");
}