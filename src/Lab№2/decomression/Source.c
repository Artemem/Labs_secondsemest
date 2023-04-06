#include "Decompression.h"
#include "Words.h"
#include "List.h"
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	system("cls");
    FILE* compr_text;
    errno_t err1 = fopen_s(&compr_text, "C:\\Autodesk\\WI\\laba2.txt", "r+");
    FILE* decompr_text;
    errno_t err2 = fopen_s(&decompr_text, "C:\\Autodesk\\WI\\laba3.txt", "w+");
    if (err1 != 0 || err2 != 0)
    {
        printf("Нельзя открыть файл");
        return 1;
    }
	LIST* list = NULL;
	make_list(&list, compr_text);
	decompression(list, compr_text, decompr_text);
    fclose(compr_text);
    fclose(decompr_text);
}