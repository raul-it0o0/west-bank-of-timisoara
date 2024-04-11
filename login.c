#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int maxLineSize = 1024;
const int user_account_limitation = 5;

typedef struct account_struct
{
    char iban[15];
    char currency[3];
    unsigned long int balance;
    unsigned int line_in_file;

};

int search_store_credentials(FILE *file_ptr, char *first_name, char *last_name, struct account_struct accounts[]) {
    
    char line_reader[maxLineSize] = {};
    bool account_found = false;

    fgets(line_reader,maxLineSize,file_ptr);
    // stores header row in line_reader
    // every call of fgets reads a new row (max 1024 chars or until \n)

    int line_counter = 1, account_counter = 0;

    while ((fgets(line_reader,maxLineSize,file_ptr) != NULL) && (account_counter < user_account_limitation)){

        char *row_entry = strtok(line_reader, ","); // get first column (first_name)
        // future: modify the name that was read from the csv in order to not be case-sensitive -> strcasecmp?

        if (strcmp(row_entry, first_name) == 0) {
            printf("LOG: first_name MATCH FOUND ON LINE %d", line_counter);

            row_entry = strtok(NULL, ",");
            if (strcmp(row_entry, last_name) == 0) {
                printf("LOG: COMPLETE MATCH FOUND ONE LINE %d", line_counter);

                strcpy(accounts[account_counter].iban, strtok(NULL, ","));
                strcpy(accounts[account_counter].currency, strtok(NULL, ","));
                accounts[account_counter].balance = (unsigned long int)strtok(NULL, ",");
                accounts[account_counter].line_in_file = line_counter;

                account_counter++;
            }
        }

        else {
            printf("NO MATCH FOUND ON LINE %d", line_counter);
        }
            
        
        line_counter++;
    }

    return account_counter;

}

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
        return printf("\nERROR: WRONG NUMBER OF ARGUMENTS\nPASS 2 ARGUMENTS AS FOLLOWS:\n./login [name] [surname]\n");
    }
    
    char *userName = argv[1], *userSurname = argv[2];
    
    // login and search for name, surname
    FILE* fPtr = fopen("../data.csv","r");

    if (fPtr == NULL) {
        printf("ERROR: DATA CSV FILE NOT FOUND");
        return 1;
    }
    
    if (search_store_credentials(fPtr, userName, userSurname) > 0) {
        create_temp_csv(acco)
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