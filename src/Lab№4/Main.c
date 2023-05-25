#include "tree.h"
#include "strings.h"
#include "check.h"


int main()
{
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    system("cls");
    FILE* data;
    errno_t err1 = fopen_s(&data, "data.txt", "r+");
    if (err1 != 0)
    {
        printf("Нельзя открыть файл");
        return(1);
    }
    tree* head = NULL;
    int check = check_str_in_text(data);
    load_tree(&head, data, 1, check );
    fclose(data);
    int go_choice = 0;
    do 
    {
        start_to_question(&head);
        printf("\n\nХочешь попробовать ещё раз?\n");
        check_go_choice(&go_choice);
        system("cls");
    } while (go_choice == 1);
    /*show_tree(head);*/
    FILE* new_data;
    errno_t err2 = fopen_s(&new_data, "data.txt", "w+");
    if (err2 != 0)
    {
        printf("Нельзя открыть файл");
        return(1);
    }
    tree_to_new_data(new_data, head);
    free_TREE(&head);
}