#include "hash.h"






unsigned int find_sum_of_symb(const char* str)
{
	unsigned int key = 0;
	for (int i = 0; i < strnlen_s(str, KB); i++)
	{
		key += (long long)(*(str + i));
	}
	return key;
}


unsigned int hash_func(int size, const char* str)
{
	unsigned int value_for_key = find_sum_of_symb(str);

	return value_for_key % CACHE_SIZE;
}