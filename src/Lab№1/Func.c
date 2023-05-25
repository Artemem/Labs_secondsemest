#include "Header.h"
int quantity_of_bicycles()
{
    int n = 0;
	printf("Введите кол-во велосипедов:");
    while ((scanf_s("%d", &n)) != 1|| getchar() != '\n')
    {
        printf("Ошибка.Попробуй снова\nВведите кол-во велосипедов:");
        rewind(stdin);
    }
    return n;
}
bicycle* memory_catalog(int n)
{
    bicycle*mas= (struct bicycle*)calloc(n, sizeof(bicycle));
	return mas;
}
void enter_mas_structure(int n, bicycle* mas)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nВведите год выпуска %d велосипеда:", i + 1);
		checker(mas, i, 1);
		//printf("Введите цвет %d велосипеда:", i + 1);
		checker(mas, i, 2);
		printf("Введите код класса %d велосипеда (Горный[0], Трюковой[1], Городской[2], Гибридный[3]):", i + 1);
		checker(mas, i, 3);
	}
}

void checker(bicycle* mas, int i, int k)
{
	if (k == 1)
	{
		while ((scanf_s("%d", &mas[i].year)) != 1 || mas[i].year>2024 || mas[i].year < 2010 || getchar() != '\n')
		{
			printf("Ошибка. Попробуй снова\nВведите год выпуска %d велосипеда:", i+1);
			rewind(stdin);
		}
	}
	if (k == 2)
	{
		mas[i].colour = (char*)calloc(1024, sizeof(char));
		if (mas[i].colour == NULL)
		{
			exit(-1);
		}
		printf("Введите цвет %d велосипеда:", i + 1);
		while(scanf_s("%s", mas[i].colour, 1024) != 1 || strlen(mas[i].colour) < 3)
		{
			printf("Ошибка! Попробуйте снова!\nВведите цвет %d велосипеда:", i + 1);
			rewind(stdin);
		}
	}
	if (k == 3)
	{
		while ((scanf_s("%d", &mas[i].class)) < 1 || mas[i].class != 0 && mas[i].class != 1 && mas[i].class != 2 && mas[i].class != 3 || getchar() != '\n')
		{
			printf("Ошибка.Попробуй снова\nВведите код класса %d велосипеда (Горный[0], Трюковой[1], Городской[2], Гибридный[3]):", i + 1);
			rewind(stdin);
		}
	}
}
void check_choice_task(int* ch)
{
	while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 && *ch != 3 && *ch !=4 && *ch!=5|| getchar() != '\n')
	{
		printf("Ошибка.Попробуй снова\nВыберите задание:");
		rewind(stdin);
	}
}
void check_go_choice(int* ch)
{
	while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 || getchar() != '\n')
	{
		printf("Ошибка.Попробуй снова\nОтвет:");
		rewind(stdin);
	}
}
void show_cat(const bicycle* mas,const int* n)
{
	printf("Каталог:\n\nКласс:\t\t\tГод:\t\tЦвет:\n");
	const static char* ForWhat[] = { "Горный", "Трюковой", "Городской", "Гибридный" }; //"Горный", "Трюковой", "Городской", "Гибридный"
	for (int i = 0; i < *n; i++)
	{
		printf("%d. ", i + 1);
		printf("%s", ForWhat[mas[i].class]);
		printf("\t\t%d\t\t", mas[i].year);
		printf("%s", mas[i].colour);
		printf("\n");
	}
}
void del_struct(bicycle* mas, int* n)
{
	printf("Какой велосипед вы хотите удалить?\n Ваш выбор(1-%d)", *n);
	int x = 0;
	check_del_str(&x, *n);
	del(&mas, x, n);
	system("cls");
	show_cat(mas, n);
}
void check_del_str(int* x, int n)
{
	while ((scanf_s("%d", x)) != 1 || *x < 1 || *x>n || getchar() != '\n')
	{
		printf("Ошибка. Попробуйте снова\nВаш выбор(1-%d)", n);
		rewind(stdin);
	}
}
void del(bicycle** mas, int x, int* n)
{
	free((*mas+x-1)->colour);
	int i = x;
	while (i < *n)
	{
		*(*mas + i - 1) = *(*mas + i);
		i++;
	}
	(*n)--;
    bicycle* store = (bicycle*)realloc(*mas, (*n) * sizeof(bicycle));
	if (store != NULL)
	{
		*mas = store;
	}
}
void sort_1_field(bicycle* mas, int* n)
{
	printf("По какому параметру вы хотите отсортировать каталог (Класс[1], Год[2], Цвет[3])?\nВаш выбор:");
	int ch_1 = 0;
	check_choice_sort(&ch_1);
    sort_1(mas, *n, ch_1);
	show_cat(mas, n);
}
void check_choice_sort(int* ch)
{
	while ((scanf_s("%d", ch)) != 1 || *ch != 1 && *ch!=2 && *ch!=3 || getchar() != '\n')
	{
		printf("Ошибка. Попробуйте снова\nВаш выбор");
		rewind(stdin);
	}
}
void sort_1(bicycle* mas,int n, int ch_1)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (variants(ch_1, j, mas) == 1)
			{
				bicycle temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}
void sort_2(bicycle* mas, int n, int ch_1, int ch_2)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
		    if (variants(ch_1, j, mas) == 1 || (variants(ch_1, j, mas) == 2 && variants(ch_2, j, mas) == 1))
		    {
				bicycle temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
		    }
		}
	}
}
int variants(int ch_1, int flag, bicycle* mas)
{
	switch (ch_1)
	{
	case 1:
		return int_check(mas[flag].class, mas[flag + 1].class);
	case 2:
		return int_check(mas[flag].year, mas[flag + 1].year);
	case 3:
		return text_check(mas[flag].colour, mas[flag + 1].colour);
	default:
		return 3;
	}
}
int text_check(const char* mas_1, char const* mas_2)
{
	if (strcmp(mas_1,mas_2)>0)
		return 1;
	if (strcmp(mas_1, mas_2) < 0)
		return 0;
	return 2;
}
int int_check(int a, int b)
{
	if (a > b)
		return 1;
	if (a == b)
		return 2;
	return 3;
}
void sort_2_field(bicycle* mas, int* n)
{
	printf("По каким двум параметрам вы хотите отсортировать каталог (Класс[1], Год[2], Цвет[3])?\n\nПервый параметр:");
	int ch_1 = 0;
	int	ch_2 = 0;
	check_choice_sort(&ch_1);
	printf("Второй параметр:");
	check_2_choices_sort(ch_1, &ch_2);
	sort_2(mas, *n, ch_1, ch_2);
	system("cls");
	show_cat(mas,n);
}
void check_2_choices_sort(int const ch_1, int* ch_2)
{
	while ((scanf_s("%d", ch_2)) != 1 || getchar() != '\n' || *ch_2 < 1 || *ch_2 > 3 || ch_1 == *ch_2)
	{
		if (ch_1 == *ch_2)
			printf("Два раза по одному параметру нельзя сортировать\n");
		printf("Второй параметр:");
		rewind(stdin);
	}
}
void free_struct(int const n, bicycle** mas)
{

	for (int i = 0; i < n; i++)
	{
		free((*mas + i)->colour);
	}
	free(*mas);
}