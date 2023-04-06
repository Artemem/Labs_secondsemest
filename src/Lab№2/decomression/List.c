#include "List.h"

void make_list(LIST** head, FILE*text)
{
    seek_symbol_for_saving_data(text);
    get_data(head, text);
}
void get_data(LIST** head, FILE* text)
{
    char* str = calloc(KB, sizeof(char));

    fgets(str, KB, text);

    while (!feof(text) && strcmp(str, symbol_for_saving_data()) != 0)
    {
        int i = 0;
        char* max = get_word_from_str(str, &i);
        char* min = get_word_from_str(str, &i);
        fgets(str, KB, text);
        push_list(max, min, head);
    }
    free(str);
}

char* get_word_from_str(char* str, int* pos_in_str)
{
    int i = *pos_in_str;
    char* word = NULL;;
    while (*(str + i) != '\0')
    {
        if ((*(str + i) >= L'A' && *(str + i) <= L'Z') || (*(str + i) >= L'a' && *(str + i) <= L'z') || (*(str + i) >= L'À' && *(str + i) <= L'ß') || (*(str + i) >= L'à' && *(str + i) <= L'ÿ'))
        {
            int size = size_of_word(str, &i);
            word = copy_word(str, i - size, size);
            break;
        }
        i++;
    }
    *pos_in_str = i;

    return word;
}
void push_list(char* max, char* min, LIST** out)
{
    LIST* buf = malloc(sizeof(LIST));
    if (buf == NULL)
    {
        exit(1);
    }
    buf->next = *out;
    buf->min = memory_for_word(min);
    buf->min = min;
    buf->max = memory_for_word(max);
    buf->max = max;
    *out = buf;
}

void free_LIST(LIST** head)
{
    while (*head != NULL)
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
