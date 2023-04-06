#pragma once
#include "Words.h"
typedef struct wordsComp {
    char* min;
    char* max;
    struct wordsComp* next;
}LIST;
void get_data(LIST** head, FILE* text);
char* get_word_from_str(char* str, int* pos_in_str);
void free_LIST(LIST** head);

void show_list(LIST* head);

void make_list(LIST** head, FILE*text);
void push_list(char* max, char* min, LIST** out);