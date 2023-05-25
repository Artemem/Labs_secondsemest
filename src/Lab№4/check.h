#pragma once
#include "tree.h"

int check_str_in_text(FILE* text);
char* check_answer();
char* check_differ(char* answer, char* guess);
char* check_yes_or_no();
void check_start();
void check_go_choice(int* ch);
void check_guess(tree** head);