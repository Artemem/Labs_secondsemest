#include "Compression.h"
#include "Stack.h"
#include "List.h"
#include "Words.h"
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	system("cls");
	FILE* orig_text;
	errno_t err1 = fopen_s(&orig_text, "C:\\Autodesk\\WI\\laba1.txt", "r+");
	FILE* compr_text;
	errno_t err2 = fopen_s(&compr_text, "C:\\Autodesk\\WI\\laba2.txt", "w+");
	if (err1 != 0 || err2 != 0)
	{
		printf("Файлы нельзя открыть");
		return(1);
	}
	STACK* stack = NULL;
	LIST* list = NULL;
	enter_words_to_stack(&stack, orig_text);
	stack_to_list(&stack, &list);
	compression(list, orig_text, compr_text);
	fclose(orig_text);
	fclose(compr_text);
	return 0;
}