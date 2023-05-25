#include "check.h"
#include "strings.h"

int check_str_in_text(FILE* text)
{
    char* str = (char*)calloc(KB, sizeof(char));
    int i = 0;
    while (!feof(text))
    {
        if (str != NULL)
        {
            fgets(str, KB - 1, text);
        }
        i++;
        if (feof(text))
            break;
    }
    free(str);
    return i;
}

void check_guess(tree** head)
{
    char* buf = decrease_str((*head)->Q_or_A);
    printf("Это %s?", buf);
    char* yes_or_no = check_yes_or_no();
    if (yes_or_no[0] == 'Д' || yes_or_no[0] == 'д')
    {
        system("cls");
        printf("Отгадано, это %s", (*head)->Q_or_A);
    }
    else
    {
        char* answer = check_answer();
        char* question = check_differ(answer, (*head)->Q_or_A);
        add_answer_and_question_to_tree(answer, question, head);
        system("cls");
        printf("Отгадано, это %s", answer);
    }
    free(yes_or_no);
    free(buf);
}
char* check_answer()
{
    char* answer = (char*)calloc(KB, sizeof(char));
    if (answer == NULL)
        exit(1);
    printf("\nА что это?\nОтвет:");
    while (gets_s(answer, (KB - 1) * sizeof(char)) == NULL || strlen(answer) < 2)
    {
        printf("\nОшибка.Попробуй снова\nНапишите, что вы загадали.\nОтвет:");
        rewind(stdin);
    }
    add_log_answers(answer);
    int length = (int)strlen(answer);
    if (answer[length - 1] != '\n')
    {
        answer[length] = '\n';
        answer[length + 1] = '\0';
    }
    return answer;
}
char* check_differ(char* answer, char* guess)
{
    char* question = (char*)calloc(KB, sizeof(char));
    if (question == NULL)
        exit(1);
    char* buf1 = decrease_str(answer);
    char* buf2 = decrease_str(guess);
    printf("\nЧем отличается %s от %s?\nОтвет:", buf1, buf2);
    while (gets_s(question, (KB) * sizeof(char)) == NULL || strlen(question) < 2)
    {
        printf("\nОшибка.Попробуй снова\nНапишите,чем отличается %s от %s\nОтвет:", answer, guess);
        rewind(stdin);
    }
    add_log_answers(question);
    int length = (int)strlen(question);
    question[length] = '?';
    question[length + 1] = '\n';
    question[length + 2] = '\0';
    free(buf1);
    free(buf2);
    return question;
}
char* check_yes_or_no()
{
    char* answer = (char*)calloc(KB, sizeof(char));
    if (answer == NULL)
        exit(1);
    printf("\nОтвет(Да/Нет):");
    while (gets_s(answer, (KB) * sizeof(char)) == NULL || ((answer)[0] != 'Д' && (answer)[0] != 'д' && (answer)[0] != 'Н' && (answer)[0] != 'н') || ((answer)[1] != 'А' && (answer)[1] != 'а' && (answer)[1] != 'Е' && (answer)[1] != 'е' && (answer)[2] != 'Т' && (answer)[2] != 'т') || strlen(answer) < 2 || strlen(answer) > 3)
    {
        printf("Ошибка.Попробуй снова\nНапишите ответ(Да/Нет):");
        rewind(stdin);
    }
    add_log_answers(answer);
    return answer;
}
void check_start()
{
    char* username = (char*)calloc(KB, sizeof(char));
    if (username == NULL)
        exit(1);
    printf("Назовите себя:");
    while (gets_s(username, (KB) * sizeof(char)) == NULL || strlen(username) < 1)
    {
        printf("Ошибка.Попробуй снова\nНазовите себя:");
        rewind(stdin);
    }
    add_log_username(username);
    printf("\n%s, загадайте любое астрономическое тело из нашей Вселенной\n\nНажмите Enter, если готовы:", username);
    while (getchar() != '\n')
    {
        printf("Ошибка.Попробуй снова\nНажмите Enter, если готовы:");
        rewind(stdin);
    }
    add_log_answers("ENTER");
}
void check_go_choice(int* ch)
{
    char* choice = check_yes_or_no();
    if ((choice)[0] == 'Д' || (choice)[0] == 'д')
        *ch = 1;
    else
        *ch = 0;
    free(choice);
}