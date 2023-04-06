#include "Stack.h"

void enter_words_to_stack(STACK** head, FILE* text)
{
    char* str = (char*)calloc(KB, sizeof(char));
    while (!feof(text))
    {
        get_str(&str, text);
        int i = 0;
        while (*(str + i) != '\0')
        {
            if ((*(str + i) >= L'A' && *(str + i) <= L'Z') || (*(str + i) >= L'a' && *(str + i) <= L'z') || (*(str + i) >= L'À' && *(str + i) <= L'ß') || (*(str + i) >= L'à' && *(str + i) <= L'ÿ'))
            {
                int size = size_of_word(str, &i);
                char* word = copy_word(str, i - size, size);
                push_STACK(head, word);
            }
            i++;
        }
        if (feof(text))
            break;
    }
    free(str);
}

void show_stack(const STACK* head) {
    while (head != NULL)
    {
        printf("%s ", head->word);
        printf("%d\n ", head->n);
        head = head->next;
    }
}

int check_STACK(STACK* head, char* word)
{
    while (head)
    {
        if (strcmp(head->word, word) == 0)
        {
            head->n++;
            return 0;
        }
        head = head->next;
    }
    return 1;
}

STACK* cheker_words(STACK** head, const char* word)
{
    STACK* buf = *head;
    while (buf)
    {
        if (strcmp(buf->word, word) == 0)
        {
            return buf;
        }
        buf = buf->next;
    }
    return buf;
}

void free_STACK(STACK** head)
{
    while ((*head))
    {
        STACK* tmp = *head;
        free((tmp->word));
        *head = (*head)->next;
        free(tmp);
    }
}
void flag_to_STACK(STACK** head, STACK* flag)
{

    if (*head == NULL)
    {
        return;
    }
    else
    {
        STACK* tmp = *head;
        if (tmp == flag)
        {
            (*head)->flag = 1;
            return;
        }
        while (tmp != flag && tmp != NULL)
        {
            tmp = (tmp)->next;
        }
        if (tmp == NULL)
        {
            printf("Элемент не найден в стеке\n");
            return;
        }
        tmp->flag = 1;
    }
}

void push_STACK(STACK** head, char* word)
{

    STACK* buf = *head;
    int cheker = check_STACK(buf, word);
    if (cheker)
    {
        STACK* storer = malloc(sizeof(STACK));
        if (storer == NULL) {
            exit(1);
        }
        storer->next = *head;
        storer->n = 1;
        storer->word = memory_for_word(word);
        storer->flag = 0;
        storer->word = word;
        storer->length = (int)strlen(word);
        *head = storer;
    }
}

void pop_STACK(STACK** head, STACK* flag)
{
    STACK* tmp = *head;
    STACK* prev = *head;
    if (tmp == flag)
    {
        *head = tmp->next;
        free(tmp->word);
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp != flag)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        printf("Элемент не найден в стеке\n");
        return;
    }
    prev->next = tmp->next;
    free(tmp->word);
    free(tmp);
}