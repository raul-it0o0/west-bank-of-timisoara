#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int maxLineSize = 1024;
const int user_account_limitation = 5;

struct account_struct
{
    char iban[15];
    char currency[3];
    unsigned long int balance;
    unsigned int line_in_file;

};

char *menu_print_and_parse(char *response){

    printf("\nChoose an option 1-4.\n");
    printf("VIEW ACCOUNT INFORMATION [1]\n");
    printf("EDIT ACCOUNT INFORMATION [2]\n");
    printf("PERFORM TRANSACTION [3]\n");
    printf("DELETE ACCOUNT [4]\n");
    printf("CREATE NEW ACCOUNT [5]\n");
    printf("\n");
    fflush(stdout);

    scanf("%c", response);
    while ((*response < (char)1) || (*response > (char)4)) { // better validation condition
        printf("\nOption must be a number between 1 and 4. Try again.\n");
        fflush(stdout);
        scanf("%c", response);
    }

    return response;
}

void create_temp_csv(struct account_struct found_accounts[], int accounts_found) {

    FILE *temp_csv = fopen("temp.csv", "w");

    fprintf(temp_csv, "IBAN,Currency,Balance,LineInFile\n");

    for (int i=0; i < accounts_found; i++) {
        fprintf(temp_csv,"%s,%s,%lu,%u",found_accounts[i].iban,found_accounts[i].currency,found_accounts[i].balance,found_accounts[i].line_in_file);
    }

    fclose(temp_csv);
}

void state_found_accounts(char *user_input, char *first_name, char *last_name, struct account_struct accounts[], int accounts_found) {
    printf("LOG: >0 ACCOUNTS MATCHED, CREATING TEMP CSV\n");
    fflush(stdout);
    create_temp_csv(accounts, accounts_found);

    // logged in state function in a separate file?

    // center in terminal
    printf("~~~WEST BANK OF TIMISOARA~~~\n");
    printf("All rights reserved.\n");

    printf("\nWelcome %s! What would you like to do today?\n", first_name); // add name from csv file
    user_input = menu_print_and_parse(user_input);

    if (user_input == '1')

}

void state_no_accounts_found(char *user_input, FILE *file_ptr, char *first_name, char *last_name, struct account_struct accounts[]) {
    // no accounts found, try again OR create new account
    printf("\nNo accounts matching %s %s.\nSelect an option.");
    printf("TRY AGAIN [1]\n");
    printf("CREATE NEW ACCOUNT [2]\n");
    printf("EXIT [3]\n");

    scanf("%s", user_input);

    while ((user_input != (char*)1) || (user_input != (char*)2) || (user_input != (char*)3)) {
        printf("\nOption must be a number between 1 and 4. Try again.\n");
        fflush(stdout);
        scanf("%c", user_input);
    }

    if (user_input == (char*)1) {
        printf("Enter first name: ");
        scanf("%s", first_name);
        printf("Enter last name: ");
        scanf("%s", last_name);
        int accounts_found = 0;
        accounts_found = search_store_credentials(file_ptr, first_name, last_name, accounts);

        if (accounts_found > 0) {
            printf("")
        }


    }
}


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



int main(int argc, char *argv[]){

    if (argc != 3) {
        return printf("\nERROR: WRONG NUMBER OF ARGUMENTS\nPASS 2 ARGUMENTS AS FOLLOWS:\n./login [name] [surname]\n");
    }
    
    char *userName = argv[1], *userSurname = argv[2];
    
    // login and search for name, surname
    FILE* fPtr = fopen("../data.csv","r");

    if (fPtr == NULL) {
        printf("ERROR: DATA CSV FILE NOT FOUND");
        fflush(stdout);
        return 1;
    }

    struct account_struct temporary_info_storage[user_account_limitation];
    int accounts_found = 0;
    accounts_found = search_store_credentials(fPtr, userName, userSurname, temporary_info_storage);
    char user_input = 0;

    if (accounts_found > 0) {

    }
    else {
        // no accounts found, try again OR create new account
        printf("\nNo accounts matching %s %s.\nSelect an option.");
        printf("TRY AGAIN [1]\n");
        printf("CREATE NEW ACCOUNT [2]\n");
        printf("EXIT [3]\n");

        scanf("%c", &user_input);

        while ((user_input != 1)||(user_input != 2)||(user_input != 3)) {
            printf("\nOption must be a number between 1 and 4. Try again.\n");
            fflush(stdout);
            scanf("%c", &user_input);
        }

        if (user_input == 1) {
            printf("Enter first name: ");
            scanf("%s", userName);
            printf("Enter last name: ");
            scanf("%s", userSurname);

        }
    }


        // center in terminal
        printf("~~~WEST BANK OF TIMISOARA~~~\n");
        printf("© 2024 West Bank of Timisoara\n"); 

        printf("Welcome %s! What would you like to do today?\n", argv[1]); // add name from csv file
        // char user_input_response = 0;

        // menu_print();
    }

    else {
        printf("Account not found.\n");
        fflush(stdout);
    }

    fclose(fPtr);

    return 0;
}