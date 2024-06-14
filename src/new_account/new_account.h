#ifndef PROGRAMMING_PROJECT_NEW_ACCOUNT_H
#define PROGRAMMING_PROJECT_NEW_ACCOUNT_H
#define MAX_CHARS_FOR_NAME 50
#include "../auth/auth.h"
#include <stdbool.h>

char *char_to_str(char c);

void new_account(char *first_name,
                 char *last_name,
                 struct account *user_accounts,
                 int *accounts_found,
                 bool authenticated);

void capitalize_str(char *str);

char *generate_iban(char *first_name,
                    char *last_name);

#endif //PROGRAMMING_PROJECT_NEW_ACCOUNT_H
