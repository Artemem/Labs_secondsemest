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
    printf("��� %s?", buf);
    char* yes_or_no = check_yes_or_no();
    if (yes_or_no[0] == '�' || yes_or_no[0] == '�')
    {
        system("cls");
        printf("��������, ��� %s", (*head)->Q_or_A);
    }
    else
    {
        char* answer = check_answer();
        char* question = check_differ(answer, (*head)->Q_or_A);
        add_answer_and_question_to_tree(answer, question, head);
        system("cls");
        printf("��������, ��� %s", answer);
    }
    free(yes_or_no);
    free(buf);
}
char* check_answer()
{
    char* answer = (char*)calloc(KB, sizeof(char));
    if (answer == NULL)
        exit(1);
    printf("\n� ��� ���?\n�����:");
    while (gets_s(answer, (KB - 1) * sizeof(char)) == NULL || strlen(answer) < 2)
    {
        printf("\n������.�������� �����\n��������, ��� �� ��������.\n�����:");
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
    printf("\n��� ���������� %s �� %s?\n�����:", buf1, buf2);
    while (gets_s(question, (KB) * sizeof(char)) == NULL || strlen(question) < 2)
    {
        printf("\n������.�������� �����\n��������,��� ���������� %s �� %s\n�����:", answer, guess);
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
    printf("\n�����(��/���):");
    while (gets_s(answer, (KB) * sizeof(char)) == NULL || ((answer)[0] != '�' && (answer)[0] != '�' && (answer)[0] != '�' && (answer)[0] != '�') || ((answer)[1] != '�' && (answer)[1] != '�' && (answer)[1] != '�' && (answer)[1] != '�' && (answer)[2] != '�' && (answer)[2] != '�') || strlen(answer) < 2 || strlen(answer) > 3)
    {
        printf("������.�������� �����\n�������� �����(��/���):");
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
    printf("�������� ����:");
    while (gets_s(username, (KB) * sizeof(char)) == NULL || strlen(username) < 1)
    {
        printf("������.�������� �����\n�������� ����:");
        rewind(stdin);
    }
    add_log_username(username);
    printf("\n%s, ��������� ����� ��������������� ���� �� ����� ���������\n\n������� Enter, ���� ������:", username);
    while (getchar() != '\n')
    {
        printf("������.�������� �����\n������� Enter, ���� ������:");
        rewind(stdin);
    }
    add_log_answers("ENTER");
}
void check_go_choice(int* ch)
{
    char* choice = check_yes_or_no();
    if ((choice)[0] == '�' || (choice)[0] == '�')
        *ch = 1;
    else
        *ch = 0;
    free(choice);
}