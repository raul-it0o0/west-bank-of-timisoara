#ifndef PROGRAMMING_PROJECT_AUTH_H
#define PROGRAMMING_PROJECT_AUTH_H

struct account_info {
    char iban[15];
    char currency[3];
    unsigned long int balance;
    unsigned int line_in_file;
};

int search_store_credentials(FILE *file_ptr,
                             char *first_name,
                             char *last_name,
                             struct account_info *current_user_account_info,
                             struct account_info current_user_accounts_info[]);

#endif //PROGRAMMING_PROJECT_AUTH_H
