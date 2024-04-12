#include <stdio.h>
#include "user_inputs.h"

void options_menu_and_parse(char *response) {

    printf("\nChoose an option 1-4.\n");
    printf("VIEW ACCOUNT INFORMATION [1]\n");
    printf("EDIT ACCOUNT INFORMATION [2]\n");
    printf("PERFORM TRANSACTION [3]\n");
    printf("DELETE ACCOUNT [4]\n");
    printf("CREATE NEW ACCOUNT [5]\n");
    printf("EXIT [6]\n");
    printf("\n");
    fflush(stdout);

    scanf("%c", response);
    while ((*response != '1') && (*response != '2') && (*response != '3') && (*response != '4') && (*response != '5') && (response != '6')) { // better validation condition
        printf("\nOption must be a number between 1 and 4. Try again.\n");
        scanf("%c", response);
    }

}

void welcome_message(char *first_name){
    // center in terminal
    printf("\nWEST BANK OF TIMISOARA\n");
    printf("All rights reserved.\n");
    printf("Welcome %s! What would you like to do today?\n", first_name);

}