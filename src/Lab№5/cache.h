#pragma once
#include "main_func.h"


void add_dop_element(cache* dop_element, char* id, char* domain, cache** head);
void collision(cache** head, cache** tail, cache** buf_cache, hash** table, char* id, char* domain, int key, int* size);
int check_size_of_cache(cache* head);
void add_times_call(cache* head);
void add_times_call_column(cache* head);
int check_cache_for_ID(char** domain, hash* table, int size, cache** head);
void shift_cache(cache** head, cache** buf, cache** buf2, char** domain, int flag);
cache* find_place(cache* element);
void free_cache(hash** table, int size);