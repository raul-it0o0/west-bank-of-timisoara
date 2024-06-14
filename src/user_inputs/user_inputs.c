#include <stdio.h>
#include "user_inputs.h"

void options_menu() {

    printf("\nChoose an option 1-4.\n");
    printf("VIEW ACCOUNT INFORMATION [1]\n");
    printf("EDIT ACCOUNT INFORMATION [2]\n");
    printf("PERFORM TRANSACTION [3]\n");
    printf("DELETE ACCOUNT [4]\n");
    printf("CREATE NEW ACCOUNT [5]\n");
    printf("EXIT [6]\n");
    printf("\n");

}

void welcome_message(char *first_name){
    printf("\nWEST BANK OF TIMISOARA\n");
    printf("All rights reserved.\n");
    printf("Welcome %s! What would you like to do today?\n", first_name);

}