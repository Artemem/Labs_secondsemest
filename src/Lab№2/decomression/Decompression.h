#pragma once
#include "Words.h"
#include "List.h"

void get_str(char** str, FILE* text);

void decompression(LIST* head, FILE*compr_text, FILE*decompr_text);

void change_words(char** str, LIST* head);

void compr_str(char** str, char* max, char* min);

void change_min_word(char** str, int start, int differ_size, char* max, int* place);

void change_max_word(char** str, int start, int differ_size, char* min, int* place);

void change_str(char** str, char* word, char* max, char* min, int* place);

void go_to_text(FILE* text);
