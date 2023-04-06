#pragma once
#include "Words.h"
typedef struct string {
    char* word;
    int n;
    int length;
    int flag;
    struct string* next;
} STACK;


int check_profit(STACK* max, STACK* min);
void flag_to_STACK(STACK** head, STACK* flag);
void enter_words_to_stack(STACK** head, FILE* text);
int check_STACK(STACK* head, char* word);

void push_STACK(STACK** head, char* word);
void show_stack(const STACK* head);
void pop_STACK(STACK** head, STACK* flag);
void free_STACK(STACK** head);
STACK* cheker_words(STACK** head, const char* word);
