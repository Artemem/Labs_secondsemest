#include "Header.h"
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	system("cls");
	LIST* list = NULL;
	make_list(&list);
	/*show_list(list);*/
	decompression(list);
	return 0;
}