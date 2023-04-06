#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<io.h>
#define KB 1024
char* copy_word(const char* str, int ind, int size);
int size_of_word(const char* str, int* i);
char* memory_for_word(const char* memory);
void get_str(char** str, FILE* text);
