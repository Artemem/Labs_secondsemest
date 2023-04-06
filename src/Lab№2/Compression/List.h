#pragma once

#include "Stack.h"
#include "Words.h"

typedef struct wordsComp {
    char* min;
    char* max;
    struct wordsComp* next;
}LIST;


void word_to_str(char** str, const char* word, int* ind);

void stack_to_list(STACK** in, LIST** out);

void push_list(char* max, char* min, LIST** out);


void free_LIST(LIST** head);

void show_list(LIST* head);
