#include "file.h"


void find_domain(FILE* data, char** str, char* id, int* size, char*** domain_arr)
{
	char* buf = (char*)calloc(KB, sizeof(char));
	fgets(buf, KB, data);
	if (strlen(buf) < 1)
	{
		return;
	}
	else
	{
		*str = buf;
	}
	if (*str == NULL || *str == "\n" || *str == "\0")
		return;
	int i = (int)strnlen_s(*str, KB);
	int cnt = 0;
	while (*(*str + i) != ' ')
	{
		i--;
	}
	i++;
	while (*(*str + i) != '\0' && *(*str + i) != '\n' && (*(id + cnt) == *(*str + i)))
	{
		i++;
		cnt++;
	}
	int length = i;
	i = 0;

	if ((cnt == (int)strnlen_s(id, KB)) && (*(*str + length) == '\0' || *(*str + length) == '\n'))
	{
		(*size)++;

		char* domain = (char*)calloc(KB, sizeof(char));
		if (domain == NULL)
		{
			for (int j = 0; j < *size; j++)
				free(*(*domain_arr + j));
			free(*domain_arr);
			free(*str);
			free(id);
			exit(-1);
		}
		while (*(*str + i) != ' ')
		{
			*(domain + i) = *(*str + i);
			i++;
		}
		*(domain + i) = '\0';

		if (*size != 1)
		{
			char** buf_arr = (char**)realloc(*domain_arr, *size * sizeof(char*));
			if (buf_arr != NULL)
				*domain_arr = buf_arr;
		}
		*(*domain_arr + (*size - 1)) = domain;
	}
}

int check_ID_in_data(FILE* data, char** id, int choice)
{
	if (choice == 1)
		printf("Введите IP-адрес:");
	else
		printf("Введите второе доменное имя");
	while (scanf_s("%s", *id, KB) != 1 || (choice == 1 && check_validation(*id) == 1) || strlen(*id) < 3)
	{
		printf("\nОшибка.Попробуй снова\n");
		if (choice == 1)
			printf("Введите IP-адрес:");
		else
			printf("Введите второе доменное имя:");
		rewind(stdin);
	}
	rewind(data);

	char* str = (char*)calloc(KB, sizeof(char));
	if (str == NULL)
	{
		return 1;
	}

	while (!feof(data))
	{
		fgets(str, KB, data);

		int i = 0;

		while (*(str + i) != ' ')
		{
			i++;
		}
		if (choice = 1)
		{
			i += (int)strnlen_s("IN A", KB) + 2;
		}
		else
		{
			i += (int)strnlen_s("IN CNAME", KB) + 2;
		}
		int counter = 0;

		while (*(str + i) != '\n')
		{
			if (*(str + i) == *(*id + counter))
			{
				counter++;
				i++;
			}
			else
				break;
		}
		if (counter == strnlen_s(*id, KB))
		{
			if (check_dubl_ip() == 0)
				return 0;
			else
				return 1;
			free(str);
		}
	}
	free(str);
	return 0;
}

int check_domain_in_data(FILE* data, char** domain)
{
	printf("Введите доменное имя:");
	while (scanf_s("%s", (*domain), KB) != 1 || strlen(*domain) < 2)
	{
		printf("\nОшибка.Попробуй снова\nВведите правильное доменное имя:");
		rewind(stdin);
	}
	rewind(data);

	char* str = (char*)calloc(KB, sizeof(char));
	if (str == NULL)
	{
		exit(-1);
	}

	while (!feof(data))
	{
		fgets(str, KB, data);

		if (strncmp(*domain, str, strnlen_s(*domain, KB)) == 0)
		{
			free(str);
			if (check_dubl_domain() == 0)
				return 0;
			else
				return 1;
		}
	}
	free(str);
	return 0;
}

int seek_for_ID_in_file(FILE* data, const char* domain, char** id)
{
	rewind(data);
	char* str = (char*)calloc(KB, sizeof(char));
	char* domain_buf = (char*)calloc(KB, sizeof(char));
	if (str == NULL || domain_buf == NULL)
	{
		free(*id);
		fclose(data);
		exit(-1);
	}

	strcpy_s(domain_buf, KB, domain);

	int flag = 1;
	int type = 0;

	if (seek_str(domain_buf, &str, data) == 0)
	{
		printf("Не хватает данных в файле!");
		free(str);
		free(domain_buf);
		return 0;
	}
	type = check_type_of_str(str, (int)strnlen_s(domain_buf, KB));
	switch (type)
	{
	case 0:
	{
		printf("Неправильно записан тип строки в файле!");
		free(str);
		free(domain_buf);
		return 0;
	}
	case 1:
	{
		int i = 0;
		int j = (int)strnlen_s(domain_buf, KB) + (int)strnlen_s("IN A", KB) + 2;

		if (j > strnlen_s(str, KB) - 1 || j < 0)
			return 0;

		while (*(str + j) != '\0')
		{
			*(*id + i) = *(str + j);
			i++;
			j++;
		}

		*(*id + i) = '\0';
		printf("Ваш IP - %s", *id);
		break;
	}
	case 2:
	{
		int i = 0;
		int j = (int)strnlen_s(domain_buf, KB) + (int)strnlen_s("IN CNAME", KB) + 2;

		char* domain_buf_buf = (char*)realloc(domain_buf, KB * sizeof(char));
		if (domain_buf_buf != NULL)
			domain_buf = domain_buf_buf;

		while (*(str + j) != '\0')
		{
			if ((domain_buf + i) != NULL && (str + j) != NULL)
			{
				*(domain_buf + i) = *(str + j);

				i++;
				j++;
			}
		}
		if ((domain_buf + (i - 1)) != NULL && i >= 1)
			*(domain_buf + (i - 1)) = '\0';
		seek_for_ID_in_file(data, domain_buf, id);
		break;

	}
	default:
	{
		free(domain_buf);
		free(str);
		return 0;
	}
	}
	free(str);
	free(domain_buf);
	return 1;
}
int seek_str(const char* domain, char** str, FILE* data)
{
	rewind(data);

	while (!feof(data))
	{
		fgets(*str, KB, data);

		if (strncmp(*str, domain, (int)strnlen_s(domain, KB)) == 0)
			return 1;
	}
	return 0;
}
