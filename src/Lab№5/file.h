#pragma once
#include "main_func.h"
void find_domain(FILE* data, char** str, char* id, int* size, char*** domain_arr);

int check_ID_in_data(FILE* data, char** id, int choice);

int check_domain_in_data(FILE* data, char** domain);
int seek_for_ID_in_file(FILE* data, const char* domain, char** id);
int seek_str(const char* domain, char** str, FILE* data);