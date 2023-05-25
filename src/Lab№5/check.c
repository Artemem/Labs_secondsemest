#include "check.h"



void check_ID(char** id)
{
	printf("Введите IP-адрес:");
	while (scanf_s("%s", *id, KB) != 1 || (check_validation(*id) == 1))
	{
		printf("\nОшибка. Возможен неправильный формат IP. Попробуй снова\nВведите IP-адрес:");
		rewind(stdin);
	}
}

int check_dubl_ip()
{
	printf("Этот IP-адрес уже находится в базе данных.\nХотите дублировать IP?\n");
	char* answer = (char*)calloc(KB, sizeof(char));
	if (answer == NULL)
		exit(1);
	printf("\nОтвет(Да/Нет):");
	while (scanf_s("%s", answer, KB) != 1 || ((answer)[0] != 'Д' && (answer)[0] != 'д' && (answer)[0] != 'Н' && (answer)[0] != 'н') || ((answer)[1] != 'А' && (answer)[1] != 'а' && (answer)[1] != 'Е' && (answer)[1] != 'е' && (answer)[2] != 'Т' && (answer)[2] != 'т') || strlen(answer) < 2 || strlen(answer) > 3)
	{
		printf("Ошибка.Попробуй снова\nХотите ввести ещё раз IP?(Да/Нет):");
		rewind(stdin);
	}
	if (answer[0] == 'Д' || answer[0] == 'д')
	{
		return 0;
	}
	else
		return 1;
}

int checker_IP_v_4(const char* id)
{
	for (int i = 0; i < strnlen_s(id, KB); i++)
	{
		if (*(id + i) != '.' && !(*(id + i) <= '9' && *(id + i) >= '0'))
			return 1;
	}

	int number = 0;

	int place = 0;

	char* storer = (char*)calloc(4, sizeof(char));
	if (storer == NULL)
		exit(-1);

	for (int i = 0; i < 4; i++)
	{
		int j = 0;

		while (*(id + place) != '.' && *(id + place) != '\0')
		{
			*(storer + j) = *(id + place);
			j++;
			place++;
		}
		place++;
		if (*storer == '0' && strnlen_s(storer, KB) == 1)
		{
			free(storer);
			return 1;
		}
		for (int a = (int)strnlen_s(storer, KB), b = 0; a > 0; a--, b++)
		{
			number += (*(storer + (a - 1)) - '0') * (int)pow(10, (int)b);
		}

		if (!(number >= 0 && number <= 255))
		{
			free(storer);
			return 1;
		}

		number = 0;

		for (int c = (int)strnlen_s(storer, 4) - 1; c >= 0; c--)
			*(storer + c) = '\0';
	}
	free(storer);
	return 0;
}

int checker_IP_v_6(const char* id)
{
	for (int i = 0; i < strnlen_s(id, KB); i++)
	{
		if (*(id + i) != ':' && !(*(id + i) <= '9' && *(id + i) >= '0') && !(*(id + i) <= 'Z' && *(id + i) >= 'A') && !(*(id + i) <= 'z' && *(id + i) >= 'a'))
			return 1;
	}
	int checker = 0;
	for (int i = 0; i < strnlen_s(id, KB); i++)
	{
		if (*(id + i) != ':')
			checker++;

		if (*(id + i) == ':')
			checker = 0;

		if (checker >= 5)
			return 1;
	}
	return 0;
}

int check_validation(char* id)
{
	int checker_1_point = 0;
	int checker_2_point = 0;
	for (int i = 1; i < strnlen_s(id, KB); i++)
	{
		if (*(id + i) == '.' && (*(id + i - 1) <= '9' && *(id + i - 1) >= '0') && (*(id + i + 1) <= '9' && *(id + i + 1) >= '0'))
		{
			checker_1_point++;
		}
		if (*(id + i) == ':' && ((*(id + i - 1) <= '9' && *(id + i - 1) >= '0') || (*(id + i - 1) <= 'Z' && *(id + i - 1) >= 'A') || (*(id + i - 1) <= 'z' && *(id + i - 1) >= 'a') || (*(id + i - 1) == ':')) && ((*(id + i + 1) <= '9' && *(id + i + 1) >= '0') || (*(id + i + 1) <= 'Z' && *(id + i + 1) >= 'A') || (*(id + i + 1) <= 'z' && *(id + i + 1) >= 'a') || (*(id + i - 1) == ':')))
		{
			checker_2_point++;
		}
	}
	if ((checker_1_point == 3 && checker_IP_v_4(id) == 0) || ((checker_2_point >= 2) && checker_IP_v_6(id) == 0))
	{
		return 0;
	}
	return 1;
}

int check_dubl_domain()
{
	printf("Это доменное имя уже есть в файле\nХотите дублировать доменное имя?");
	char* answer = (char*)calloc(KB, sizeof(char));
	if (answer == NULL)
		exit(-1);
	printf("\nОтвет(Да/Нет):");
	while (scanf_s("%s", answer, KB) != 1 || ((answer)[0] != 'Д' && (answer)[0] != 'д' && (answer)[0] != 'Н' && (answer)[0] != 'н') || ((answer)[1] != 'А' && (answer)[1] != 'а' && (answer)[1] != 'Е' && (answer)[1] != 'е' && (answer)[2] != 'Т' && (answer)[2] != 'т') || strlen(answer) < 2 || strlen(answer) > 3)
	{
		printf("Ошибка.Попробуй снова\nВведите правильный ответ(Да/Нет):");
		rewind(stdin);
	}
	if (answer[0] == 'Д' || answer[0] == 'д')
	{
		return 0;
	}
	else
		return 1;
}

void check_type(int* x)
{
	printf("Введите тип записи в DNS-файле(1/2):");
	while ((scanf_s("%d", x)) != 1 || *x < 1 || *x>2 || getchar() != '\n')
	{
		printf("Ошибка.Попробуйте снова\nОтвет:");
		rewind(stdin);
	}
}

int check_type_of_str(const char* str, unsigned int domain_size)
{
	int first_type_cheker = 0;
	int second_type_cheker = 0;

	for (int i = domain_size + 1, j = 0; j < (int)strnlen_s("IN CNAME", KB); j++, i++)
	{
		if ((j < (int)strnlen_s("IN A", KB)) && *(str + i) == "IN A"[j])
			first_type_cheker++;

		if (*(str + i) == "IN CNAME"[j])
			second_type_cheker++;
	}

	if (first_type_cheker == (int)strnlen_s("IN A", KB))
		return 1;
	else if (second_type_cheker == (int)strnlen_s("IN CNAME", KB))
		return 2;
	else
		return 0;
}

void check_choice_task(int* ch)
{
	while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 && *ch != 3 && *ch != 4 && *ch != 5 || getchar() != '\n')
	{
		printf("Ошибка.Попробуйте снова\nВыберите задание:");
		rewind(stdin);
	}
}
void check_go_choice(int* ch)
{
	while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 || getchar() != '\n')
	{
		printf("Ошибка.Попробуйте снова\nОтвет:");
		rewind(stdin);
	}
}