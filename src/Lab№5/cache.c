#include "cache.h"

void push_cache(cache** head, cache** tail, char* id, char* domain)
{
	cache* buf = malloc(sizeof(cache));
	if (buf == NULL)
		exit(-1);

	buf->id = id;
	buf->domain = domain;
	buf->times_calls = 1;

	if (*tail == NULL)
	{
		*tail = buf;
		*head = buf;
		buf->next = NULL;
		buf->prev = NULL;
		buf->dop = NULL;
	}
	else
	{
		buf->prev = *head;
		buf->next = NULL;
		buf->dop = NULL;
		(*head)->next = buf;
		*head = buf;
	}
}


void add_dop_element(cache* dop_element, char* id, char* domain, cache** head)
{
	cache* buf = malloc(sizeof(cache));
	if (buf == NULL)
		exit(-1);
	buf->id = id;
	buf->domain = domain;
	buf->times_calls = 1;
	buf->prev = NULL;
	buf->next = NULL;
	if (dop_element->prev != NULL)
	{
		dop_element->prev->next = buf;
		buf->prev = dop_element->prev;
		dop_element->prev = NULL;
	}
	if (dop_element->next != NULL)
	{
		dop_element->next->prev = buf;
		buf->next = dop_element->next;
		dop_element->next = NULL;
	}
	buf->dop = dop_element;
	if (buf->next != NULL)
	{
		buf->next->prev = buf->prev;
	}
	if (buf->prev != NULL) {
		buf->prev->next = buf->next;
	}
	buf->next = NULL;
	buf->prev = *head;
	(*head)->next = buf;
	*head = buf;
}
void collision(cache** head, cache** tail, cache** buf_cache, hash** table, char* id, char* domain, int key, int* size)
{
	cache* buf_for_tail_dop = NULL;
	if (*tail == NULL)
	{
		exit(-1);
	}
	if ((*tail)->dop != NULL)
	{
		buf_for_tail_dop = (*tail)->dop;

		(*head)->next = (*tail)->dop;
		(*tail)->dop->prev = *head;
		*head = (*tail)->dop;

		cache* cache_tmp = *tail;
		*tail = (*tail)->next;
		free(cache_tmp->domain);
		free(cache_tmp->id);
		free(cache_tmp);
		(*tail)->prev = NULL;

		*buf_cache = *head;
		cache* element = find_place(*buf_cache);

		if (element = *tail)
		{
			(*tail)->prev = *buf_cache;
			*head = (*buf_cache)->prev;
			(*head)->next = NULL;
			(*buf_cache)->next = (*tail);
			*tail = *buf_cache;
			(*buf_cache)->prev = NULL;
		}
		else if (element != (*head))
		{
			*head = (*buf_cache)->prev;
			(*head)->next = NULL;
			element->prev->next = *buf_cache;
			(*buf_cache)->prev = element->prev;
			element->prev = *buf_cache;
			(*buf_cache)->next = element;
		}

		(*(*table + hash_func(*size, buf_for_tail_dop->domain))).id = buf_for_tail_dop;
		add_times_call(*head);
		if ((*(*table + key)).id == NULL)
			push_cache(head, tail, id, domain);
		else
			add_dop_element(*buf_cache, id, domain, head);
	}
	else
	{
		if ((*(*table + key)).id == *tail)
		{
			free((*tail)->domain);
			free((*tail)->id);
			cache* buf = *tail;
			*tail = (*tail)->next;
			(*tail)->prev = NULL;
			free(buf);
			add_times_call(*head);
			push_cache(head, tail, id, domain);

			(*(*table + key)).id = *head;
		}
		else
		{
			(*(*table + hash_func(*size, (*tail)->domain))).id = NULL;

			free((*tail)->domain);
			free((*tail)->id);
			cache* buf = *tail;
			*tail = (*tail)->next;
			(*tail)->prev = NULL;
			free(buf);
			add_times_call(*head);
			add_dop_element((*(*table + key)).id, id, domain, head);
		}
	}
}

int check_size_of_cache(cache* head)
{
	int size = 0;
	while (head != NULL)
	{
		cache* buf = head->dop;
		while (buf != NULL)
		{
			size++;
			buf = buf->dop;
		}
		size++;
		head = head->prev;
	}
	return size;
}
void add_times_call(cache* head)
{
	while (head != NULL)
	{
		head->times_calls++;
		if (head->dop != NULL)
		{
			add_times_call_column(head->dop);
		}
		head = head->prev;
	}
}

void add_times_call_column(cache* head)
{
	while (head != NULL)
	{
		head->times_calls++;

		head = head->dop;
	}
}

int check_cache_for_ID(char** domain, hash* table, int size, cache** head)
{
	printf("Введите доменное имя:");
	while (scanf_s("%s", (*domain), KB) != 1 || strlen(*domain) < 3)
	{
		printf("\nОшибка.Попробуй снова\nВведите правильное доменное имя:");
		rewind(stdin);
	}
	int key = hash_func(size, *domain);
	cache* buf = (*(table + key)).id;
	cache* buf2 = buf;
	int flag = 0;
	while (buf != NULL)
	{
		if (strncmp(*domain, buf->domain, KB) == 0)
		{
			printf("Вот ваш айди: %s", buf->id);
			buf->times_calls = 1;
			shift_cache(head, &buf, &buf2, domain, flag);
			add_times_call((*head)->prev);
			return 0;
		}
		buf = buf->dop;
		flag++;
	}
	return 1;
}

void shift_cache(cache** head, cache** buf, cache** buf2, char** domain, int flag)
{
	if (strcmp((*head)->domain, *domain) != 0)
	{
		if (flag == 0)
		{
			(*buf)->next->prev = (*buf)->prev;
			if ((*buf)->prev != NULL) {
				(*buf)->prev->next = (*buf)->next;
			}
			(*buf)->next = NULL;
			(*buf)->prev = *head;
			(*head)->next = *buf;
			*head = *buf;
		}
		else
		{
			if ((*buf2)->next != NULL)
			{
				(*buf2)->next->prev = (*buf2)->prev;
			}
			if ((*buf2)->prev != NULL) {
				(*buf2)->prev->next = (*buf2)->next;
			}
			while ((*buf2)->dop != *buf)
			{
				(*buf2) = (*buf2)->dop;
			}
			(*buf2)->dop = (*buf)->dop;
			(*buf)->dop = *buf2;
			(*buf)->next = NULL;
			(*buf)->prev = *head;
			(*head)->next = *buf;
			*head = *buf;
		}

	}
}
cache* find_place(cache* element)
{
	while (element->prev != NULL && (element->prev->times_calls) < (element->times_calls))
		element = element->prev;
	return element;
}

void free_cache(hash** table, int size)
{
	cache* buf = NULL;
	for (int i = 0; i < size; i++)
	{
		while ((*(*table + i)).id != NULL)
		{
			buf = (*(*table + i)).id;
			(*(*table + i)).id = (*(*table + i)).id->dop;
			free(buf->domain);
			free(buf->id);
			free(buf);
		}

	}
}