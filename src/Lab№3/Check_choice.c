#include "Check_choice.h"

void check_choice_task(int* ch)
{
    while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 && *ch != 3 && *ch != 4 && *ch != 5 || getchar() != '\n')
    {
        printf("������.���������� �����\n�������� �������:");
        rewind(stdin);
    }
}
void check_go_choice(int* ch)
{
    while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 || getchar() != '\n')
    {
        printf("������.���������� �����\n�����:");
        rewind(stdin);
    }
}
void check_file_name(char** file_name)
{
    FILE* BMPfile;
    errno_t err = fopen_s(&BMPfile, *file_name, "r+b");
    if (err != 0)
    {
        printf("������ ������� ����");
        free(*file_name);
        exit(1);
    }
    fclose(BMPfile);
}
int check_median_choice()
{
    int n = 0;
    printf("������� ��������� ��������� ���������� [1-1000]:");
    while (scanf_s("%d", &n) != 1 || n > 1000 || n < 1 || getchar() != '\n')
    {
        printf("������. ���������� �����.\n������� ��������� ��������� ���������� [1-1000]:");
        rewind(stdin);
    }
    return n;
}
float check_gamma()
{
    float gamma = (float)0000000000;
    printf("������� ����������� �����-��������� [0-20]:");
    while (scanf_s("%f", &gamma) != 1 || gamma > 100.0 || gamma < 0.0 || getchar() != '\n')
    {
        printf("������. ���������� �����.\n������� ����������� �����-��������� [0-20]:");
        rewind(stdin);
    }
    return gamma;
}
char* enter_file_name()
{
    char* name = (char*)calloc(KB, sizeof(char));
    printf("������� �������� ����� (!!! � ����������� .bmp):");
    if (name != NULL)
    {
        while ((int)gets_s(name, KB) == 1 || (int)strlen(name) < 2)
        {
            printf("������. ���������� �����\n������� �������� ����� (!!! � ����������� .bmp):");
            rewind(stdin);
        }
    }
    return name;
}
void check_ID(BMPfile** picture)
{
    if ((*picture)->bhdr.ID[0] != 'B' && (*picture)->bhdr.ID[1] != 'M')
    {
        free(*picture);
        exit(1);
    }
}
