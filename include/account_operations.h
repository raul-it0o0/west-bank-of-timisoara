#ifndef PROGRAMMING_PROJECT_NEW_ACCOUNT_H
#define PROGRAMMING_PROJECT_NEW_ACCOUNT_H
#define MAX_CHARS_FOR_NAME 50
#include "helpers.h"
#include "print.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void view_accounts(const User *session_user);
void edit_data(User *session_user);
void edit_account(User *session_user);
void edit_credentials();
void transaction();
void delete_account();
void new_account(User *session_user, bool authenticated);

#endif //PROGRAMMING_PROJECT_NEW_ACCOUNT_H
