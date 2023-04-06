#include "Decompression.h"
#define KB 1024






void word_to_str(char** str, const char* word, int* ind)
{
    int i = 0;
    while (*(word + i) != '\0')
    {
        *(*str + *ind) = *(word + i);
        i++;
        (*ind)++;
    }
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

void go_to_text(FILE*text)
{
    char* str = (char*)calloc(KB, sizeof(char));
    if (str != NULL)
    {
        seek_symbol_for_saving_data(text);
        fgets(str, KB, text);
        seek_symbol_for_saving_data(text);
    }
    free(str);
}



void decompression(LIST* head, FILE*compr_text, FILE*decompr_text)
{
    
        go_to_text(compr_text);
        char* str = (char*)calloc(KB, sizeof(char));
        while (feof(compr_text) == 0)
        {
            if (str != NULL && &str != NULL && !feof(compr_text))
            {
                get_str(&str, compr_text);
                change_words(&str, head);
            }
            if (feof(compr_text))
            {
                break;
            }
            if (str != NULL)
            {
                fputs(str, decompr_text);
            }
        }
        int size_of_compr_text = (int)ftell(compr_text);
        printf("Размер сжатого текста: %d ", size_of_compr_text);
        int size_of_decompr_text = (int)ftell(decompr_text);
        printf("\nРазмер разжатого текста: %d ", size_of_decompr_text);
        int def_size = size_of_decompr_text - size_of_compr_text;
        printf("\nРазмер разжимаемых данных: %d", def_size);
        free(str);
        free_LIST(&head);
}

void change_words(char** str, LIST* head)
{
    LIST* tmp = head;
    while (tmp != NULL)
    {
        compr_str(str, tmp->max, tmp->min);
        tmp = tmp->next;
    }
}

void compr_str(char** str, char* max, char* min)
{
    int i = 1;
    while (i < (int)strlen(*str))
    {
        if ((*(*str + i) >= L'A' && *(*str + i) <= L'Z') || (*(*str + i) >= L'a' && *(*str + i) <= L'z') || (*(*str + i) >= L'À' && *(*str + i) <= L'ß') || (*(*str + i) >= L'à' && *(*str + i) <= L'ÿ'))
        {
            int size = size_of_word(*str, &i);
            char* word = copy_word(*str, i - size, size);
            change_str(str, word, max, min, &i);
        }
        i++;
    }
}

void change_min_word(char** str, int start, int differ_size, char* max, int* place)
{
    int size_new_str = ((int)strlen(*str) + differ_size + 1);
    char* buf = (char*)calloc(size_new_str, sizeof(char));
    if (buf != NULL)
    {
        (void)strcpy_s(buf, sizeof(char) * size_new_str, *str);
        *str = buf;
    }
    for (int i = size_new_str; i > start + differ_size; i--)
    {
        *(*str + i) = *(*str + i - differ_size);
    }
    for (int i = start, j = 0; i < start + strlen(max); i++, j++)
    {
        *(*str + i) = *(max + j);
        *place = i + 1;
    }
}

void change_max_word(char** str, int start, int differ_size, char* min, int* place)
{
    int size_new_str = ((int)strlen(*str) - differ_size + 1);
    int size_old_str = (int)strlen(*str);
    for (int i = start + 1; i < size_old_str - differ_size + 1; i++)
    {
        *(*str + i) = *(*str + i + differ_size);
    }

    for (int i = start, j = 0; i < start + strlen(min); i++, j++)
    {
        *(*str + i) = *(min + j);
        *place = i + 1;
    }
    char* buf = (char*)calloc(size_new_str, sizeof(char));
    if (buf != NULL)
    {
        (void)strcpy_s(buf, sizeof(char) * size_new_str, *str);
        *str = buf;
    }
}

void change_str(char** str, char* word, char* max, char* min, int* place)
{
    int start = *place - (int)strlen(word);
    int differ_size = (int)strlen(max) - (int)strlen(min);
    if (strcmp(word, min) == 0)
    {
        change_min_word(str, start, differ_size, max, place);
    }
    if (strcmp(word, max) == 0)
    {
        change_max_word(str, start, differ_size, min, place);
    }
}

