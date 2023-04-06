#include "Words.h"

char* symbol_for_saving_data()
{
    char* symb = calloc(3, sizeof(char));
    if (symb)
    {
        *(symb + 0) = '/';
        *(symb + 1) = '\n';
    }
    return symb;
}

void seek_symbol_for_saving_data(FILE* text)
{
    char* str = calloc(KB, sizeof(char));

    if (str != NULL)
    {
        while (!feof(text) && strcmp(str, symbol_for_saving_data()) != 0)
        {
            fgets(str, 1024, text);
        }
    }
    free(str);
}
char* copy_word(const char* str, int ind, int size)
{
    char* word = (char*)calloc(size+1, sizeof(char));
    if (word != NULL)
    {
        for (int i = ind, j = 0; j < size; i++, j++)
        {
            *(word + j) = *(str + i);
        }
    }
    return word;
}

int size_of_word(const char* str, int* i)
{
    int size = 0;
    while ((*(str + *i) >= L'A' && *(str + *i) <= L'Z') || (*(str + *i) >= L'a' && *(str + *i) <= L'z') || (*(str + *i) >= L'À' && *(str + *i) <= L'ß') || (*(str + *i) >= L'à' && *(str + *i) <= L'ÿ'))
    {
        size++;
        (*i)++;
    }
    return size;
}
char* memory_for_word(const char* memory)
{
    char* word;
    word = (char*)calloc(strlen(memory) + 1, sizeof(char));
    return word;
}