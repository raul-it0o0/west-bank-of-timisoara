#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STB_DS_IMPLEMENTATION
// Required for using the stb_ds library (dynamic arrays)

#include "helpers.h"


void generate_iban(const char *first_name, const char *last_name, char *iban) {

    iban[0] = first_name[0];
    iban[1] = last_name[0];

    for (int i = 2; i < 15; i++) {
        sprintf(&iban[i], "%d", (rand()%10));
    }

    while(!unique_iban(iban)) {
        // Generate a new 14-digit sequence for the IBAN
        for (int i = 2; i < 15; i++) {
            sprintf(&iban[i], "%d", (rand()%10));
        }
    }

}

bool unique_iban(const char* iban) {

    FILE* file_ptr = fopen("../data/data.csv", "r");
    if (file_ptr == NULL) {
        printf("Error opening CSV file\n");
        printf("Cannot check IBAN uniqueness, assuming is unique\n");
        pause();
        return true;
    }

    char* row_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));
    char* iban_entry = calloc(16, sizeof(char));

    fgets(row_reader, MAX_CHARS_PER_LINE, file_ptr);
    // Stores (and ignores, i.e. does not process) header row in row_reader

    while (fgets(row_reader,MAX_CHARS_PER_LINE,file_ptr) != NULL) {
        memset(iban_entry, '\0', 16);

        // Skip first and second columns
        strtok(row_reader,",");
        strtok(NULL,",");

        strcpy(iban_entry, strtok(NULL, ","));
        if (strcmp(iban_entry, iban) == 0) {
            free(iban_entry);
            free(row_reader);
            return false;
        }
    }

    free(iban_entry);
    free(row_reader);
    fclose(file_ptr);
    return true;

}

void capitalize_str(char *str) {
    if ((str[0] >= 'a') && (str[0] <= 'z'))
        str[0] -= 32;
}

BankAccount* bank_account_init(int currency_code, const char *first_name, const char *last_name) {

    BankAccount* this = malloc(sizeof(BankAccount));
    if (this == NULL) {
        printf("Allocation failed\n");
        pause();
        return NULL;
    }

    generate_iban(first_name, last_name, this->iban);

    this->balance = 0;

    switch(currency_code) {
        case 1:
            strcpy(this->currency, "RON");
            break;

        case 2:
            strcpy(this->currency, "EUR");
            break;

        case 3:
            strcpy(this->currency, "GBP");
            break;

        case 4:
            strcpy(this->currency, "USD");
            break;

        case 5:
            strcpy(this->currency, "BTC");
            break;

        default:
            break;
    }

    return this;

}

void bank_account_destroy(BankAccount* this) {

    this->balance = 0;

    memset(this->iban, '\0', sizeof(this->iban));
    memset(this->currency, '\0', sizeof(this->currency));

    free(this);
    this = NULL;

}

User* user_init(const char *first_name, const char *last_name) {

    User* this = malloc(sizeof(User));

    this->first_name = calloc(MAX_CHARS_PER_LINE, sizeof(char));
    this->last_name = calloc(MAX_CHARS_PER_LINE, sizeof(char));

    strcpy(this->first_name, first_name);
    strcpy(this->last_name, last_name);

    this->owned_bank_accounts = NULL;

    return this;
}

void user_destroy(User* this) {

    int number_of_accounts = arrlen(this->owned_bank_accounts);
    for (int i = 0; i < number_of_accounts; i++) {
        bank_account_destroy(this->owned_bank_accounts[i]);
    }

    // if not NULL
    if (this->owned_bank_accounts) {
        arrfree(this->owned_bank_accounts);
        this->owned_bank_accounts = NULL;
    }

    // TODO: Remove
    printf("Freed array\n");

    free(this);
    this = NULL;

    // TODO: Remove
    printf("Freed user\n");

}

void get_matches(User* user) {

    FILE* file_ptr = fopen("../data/data.csv", "r");

    if (file_ptr == NULL) {
        printf("Error opening CSV file\n");
        pause();
        return;
    }

    char* row_reader = calloc(MAX_CHARS_PER_LINE, sizeof(char));
    char* row_entry = calloc(MAX_CHARS_PER_LINE, sizeof(char));

    fgets(row_reader, MAX_CHARS_PER_LINE, file_ptr);
    // Stores (and ignores, i.e. does not process) header row in row_reader
    // Every call of fgets reads a new row (max 1024 chars or until \n)

    while (fgets(row_reader,MAX_CHARS_PER_LINE,file_ptr) != NULL) {

        // Get first column (first name)
        memset(row_entry, '\0', MAX_CHARS_PER_LINE);
        strcpy(row_entry, strtok(row_reader, ","));

        // If entry matches first name
        if (strcasecmp(row_entry, user->first_name) == 0) {

            // Get second column (last name)
            memset(row_entry, '\0', MAX_CHARS_PER_LINE);
            strcpy(row_entry, strtok(NULL, ","));

            // If entry matches last name -> Match found
            if (strcasecmp(row_entry, user->last_name) == 0) {

                BankAccount* account = malloc(sizeof(BankAccount));

                // Store IBAN (length: 16)
                strcpy(account->iban, strtok(NULL, ","));

                // Store currency (length: 3)
                strcpy(account->currency, strtok(NULL, ","));

                // Convert string read into float number and store as balance
                account->balance = strtold(strtok(NULL, ","), NULL);
                // Shouldn't the delimiter be "\n" for the last column?

                // Link this account to the user
                arrput(user->owned_bank_accounts, account);
            }
        }
    }

    fclose(file_ptr);

    free(row_reader);
    free(row_entry);

}