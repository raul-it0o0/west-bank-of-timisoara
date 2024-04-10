#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int maxLineSize = 1024;

char *menu_print_and_parse(char *response){
    
    printf("\nChoose an option 1-4.\n");
    printf("VIEW ACCOUNT INFORMATION [1]\n");
    printf("EDIT ACCOUNT INFORMATION [2]\n");
    printf("PERFORM TRANSACTION [3]\n");
    printf("DELETE ACCOUNT [4]\n");
    printf("\n");

    scanf("%c", response);
    while ((*response < (char)1) || (*response > (char)4)) {
        printf("\nOption must be a number between 1 and 4. Try again.\n");
        scanf("%c", response);
    }

    return response;
}

int main(int argc, char *argv[]){

    if (argc != 3) {
        return printf("\nERROR: NOT ENOUGH ARGUMENTS\nPASS 2 ARGUMENTS AS FOLLOWS:\n./login [name] [surname]\n");
    }
    
    char *userName = argv[1], *userSurname = argv[2];
    
    // login and search for name, surname
    FILE* fPtr = fopen("../data.csv","r");

    if (fPtr == NULL) {
        printf("ERROR: DATA FILE NOT FOUND");
        return 1;
    }
    
    char rowStr[maxLineSize] = {};
    bool account_found = false;

    fgets(rowStr,maxLineSize,fPtr);
    // stores header row in rowStr
    // every call of fgets reads a new row (max 1024 chars or until \n)

    unsigned int line_counter = 1;
    while((fgets(rowStr,maxLineSize,fPtr) != NULL)&&(!account_found)){
        // get name username

        char *row_entry = strtok(rowStr, ",");
        // future: modify the name that was read from the csv in order to not be case-sensitive -> strcasecmp?
        if (strcmp(row_entry,userName) != 0) {
            printf("NOT IN LINE %d\n", line_counter);
        }
        else /* the two strings are equal */{
            printf("NAME MATCHES IN LINE %d! NOW SEARCHING FOR SURNAME MATCH IN SAME LINE\n", line_counter);
            row_entry = strtok(NULL, ",");

            if (strcmp(row_entry,userSurname) == 0) {
                printf("SURNAME MATCHES IN LINE %d!\n", line_counter);
                account_found = true;
            }
        }
        
        line_counter++;

    }

    if (account_found) {
        printf("Account found.\n");

        // center in terminal
        printf("~~~WEST BANK OF TIMISOARA~~~\n");
        printf("© 2024 West Bank of Timisoara\n"); 

        printf("Welcome %s! What would you like to do today?\n", argv[1]); // add name from csv file
        // char user_input_response = 0;

        // menu_print();
    }

    else {
        printf("Account not found.\n");
    }

    fclose(fPtr);

    return 0;
}