#include "Words.h"
char* memory_for_word(const char* memory)
{
    char* word;
    word = (char*)calloc(strlen(memory) + 1, sizeof(char));
    return word;
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
void get_str(char** str, FILE* text)
{
    if (*str != NULL && !feof(text))
    {
        char* buf = (char*)realloc(*str, KB * sizeof(char));
        if (buf != NULL)
        {
            *str = buf;
        }
        fgets(*str, KB, text);
        buf = (char*)realloc(*str, (strlen(*str) + 1) * sizeof(char));
        if (buf != NULL)
        {
            *str = buf;
        }
        else
        {
            exit(1);
        }
    }
}