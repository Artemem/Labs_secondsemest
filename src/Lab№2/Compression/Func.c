#include "Header.h"
#define kb 1024
void enter_words_struct(STACK** head)
{
    FILE* text;
    errno_t err = fopen_s(&text, "C:\\Autodesk\\WI\\laba1.txt", "r+");
    if (err != 0)
    {
        printf("Открыть файл не удалось");
        exit(1);
    }
    char* str = (char*)calloc(kb, sizeof(char));
    while (!feof(text))
    {
         get_str(&str, text);
         int i = 0;
         while (*(str + i) != '\0')
         {
             if ((*(str + i) >= L'A' && *(str + i) <= L'Z') || (*(str + i) >= L'a' && *(str + i) <= L'z') || (*(str + i) >= L'À' && *(str + i) <= L'ß') || (*(str + i) >= L'à' && *(str + i) <= L'ÿ'))
             {
                    int size = size_word(str, &i);
                    char* word = word_copy(str, i - size, size);
                    push_STACK(head, word);
             }
             i++;
         }
         if (feof(text))
             break;
    }
    fclose(text);
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
    while ((*(str + *i) >= L'A' && *(str + *i) <= L'Z') || (*(str + *i) >= L'a' && *(str + *i) <= L'z') || (*(str+ *i) >= L'À' && *(str + *i) <= L'ß') || (*(str + *i) >= L'à' && *(str + *i) <= L'ÿ'))
    {
        size++;
        (*i)++;
    }
    return size;
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
void sort_STACK(STACK* head)
{
    STACK * ptr1 = head;
    STACK* ptr2 = head;
    while (ptr1 != NULL)
    {
        while (ptr2 != NULL)
        {
            if (strlen(ptr2->word) > strlen(ptr1->word) || (strlen(ptr2->word) == strlen(ptr1->word)&& (ptr2->n>ptr1->n)))
            {
                char* temp = (ptr2)->word;
                int flag = (ptr2)->n;
                (ptr2)->word =(ptr1)->word;
                (ptr2)->n = (ptr1)->n;
                (ptr1)->word = temp;
                ptr1->n = flag;
            }
            ptr2 = (ptr2)->next;
        }
        ptr1 = (ptr1)->next;
        ptr2 = ptr1;
    }
}
void get_str(char** str, FILE* text)
{
    if (*str != NULL && !feof(text))
    {
        char* buf = (char*)realloc(*str, kb * sizeof(char));
        if (buf != NULL)
        {
            *str = buf;
        }
        fgets(*str, kb, text);
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
char* memory(const char* memory)
{
    char* word;
    word = (char*)calloc(strlen(memory) + 1, sizeof(char));
    return word;
}
void compression(LIST*head)
{
    FILE* text2;
    errno_t err2 = fopen_s(&text2, "C:\\Autodesk\\WI\\laba2.txt", "w+");
    FILE* text1;
    errno_t err1 = fopen_s(&text1, "C:\\Autodesk\\WI\\laba1.txt", "r+");
    if (err1 != 0 || err2!=0)
    {
        printf("Cant open file");
        exit(1);
    }
    else 
    {
        save_data(head, text2);
        char* str = (char*)calloc(kb, sizeof(char));
        while (feof(text1) == 0)
        {
            if (str != NULL && &str != NULL && !feof(text1))
            {
                get_str(&str, text1);
                change_words(&str, head);
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
        int size1= (int)ftell(text1);
        printf("Размер оригинального текста: %d ",size1);
        int size2= (int)ftell(text2);
        printf("\nРазмер сжатого текста: %d ", size2);
        int def_size = size1 - size2;
        printf("\nРазмер сжимаемых данных: %d", def_size);
        free(str);
        fclose(text1);
        fclose(text2);
        free_LIST(&head);
    }
}

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
void save_data(LIST* head, FILE* text)
{
    const char* sb = start_and_end();

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
        head = head->next;
    }
    fputs(sb, text);
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
char* make_str(const LIST* head)
{
    int size = (int)strlen(head->max) + (int)strlen(head->min) + 3;
    char* str = calloc(size, sizeof(char));
    return str;
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
int profit(STACK* max, STACK* min)
{
    if (max != NULL && min != NULL)
    {
        int old_len = ((int)strlen(max->word) * (max->n)) + ((int)strlen(min->word) * (min->n));
        int new_len = ((int)strlen(max->word) * (min->n)) + ((int)strlen(min->word) * (max->n))+ (int)strlen(max->word)+ (int)strlen(min->word)+2;
        int prof = old_len - new_len;
        return prof;
    }
    else
        return 0;
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
        storer->word = memory(word);
        storer->flag = 0;
        storer->word = word;
        *head = storer;
    }
}
void stek_to_list(STACK** in, LIST** out)
{
    //int i = 0;
    int size = size_STACK(*in)/2;
    do
    {
        STACK* tmp1 = *in, * tmp2 = *in, * flag1 = NULL, * flag2 = NULL;
        int max_profit = 0;
        while (tmp1 != NULL)
        {
            while (tmp2 != NULL)
            {
                if (profit(tmp1, tmp2) > max_profit)
                {
                    flag1 = tmp1;
                    flag2 = tmp2;
                    max_profit = profit(tmp1, tmp2);
                }
                tmp2 = tmp2->next;
            }
            tmp1 = tmp1->next;
            tmp2 = tmp1;
        }
        if (flag1 != NULL && flag2 != NULL && *in != NULL)
        {
            if (strlen(flag1->word) > strlen(flag2->word))
            {
                push_list(flag1->word, flag2->word, out);
            }
            else
            {
                push_list(flag2->word, flag1->word, out);
            }
            pop_STACK(in, flag1);
            pop_STACK(in, flag2);
        }
        size--;
    } while (size > 0);
    /*STACK* tmp1 = *in, * tmp2 = *in;
    do
    {
        tmp1 = seek_max_word(*in);
        tmp2 = seek_min_word(*in);
        if (tmp1 != NULL && tmp2 != NULL && *in != NULL)
        {
            if (profit(tmp1, tmp2) > 0 && strcmp(tmp1->word, tmp2->word) > 0)
            {
                push_list(tmp1->word, tmp2->word, out);
            }
            flag_to_STACK(in, tmp1);
            flag_to_STACK(in, tmp2);
        }
        size--;
    } while (tmp1 != tmp2 && size >= i); */
    /*free_STACK(in);
    free_STACK(in);*/
    /*while (tmp1 != tmp2 && size>=i);*/
    /*int max_size = max_size_words(*in);
    while (max_size > 0 && *in!=NULL)
    {
        STACK* tmp1 = seek_max_word(*in, max_size);
        STACK* flag1 = NULL, * flag2 = NULL;
        int min_size = min_size_words(*in);
        int max_profit = 0;
        while(max_size > min_size)
        {
            STACK* tmp2 = seek_min_word(*in, min_size);
            if (profit(tmp1, tmp2) > max_profit && tmp1!=NULL && tmp2!=NULL)
            {
                max_profit = profit(tmp1, tmp2);
                flag1 = tmp1;
                flag2 = tmp2;
                push_list(tmp1->word, tmp2->word, out);
            }
            min_size++;
        } 
        max_size--;
        if (flag1 != NULL && flag2 != NULL && *in != NULL)
        {
            pop_STACK(in, flag1);
            pop_STACK(in, flag2);
        }
    }*/
}
int max_size_words(STACK*head)
{
    int max = 0;
    STACK* tmp = head;
    while (tmp != 0)
    {
        if ((int)strlen(tmp->word) > max)
        {
            max = (int)strlen(tmp->word);
        }
        tmp = tmp->next;
    }
    return max;
}
int min_size_words(STACK* head)
{
    int min = (int)strlen(head->word);
    STACK* tmp = head;
    while (tmp != 0)
    {
        if ((int)strlen(tmp->word) < min)
        {
            min = (int)strlen(tmp->word);
        }
        tmp = tmp->next;
    }
    return min;
}
void flag_to_STACK(STACK** head, STACK* flag) {

    if (*head == NULL)
    {
        return;
    }
    else
    {
        STACK* tmp = *head;
        if (tmp == flag)
        {
            (* head)->flag = 1;
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
STACK* seek_min_word(STACK* head)
{
    STACK* tmp = head, * flag = head;
    int min = 10000;
    int min_size = 100000;
    while (tmp != 0)
    {
        if ((strlen(tmp->word) < min_size || (strlen(tmp->word) == min_size && tmp->n<min))&& tmp->flag!=1)
        {
            min_size = (int)strlen(tmp->word);
            min = tmp->n;
            flag = tmp;
        }
        tmp = tmp->next;
    }
    return flag;
}
STACK* seek_max_word(STACK* head)
{
    STACK* tmp = head, * flag = head;
    int max = 0;
    int max_size = 0;
    while (tmp != 0)
    {
        if ((strlen(tmp->word) > max_size || (strlen(tmp->word) == max_size && tmp->n > max))&&tmp->flag!=1)
        {
            max_size = (int)strlen(tmp->word);
            max = tmp->n;
            flag = tmp;
        }
        tmp = tmp->next;
    }
    return flag;
}
void pop_STACK(STACK** head, STACK* flag1)
{
    if (*head == NULL)
    {
        return;
    }
    else 
    {
        STACK* tmp = *head;
        STACK* tail = *head;
        if (tmp ==flag1) 
        {
            *head = tmp->next;
            free(tmp);
            return;
        }

        while (tmp != flag1 && tmp!=NULL)
        {
            tail = tmp;
            tmp = (tmp)->next;
        }
        if (tmp == NULL) 
        {
            printf("Элемент не найден в стеке\n");
            return;
        }
        tail->next = tmp->next;
        free((tmp)->word);
        free(tmp);
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
int size_STACK(STACK* head)
{
    int size = 0;
    STACK* tmp1 = head;
    while (tmp1 != NULL)
    {
        size++;
        tmp1 = tmp1->next;
    }
    return size;
}
STACK* search_STACK(STACK* head, int n)
{
    if (head == NULL)
    {
        return NULL;
    }
    else 
    {
        int i = 1;
        STACK* tmp = head;
        while (i < n)
        {
            tmp = tmp->next;
            i++;
        }
        return tmp;
    }
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
void show_stack(const STACK* head) {
    while (head != NULL)
    {
        printf("%s ", head->word);
        printf("%d\n ", head->n);
        head = head->next;
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