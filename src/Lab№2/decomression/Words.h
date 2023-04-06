#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<io.h>
#define KB 1024
void seek_symbol_for_saving_data(FILE* text);
char* symbol_for_saving_data();
char* copy_word(const char* str, int ind, int size);
int size_of_word(const char* str, int* i);
char* memory_for_word(const char* memory);