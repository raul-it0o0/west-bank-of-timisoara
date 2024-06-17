cmake_minimum_required(VERSION 3.27)
project(West_Bank_of_Timisoara)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(login
        src/login.c
        src/auth/auth.c
        src/auth/auth.h
        src/user_inputs/user_inputs.c
        src/user_inputs/user_inputs.h
        src/auth_success/auth_success.c
        src/auth_success/auth_success.h
        src/new_account/new_account.c
        src/new_account/new_account.h)
