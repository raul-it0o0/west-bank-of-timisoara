#ifndef PROGRAMMING_PROJECT_AUTH_H
#define PROGRAMMING_PROJECT_AUTH_H

#define USER_ACCOUNT_LIMITATION 5
#define MAX_CHARS_PER_LINE 1024
#include <stdio.h>

typedef struct account {
    char iban[16];
    char currency[3];
    unsigned long int balance;
}BankAccount;

int search_store_credentials(FILE *file_ptr,
                             char *first_name,
                             char *last_name,
                             struct account current_user_accounts_info[]);

void no_accounts_found_request_input(char *user_input);

int auth(char *first_name,
         char *last_name,
         BankAccount accounts_info[],
         int *accounts_found);

#endif //PROGRAMMING_PROJECT_AUTH_H
