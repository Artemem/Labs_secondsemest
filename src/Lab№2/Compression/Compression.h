#pragma once
#include "List.h"
#include "Words.h"

char* symbol_for_saving_data();

char* make_str(const LIST* head);

void save_data(LIST* head, FILE* text);

void compression(LIST* head, FILE*orig_text, FILE*compr_text);

void change_words(char** str, LIST* head);

void compr_str(char** str, char* max, char* min);

void change_min_word(char** str, int start, int differ_size, char* max, int* place);

void change_max_word(char** str, int start, int differ_size, char* min, int* place);

void change_str(char** str, char* word, char* max, char* min, int* place);