#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h> 
#include <time.h>

#define KB 1024

typedef struct bin_tree
{
	char* Q_or_A;
	struct bin_tree* yes;
	struct bin_tree* no;
}tree;

void show_tree(tree* head);
void free_TREE(tree** head);
void load_tree(tree** head, FILE* text, int place, int check);
void questions(tree** head);
void tree_to_new_data(FILE* data, tree* head);
void start_to_question(tree** head);

void add_answer_and_question_to_tree(char* answer, char* question, tree** head);
void max_place(tree* head, int* n, int place);
void seek_for_str(tree* head, int place, int index, char** str);
void add_log_username(const char* username);
void add_log_answers(const char* answer);