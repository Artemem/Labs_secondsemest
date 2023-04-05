#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <string.h>
#include <locale.h>
#include<io.h>
typedef struct string {
    char* word;
    int n;
    int flag;
    struct string* next;
} STACK;
typedef struct wordsComp {
    char* min;
    char* max;
    struct wordsComp* next;
}LIST;
void flag_to_STACK(STACK** head, STACK* flag);
char* start_and_end();
void word_to_str(char** str, const char* word, int* ind);
char* make_str(const LIST* head);
void enter_words_struct(STACK** head);
void save_data(LIST* head, FILE* text);
char* word_copy(const char* str, int ind, int size);
int size_word(const char* str, int* i);
STACK* cheker_words(STACK** head, const char* word);

void sort_STACK(STACK* head);

void get_str(char** str, FILE* text);
char* memory(const char* memory);
void compression(LIST* head);
void change_words(char** str, LIST* head);
void compr_str(char** str, char* max, char* min);
void change_min_word(char** str, int start, int differ_size, char* max, int* place);
void change_max_word(char** str, int start, int differ_size, char* min, int* place);
void change_str(char** str, char* word, char* max, char* min, int* place);

int profit(STACK* max, STACK* min);
int check_STACK(STACK* head, char* word);
void push_STACK(STACK** head, char* word);

void stek_to_list(STACK** in, LIST** out);
void pop_STACK(STACK** head, STACK* flag1);
void push_list(char* max, char* min, LIST** out);

int size_STACK(STACK* head);

STACK* search_STACK(STACK* head, int n);

void free_STACK(STACK** head);

void free_LIST(LIST** head);

void show_stack(const STACK* head);
void show_list(LIST* head);
int max_size_words(STACK* head);
int min_size_words(STACK* head);
STACK* seek_min_word(STACK* head);
STACK* seek_max_word(STACK* head);