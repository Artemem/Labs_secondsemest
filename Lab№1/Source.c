#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int n = quantity_of_bicycles();
	struct bicycle* catalog = memory_catalog(&n);
	enter_mas_structure(&n, catalog);
	int choice_task = 0, go_choice = 0;
	void (**menu)() = NULL;
	menu = (void(**)(struct bicycle *mas,int* n))calloc(4, sizeof(void(*)(struct bicycle* catalog, int* n)));
	if (menu != NULL)
	{
		menu[0] = show_cat;
		menu[1] = del_struct;
		menu[2] = sort_1_field;
		menu[3] = sort_2_field;
		do
		{
			printf("\n\n\n���� �������:\n1.������� �������.\n2.������� ���������.\n3.������������� ������ ������� �� ������ ����\n4.������������� ������ ������� �� ���� �����\\���� �� �������� ��������� ������, �� ������� ����� <5>\n\n�������� �������:");
			check_choice_task(&choice_task);
			if (choice_task == 5)
				return 0;
			system("cls");
			printf("%d ������.\n\n", choice_task);
			menu[choice_task - 1](catalog, &n);
			printf("\n\n������ ��������� � ����?\n1-��\n2-���\n\n�����:");
			check_go_choice(&go_choice);
			system("cls");
		} while (go_choice == 1);
		return 0;
	}
	free_struct(&n, &catalog);
	free(menu);
}