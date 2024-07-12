#ifndef WEST_BANK_OF_TIMISOARA_MENUS_H
#define WEST_BANK_OF_TIMISOARA_MENUS_H
#include <stdio.h>
#include "account_operations.h"
#include "helpers.h"
#include "print.h"

void no_match_found_prompt(char *user_input);

int auth(User* session_user);

void auth_success(User* session_user);


#endif //WEST_BANK_OF_TIMISOARA_MENUS_H
