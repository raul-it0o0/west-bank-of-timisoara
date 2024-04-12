#ifndef PROGRAMMING_PROJECT_AUTH_H
#define PROGRAMMING_PROJECT_AUTH_H

#define USER_ACCOUNT_LIMITATION 5
#define MAX_CHARS_PER_LINE 1024

#include <stdio.h>

struct account {
    char iban[15];
    char currency[3];
    unsigned long int balance;
    unsigned int line_in_file;
};

int search_store_credentials(FILE *file_ptr,
                             char *first_name,
                             char *last_name,
                             struct account *current_user_account,
                             struct account current_user_accounts_info[]);

void no_accounts_found_request_input(char *user_input);

void store_current_info_in_struct_array(struct account *single_account,
                                        struct account all_accounts[],
                                        int index);

char auth(char *first_name, 
          char *last_name,
          struct account *singular_account_info,
          struct account accounts_info[],
          int *accounts_found);

#endif //PROGRAMMING_PROJECT_AUTH_H
