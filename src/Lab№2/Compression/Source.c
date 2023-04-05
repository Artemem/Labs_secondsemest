#include "Header.h"
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	system("cls");
	STACK* stack = NULL;
	LIST* list = NULL;
	enter_words_struct(&stack);
	/*show_stek(stek);*/
	/*sort_STACK(stack);*/
	/*show_stek(stek);*/
	stek_to_list(&stack, &list);
	/*show_list(list);*/
	compression(list);
	/*free_STACK(&stack);*/
	return 0;
}