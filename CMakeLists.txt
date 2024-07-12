cmake_minimum_required(VERSION 3.27)
project(West_Bank_of_Timisoara)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(login
        src/login.c
        src/helpers.c
        src/print.c
        src/account_operations.c
        src/menus.c)

target_include_directories(login PUBLIC include lib/sds)
