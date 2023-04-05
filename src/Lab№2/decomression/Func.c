#include "Header.h"
char* start_and_end()
{
    char* symb = calloc(3, sizeof(char));
    if (symb)
    {
        *(symb + 0) = '/';
        *(symb + 1) = '\n';
    }
    return symb;
}
void seek_start_or_end(FILE* text)
{
    char* str = calloc(1024, sizeof(char));

    if (str != NULL)
    {
        while (!feof(text) && strcmp(str, start_and_end()) != 0)
        {
            fgets(str, 1024, text);
        }
    }
    free(str);
}

void get_data(LIST** head, FILE* text)
{
    char* str = calloc(1024, sizeof(char));

    fgets(str, 1024, text);

    while (!feof(text) && strcmp(str, start_and_end()) != 0)
    {
        int i = 0;
        char* max = word_from_str(str, &i);
        char* min = word_from_str(str, &i);
        fgets(str, 1024, text);
        push_list(max, min, head);
    }

    free(str);
}
char* word_from_str(char* str, int* pos_in_str)
{
    int i = *pos_in_str;
    char* word = NULL;;
    while (*(str + i) != '\0')
    {
        if ((*(str + i) >= L'A' && *(str + i) <= L'Z') || (*(str + i) >= L'a' && *(str + i) <= L'z') || (*(str + i) >= L'À' && *(str + i) <= L'ß') || (*(str + i) >= L'à' && *(str + i) <= L'ÿ'))
        {
            int size = size_word(str, &i);
            word = word_copy(str, i - size, size);
            break;
        }
        i++;
    }
    *pos_in_str = i;

    return word;
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
void make_list(LIST** head)
{
    FILE* text;
    errno_t err = fopen_s(&text, "C:\\Autodesk\\WI\\laba2.txt", "r");
    if (err != 0)
    {
        printf("Файл не открывается");
        exit(1);
    }
    else
    {
        seek_start_or_end(text);
        get_data(head, text);
        fclose(text);
    }

}

char* word_copy(const char* str, int ind, int size)
{
    char* word = (char*)calloc(size + 1, sizeof(char));
    if (word != NULL)
    {
        for (int i = ind, j = 0; j < size; i++, j++)
        {
            *(word + j) = *(str + i);
        }
    }
    return word;
}
int size_word(const char* str, int* i)
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
        char* buf = (char*)realloc(*str, 1024 * sizeof(char));
        if (buf != NULL)
        {
            *str = buf;
        }
        fgets(*str, 1024, text);
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
    char* str = (char*)calloc(1024, sizeof(char));
    if (str != NULL)
    {
        seek_start_or_end(text);
        fgets(str, 1024, text);
        seek_start_or_end(text);
    }
    free(str);
}
char* memory(const char* memory)
{
    char* word;
    word = (char*)calloc(strlen(memory) + 1, sizeof(char));
    return word;
}
void decompression(LIST* head)
{
    FILE* text2;
    errno_t err2 = fopen_s(&text2, "C:\\Autodesk\\WI\\laba3.txt", "w+");
    FILE* text1;
    errno_t err1 = fopen_s(&text1, "C:\\Autodesk\\WI\\laba2.txt", "r+");
    if (err1 != 0 || err2 != 0)
    {
        printf("Cant open file");
        exit(1);
    }
    else
    {
        go_to_text(text1);
        int size1 = (int)ftell(text1);
        int size2 = 0;
        char* str = (char*)calloc(10240, sizeof(char));
        while (feof(text1) == 0)
        {
            if (str != NULL && &str != NULL && !feof(text1))
            {
                get_str(&str, text1);
                change_words(&str, head);
                size2 = size2 + (int)strlen(str);
            }
            if (feof(text1))
            {
                break;
            }
            if (str != NULL)
            {
                fputs(str, text2);
            }
        }
        size1 = (int)ftell(text1) - size1;
        printf("Длина сжатого текста: %d ", size1);
        /*int size2 = (int)ftell(text2);*/
        printf("\nДлина разжатого текста: %d ", size2);
        int def_size = size2 - size1;
        printf("\nРазмер разжимаемых данных: %d", def_size);
        free(str);
        fclose(text1);
        fclose(text2);
        free_LIST(&head);
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
            int size = size_word(*str, &i);
            char* word = word_copy(*str, i - size, size);
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
void push_list(char* max, char* min, LIST** out)
{
    LIST* buf = malloc(sizeof(LIST));
    if (buf == NULL)
    {
        exit(1);
    }
    buf->next = *out;
    buf->min = memory(min);
    buf->min = min;
    buf->max = memory(max);
    buf->max = max;
    *out = buf;
}
void free_LIST(LIST** head)
{
    while (*head!=NULL)
    {
        LIST* tmp = *head;
        free((*head)->max);
        free((*head)->min);
        *head = (*head)->next;
        free(tmp);
    }
}
void show_list(LIST* head)
{
    while (head != NULL)
    {
        printf("\n%s ", head->max);
        printf("%s ", head->min);
        head = head->next;
    }
}