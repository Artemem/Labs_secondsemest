#include "main_func.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    system("cls");
    hash* table = (hash*)calloc(CACHE_SIZE, sizeof(hash));
    if (table == NULL)
        return -1;
    cache* head = NULL;
    cache* tail = NULL;
    FILE* data;
    errno_t err1 = fopen_s(&data, "database.txt", "r+");
    if (err1 != 0)
    {
        printf("������ ������� ����");
        return(1);
    }
    int choice_task = 0;
    int go_choice = 0;
    int size = 0;
    do
    {
         printf("\n\t����\n1.����� IP-�����.\n2.�������� ������ � DNS-����.\n3.����� ��� �������� ����� �� IP.\n4.����������� ���.\n���� �� �������� ��������� ������, �� ������� ����� <5>\n\n�������� �������:");
         check_choice_task(&choice_task);
            
         if (choice_task == 5)
         {
             free_cache(&table, size);
             return 0;
         }
         system("cls");
         printf("%d ������.\n\n", choice_task); 
         switch (choice_task) 
         {
         case 1:
         {
             seek_IP(&table, &head, &tail, data, &size);
             break;
         }
         case 2:
         {
             add_data(data);
             break;
         }
         case 3:
         {   
             all_domain_names(data);
             break;
         }
         case 4:
         {    
             look_at_cache(head);
             break;
         }
         default:
         {    
             fclose(data);
             free_cache(&table, size);
             return 0;
         }
         }
         printf("\n\n������ ��������� � ����?\n1-��\n2-���\n\n�����:"); 
         check_go_choice(&go_choice); 
         system("cls");
    } while (go_choice == 1);
    fclose(data);
    free_cache(&table, size);
    return 0;
}