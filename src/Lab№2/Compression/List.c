#include "List.h"

void stack_to_list(STACK** in, LIST** out)
{
    int max_profit = 0;
    STACK* flag1 = NULL, * flag2 = NULL;
    do
    {
        flag1 = NULL;
        flag2 = NULL;
        STACK* tmp1 = *in, * tmp2 = *in;
        max_profit = 0;
        while (tmp1 != NULL)
        {
            while (tmp2 != NULL)
            {
                if (check_profit(tmp1, tmp2) > max_profit && tmp1->flag != 1 && tmp2->flag != 1)
                {
                    flag1 = tmp1;
                    flag2 = tmp2;
                    max_profit = check_profit(tmp1, tmp2);
                }
                tmp2 = tmp2->next;
            }
            tmp1 = tmp1->next;
            tmp2 = tmp1;
        }
        if (flag1 != NULL && flag2 != NULL && *in != NULL)
        {
            if (flag1->length > flag2->length)
            {
                push_list(flag1->word, flag2->word, out);
            }
            else
            {
                push_list(flag2->word, flag1->word, out);
            }
            flag_to_STACK(in, flag1);
            flag_to_STACK(in, flag2);
        }
    } while (max_profit != 0 && flag1 != NULL && flag2 != NULL);
}

int check_profit(STACK* max, STACK* min)
{
    if (max != NULL && min != NULL)
    {
        int old_len = ((max->length) * (max->n)) + ((min->length) * (min->n));
        int new_len = ((max->length) * (min->n)) + ((min->length) * (max->n)) + max->length + +3;
        int prof = old_len - new_len;
        return prof;
    }
    else
    {
        return 0;
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
    buf->min = memory_for_word(min);
    buf->min = min;
    buf->max = memory_for_word(max);
    buf->max = max;
    *out = buf;
}


void free_LIST(LIST** head)
{
    while (*head)
    {
        LIST* tmp = *head;
        free((tmp)->max);
        free((tmp)->min);
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