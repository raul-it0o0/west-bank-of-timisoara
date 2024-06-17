#ifndef PROGRAMMING_PROJECT_AUTH_H
#define PROGRAMMING_PROJECT_AUTH_H
#define USER_ACCOUNT_LIMITATION 5
#define MAX_CHARS_PER_LINE 1024
#include <stdio.h>

typedef struct account {
    char iban[16];
    char currency[3];
    unsigned long int balance;
} BankAccount;

int account_number(FILE *file_ptr,
                   char *first_name,
                   char *last_name,
                   BankAccount current_user_accounts_info[]);

char *char_to_str(char c);
void capitalize_str(char *str);
char *generate_iban(char *first_name,
                    char *last_name);

#endif //PROGRAMMING_PROJECT_AUTH_H
