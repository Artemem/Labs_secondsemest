#include "tree.h"
#include "check.h"
#include "strings.h"

void load_tree(tree** head, FILE* text, int place, int check)
{
    if (place <= check && strncmp(get_number_str(text, place), "\n", 1) != 0)
    {
        tree* buf = malloc(sizeof(tree));
        if (buf == NULL)
        {
            exit(1);
        }
        buf->no = NULL;
        buf->yes = NULL;
        buf->Q_or_A = (char*)calloc(KB, sizeof(char));
        buf->Q_or_A = get_number_str(text, place);
        *head = buf;
        load_tree(&(*head)->no, text, (2 * place + 1), check);
        load_tree(&(*head)->yes, text, (2 * place), check);
    }
    return;
}

void free_TREE(tree** head)
{
    if ((*head)->no == NULL || (*head)->yes == NULL)
    {
        free((*head)->Q_or_A);
        free(*head);
        return;
    }

    free_TREE(&(*head)->yes);
    free_TREE(&(*head)->no);
    free((*head)->Q_or_A);
    free(*head);
}

void show_tree(tree* head)
{
    if (head != NULL)
    {
        printf("%s", head->Q_or_A);
        /*if ((tree->Q_or_A)[strlen(tree->Q_or_A) - 1] != '\n')
            printf("\n");*/
        show_tree(head->no);
        show_tree(head->yes);
    }
}

void start_to_question(tree** head)
{
    char* username = (char*)calloc(KB, sizeof(char));
    check_start(&username);
    system("cls");
    questions(head);
}

void questions(tree** head)
{
    if ((*head)->no == NULL || (*head)->yes == NULL)
    {
        check_guess(head);
    }
    else
    {
        printf("%s", (*head)->Q_or_A);
        char* answer = check_yes_or_no();
        system("cls");
        if (answer[0] == 'Д' || answer[0] == 'д')
        {
            questions(&(*head)->yes);
        }
        else
        {
            questions(&(*head)->no);
        }
    }

}

void add_answer_and_question_to_tree(char* answer, char* question, tree** head)
{
    tree* buf_Y = malloc(sizeof(tree));
    tree* buf_N = malloc(sizeof(tree));
    if (buf_Y == NULL || buf_N == NULL)
    {
        exit(1);
    }
    buf_Y->no = NULL;
    buf_Y->yes = NULL;
    buf_N->no = NULL;
    buf_N->yes = NULL;
    buf_Y->Q_or_A = (char*)calloc(KB, sizeof(char));
    buf_N->Q_or_A = (char*)calloc(KB, sizeof(char));
    buf_Y->Q_or_A = answer;
    buf_N->Q_or_A = (*head)->Q_or_A;
    (*head)->no = buf_N;
    (*head)->yes = buf_Y;
    (*head)->Q_or_A = question;
}

void tree_to_new_data(FILE* data, tree* head)
{
    int n = 0;
    max_place(head, &n, 1);
    for (int i = 1; i <= n; i++)
    {
        char* str = NULL;
        seek_for_str(head, 1, i, &str);
        if (str == NULL)
        {
            str = "\n";
        }
        fputs(str, data);
    }
}

void max_place(tree* head, int* n, int place)
{
    if (head != NULL)
    {
        if (*n < place)
        {
            *n = place;
        }
        max_place(head->no, n, 2 * place + 1);
        max_place(head->yes, n, 2 * place);
    }
    return;
}

void seek_for_str(tree* head, int place, int index, char** str)
{
    if (head != NULL)
    {
        if (place == index)
        {
            *str = (char*)calloc(KB, sizeof(char));
            *str = head->Q_or_A;
        }
        else
        {
            seek_for_str(head->no, 2 * place + 1, index, str);
            seek_for_str(head->yes, 2 * place, index, str);
        }
    }
    return;
}

void add_log_username(const char* username)
{
    FILE* log_database;
    errno_t err = fopen_s(&log_database, "database.txt", "a+");
    if (err != 0)
    {
        printf("Нельзя открыть файл");
        exit(1);
    }
    char* str_username = (char*)calloc(KB, sizeof(char));
    if (str_username == NULL)
        exit(1);
    strcat_s(str_username,KB, "\nДействия ");
    strcat_s(str_username,KB, username);
    strcat_s(str_username,KB, "а:\n");
    fputs(str_username, log_database);
    free(str_username);
    fclose(log_database);
}

void add_log_answers(const char* answer)
{
    FILE* log_database;
    errno_t err = fopen_s(&log_database, "database.txt", "a+");
    if (err != 0)
    {
        printf("Нельзя открыть файл");
        exit(1);
    }
    char* str_log = (char*)calloc(KB, sizeof(char));
    if (str_log == NULL)
        exit(1);
    time_t mytime = time(NULL);
    struct tm* now = (struct tm*)malloc(sizeof(struct tm));
    if (now == NULL)
    {
        exit(1);
    }
    localtime_s(now, &mytime);
    char str[15];
    strftime(str, sizeof(str), "%x", now);
    strcat_s(str_log, KB, "В дату ");
    strcat_s(str_log,KB, str);
    strftime(str, sizeof(str), "%X", now);
    strcat_s(str_log,KB, " во время ");
    strcat_s(str_log,KB, str);
    strcat_s(str_log,KB, " ответил:");
    strcat_s(str_log,KB, answer);
    strcat_s(str_log, KB, "\n");
    fputs(str_log, log_database);
    free(str_log);
    fclose(log_database);
}