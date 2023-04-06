#include "Compression.h"


void compression(LIST*head, FILE*orig_text, FILE*compr_text)
{       
    save_data(head, compr_text);
    char* str = (char*)calloc(KB, sizeof(char)); 
    rewind(orig_text);
    while (feof(orig_text) == 0)   
    {    
        if (str != NULL && &str != NULL && !feof(orig_text)) 
        {   
            get_str(&str, orig_text); 
            change_words(&str, head); 
        }
        if (feof(orig_text))
        { 
            break; 
        }  
        if (str != NULL) 
        { 
            fputs(str, compr_text);
        }
    }
    int size_orig_text= (int)ftell(orig_text);
    printf("Размер оригинального текста: %d ", size_orig_text);
    int size_compr_text= (int)ftell(compr_text);
    printf("\nРазмер сжатого текста: %d ", size_compr_text);
    int def_size = size_orig_text - size_compr_text;  
    printf("\nРазмер сжимаемых данных: %d", def_size); 
    free(str);
    free_LIST(&head);
}

void save_data(LIST* head, FILE* text)
{
    char* sb = symbol_for_saving_data();

    fputs(sb, text);
    while (head!=NULL)
    {
        char* str = make_str(head);
        if (str != NULL)
        {
            int ind = 0;
            word_to_str(&str, head->max, &ind);
            *(str + ind) = ' ';
            ind++;
            word_to_str(&str, head->min, &ind);
            *(str + ind) = '\n'; 
            ind++;
            fputs(str, text);
        }
        free(str);
        head = head->next;
    }
    fputs(sb, text);
    free(sb);
}
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
char* make_str(const LIST* head)
{
    int size = (int)strlen(head->max) + (int)strlen(head->min) + 3;
    char* str = (char*)calloc(size, sizeof(char));
    return str;
}
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
void change_min_word(char** str, int start, int differ_size, char*max, int *place)
{
    int size_new_str = ((int)strlen(*str) + differ_size+1);
    char* buf = (char*)calloc(size_new_str, sizeof(char));
    if (buf != NULL)
    {
        (void)strcpy_s(buf, sizeof(char)*size_new_str, *str);
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
    int size_new_str = ((int)strlen(*str) - differ_size+1);
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














