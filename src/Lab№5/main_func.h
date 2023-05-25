#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h>
#include <math.h>
#define CACHE_SIZE 5
#define KB 1024

struct CACHE
{
	char* id;
	char* domain;
	int times_calls;
	struct CACHE* next;
	struct CACHE* prev;
	struct CACHE* dop;

}typedef cache;
struct HASH
{
	struct CACHE* id;
}typedef hash;
#include "check.h"
#include"hash.h"
#include "file.h"
#include "cache.h"
void seek_IP(hash** table, cache** head, cache** tail, FILE* data, int* size);
void add_data(FILE* data);
void look_at_cache(cache* head);
void all_domain_names(FILE* data);

