#include "main_func.h"

void seek_IP(hash** table, cache** head, cache** tail, FILE * data, int* size)
{
	char* domain = (char*)calloc(KB, sizeof(char));
	char* id = (char*)calloc(KB, sizeof(char));
	if (domain == NULL || id==NULL)
	{
		fclose(data);
		exit(-1);
	}
	int place = 0;
	if (check_cache_for_ID(&domain, *table, *size, head) == 0 || seek_for_ID_in_file(data, domain, &id) == 0)
	{
		free(domain);
		free(id);
		return;
	}

	unsigned int key = hash_func(*size, domain);

	cache* buf_cache = (*(*table + key)).id;

	if (check_size_of_cache(*head) < CACHE_SIZE)
	{
		add_times_call(*head);
		if (buf_cache == NULL)
		{
			push_cache(head, tail, id, domain);
			(*(*table + key)).id = *head;
		}
		else
		{
			add_dop_element(buf_cache, id, domain, head);
		}
		(*size)++;
		return;
	}
	collision(head, tail, buf_cache, table, id, domain, key, size);
}

void add_data(FILE*data)
{
	char* domain = ( char*)calloc(KB, sizeof(char));
	char* id = (char*)calloc(KB, sizeof(char));
	if (domain == NULL || id==NULL)
	{
		fclose(data);
		exit(-1);
	}

	int choise = 0;
	check_type(&choise);

	if (check_domain_in_data(data, &domain) == 1 || check_ID_in_data(data, &id, choise) == 1)
	{
		free(id);
		free(domain);
		return;
	}
	strcat_s(domain, KB, " ");
	if (choise == 1)
		strcat_s(domain, KB, "IN A");
	else
		strcat_s(domain, KB, "IN CNAME");
	strcat_s(domain, KB, " ");
	strcat_s(domain, KB, id);
	strcat_s(domain, KB, "\n");

	fputs(domain, data);

	free(domain);
	free(id);
	return;
}


void all_domain_names(FILE* data)
{
	rewind(data);
	int size = 0;
	char** domain_arr = (char**)calloc(1, sizeof(char*));
	char* id = (char*)calloc(KB, sizeof(char));
	char* str = (char*)calloc(KB, sizeof(char));
	if (domain_arr == NULL || id ==NULL || str ==NULL)
	{
		fclose(data);
		exit(-1);
	}
	check_ID(&id);
	char* id_buf = id;
	int flag = 1;
	while (!feof(data))
	{
		if (str!=NULL && &str!=NULL && !feof(data))
		{
			find_domain(data, &str, id, &size, &domain_arr);
		}
		if (feof(data))
			break;
	}
	for (int i = 0; i < size; i++)
		printf("%s\n", *(domain_arr + i));
	for (int i = 0; i < size; i++)
		free(*(domain_arr + i));
	free(domain_arr);
	free(str);
	free(id_buf);
}


void look_at_cache(cache* head)
{
	while (head != NULL)
	{
		printf("%s", head->id);
		cache* buf = head->dop;
		while (buf != NULL)
		{
			printf("%s", buf->id);
			buf = buf->dop;
		}
		head = head->prev;
	}
}