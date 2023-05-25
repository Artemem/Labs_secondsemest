#pragma once
#include "hash.h"
#include "main_func.h"
void check_ID(char** id);

int check_dubl_ip();

int checker_IP_v_4(const char* id);

int checker_IP_v_6(const char* id);

int check_validation(char* id);

int check_dubl_domain();

void check_type(int* x);

int check_type_of_str(const char* str, unsigned int domain_size);
void check_choice_task(int* ch);
void check_go_choice(int* ch);