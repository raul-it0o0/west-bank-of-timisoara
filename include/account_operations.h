#ifndef PROGRAMMING_PROJECT_NEW_ACCOUNT_H
#define PROGRAMMING_PROJECT_NEW_ACCOUNT_H
#define MAX_CHARS_FOR_NAME 50
#include "helpers.h"
#include "print.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void view_accounts(char *first_name,
                   BankAccount *user_accounts,
                   const int *accounts_found);
void edit_account();
void transaction();
void delete_account();
void new_account(char *first_name,
                 char *last_name,
                 struct account *user_accounts,
                 int *accounts_found,
                 bool authenticated);

#endif //PROGRAMMING_PROJECT_NEW_ACCOUNT_H
