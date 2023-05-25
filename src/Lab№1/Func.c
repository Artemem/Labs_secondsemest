#include "Header.h"
int quantity_of_bicycles()
{
    int n = 0;
	printf("Ââåäèòå êîë-âî âåëîñèïåäîâ:");
    while ((scanf_s("%d", &n)) != 1|| getchar() != '\n')
    {
        printf("Îøèáêà.Ïîïðîáóé ñíîâà\nÂâåäèòå êîë-âî âåëîñèïåäîâ:");
        rewind(stdin);
    }
    return n;
}
bicycle* memory_catalog(int n)
{
    bicycle*mas= (bicycle*)calloc(n, sizeof(bicycle));
	return mas;
}
void enter_mas_structure(int n, bicycle* mas)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nÂâåäèòå ãîä âûïóñêà %d âåëîñèïåäà:", i + 1);
		checker(mas, i, 1);
		//printf("Ââåäèòå öâåò %d âåëîñèïåäà:", i + 1);
		checker(mas, i, 2);
		printf("Ââåäèòå êîä êëàññà %d âåëîñèïåäà (Ãîðíûé[0], Òðþêîâîé[1], Ãîðîäñêîé[2], Ãèáðèäíûé[3]):", i + 1);
		checker(mas, i, 3);
	}
}

void checker(bicycle* mas, int i, int k)
{
	if (k == 1)
	{
		while ((scanf_s("%d", &mas[i].year)) != 1 || mas[i].year>2024 || mas[i].year < 2010 || getchar() != '\n')
		{
			printf("Îøèáêà. Ïîïðîáóé ñíîâà\nÂâåäèòå ãîä âûïóñêà %d âåëîñèïåäà:", i+1);
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
		printf("Ââåäèòå öâåò %d âåëîñèïåäà:", i + 1);
		while(scanf_s("%s", mas[i].colour, 1024) != 1 || strlen(mas[i].colour) < 3)
		{
			printf("Îøèáêà! Ïîïðîáóéòå ñíîâà!\nÂâåäèòå öâåò %d âåëîñèïåäà:", i + 1);
			rewind(stdin);
		}
	}
	if (k == 3)
	{
		while ((scanf_s("%d", &mas[i].class)) < 1 || mas[i].class != 0 && mas[i].class != 1 && mas[i].class != 2 && mas[i].class != 3 || getchar() != '\n')
		{
			printf("Îøèáêà.Ïîïðîáóé ñíîâà\nÂâåäèòå êîä êëàññà %d âåëîñèïåäà (Ãîðíûé[0], Òðþêîâîé[1], Ãîðîäñêîé[2], Ãèáðèäíûé[3]):", i + 1);
			rewind(stdin);
		}
	}
}
void check_choice_task(int* ch)
{
	while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 && *ch != 3 && *ch !=4 && *ch!=5|| getchar() != '\n')
	{
		printf("Îøèáêà.Ïîïðîáóé ñíîâà\nÂûáåðèòå çàäàíèå:");
		rewind(stdin);
	}
}
void check_go_choice(int* ch)
{
	while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 || getchar() != '\n')
	{
		printf("Îøèáêà.Ïîïðîáóé ñíîâà\nÎòâåò:");
		rewind(stdin);
	}
}
void show_cat(const bicycle* mas,const int* n)
{
	printf("Êàòàëîã:\n\nÊëàññ:\t\t\tÃîä:\t\tÖâåò:\n");
	const static char* ForWhat[] = { "Ãîðíûé", "Òðþêîâîé", "Ãîðîäñêîé", "Ãèáðèäíûé" }; //"Ãîðíûé", "Òðþêîâîé", "Ãîðîäñêîé", "Ãèáðèäíûé"
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
	printf("Êàêîé âåëîñèïåä âû õîòèòå óäàëèòü?\n Âàø âûáîð(1-%d)", *n);
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
		printf("Îøèáêà. Ïîïðîáóéòå ñíîâà\nÂàø âûáîð(1-%d)", n);
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
	printf("Ïî êàêîìó ïàðàìåòðó âû õîòèòå îòñîðòèðîâàòü êàòàëîã (Êëàññ[1], Ãîä[2], Öâåò[3])?\nÂàø âûáîð:");
	int ch_1 = 0;
	check_choice_sort(&ch_1);
    sort_1(mas, *n, ch_1);
	show_cat(mas, n);
}
void check_choice_sort(int* ch)
{
	while ((scanf_s("%d", ch)) != 1 || *ch != 1 && *ch!=2 && *ch!=3 || getchar() != '\n')
	{
		printf("Îøèáêà. Ïîïðîáóéòå ñíîâà\nÂàø âûáîð");
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
	printf("Ïî êàêèì äâóì ïàðàìåòðàì âû õîòèòå îòñîðòèðîâàòü êàòàëîã (Êëàññ[1], Ãîä[2], Öâåò[3])?\n\nÏåðâûé ïàðàìåòð:");
	int ch_1 = 0;
	int	ch_2 = 0;
	check_choice_sort(&ch_1);
	printf("Âòîðîé ïàðàìåòð:");
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
			printf("Äâà ðàçà ïî îäíîìó ïàðàìåòðó íåëüçÿ ñîðòèðîâàòü\n");
		printf("Âòîðîé ïàðàìåòð:");
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
