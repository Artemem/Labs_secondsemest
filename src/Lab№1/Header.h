#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <string.h>
#include <locale.h>
int quantity_of_bicycles();
enum tip
{
	MOUNTAIN = 0,
	STUNT,
	URBAN,
	HYBRID
};
typedef struct bicycle
{
	int year;
	char* colour;
	enum tip class;
}bicycle;
bicycle* memory_catalog(int n);
void enter_mas_structure(int n,bicycle* mas);
void show_cat(bicycle const* mas, const int* n);
void del_struct(bicycle* mas, int* n);
void sort_1_field(bicycle* mas, int* n);
void sort_2_field( bicycle* mas, int* n);
void check_choice_task(int* ch);
void check_go_choice(int* ch);
void checker(bicycle* mas, int i, int k);
void check_choice_sort(int* ch);
void check_del_str(int* x, int n);
void del(bicycle** mas, int x, int* n);
void sort_1_field(bicycle* mas, int* n);
void check_2_choices_sort(int ch_1, int* ch_2);
int text_check(const char* mas_1, char const* mas_2);
int int_check(int a, int b);
int variants(int ch_1, int flag, bicycle* mas);
void free_struct(int n, bicycle** mas);
void sort_2(bicycle* mas, int n, int ch_1, int ch_2);
void sort_1(bicycle* mas, int n, int ch_1);
//void class_html(FILE* file, struct bicycle* mas);
//void year_html(FILE* file, struct bicycle* mas);
//void name_html(FILE* file, struct bicycle* mas);
//void html_file(struct bicycle* mas);