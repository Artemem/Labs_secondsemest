#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <string.h>
#include <locale.h>
#include<io.h>
typedef struct wordsComp {
    char* min;
    char* max;
    struct wordsComp* next;
}LIST;
char* start_and_end();
void seek_start_or_end(FILE* text);
void get_data(LIST** head, FILE* text);
char* word_copy(const char* str, int ind, int size);
int size_word(const char* str, int* i);
void seek_start_or_end(FILE* text);
void get_str(char** str, FILE* text);
char* memory(const char* memory);
void decompression(LIST* head);
void change_words(char** str, LIST* head);
void compr_str(char** str, char* max, char* min);
void change_min_word(char** str, int start, int differ_size, char* max, int* place);
void change_max_word(char** str, int start, int differ_size, char* min, int* place);
void change_str(char** str, char* word, char* max, char* min, int* place);
void push_list(char* max, char* min, LIST** out);
void go_to_text(FILE* text);
void free_LIST(LIST** head);
void show_list(LIST* head);
void make_list(LIST** head);
char* start_and_end();
char* word_from_str(char* str, int* pos_in_str);