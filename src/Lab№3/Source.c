#include "Header.h" 

int main()
{
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    system("cls");
    char* file_name = enter_file_name();
    FILE* file;
    errno_t err = fopen_s(&file, file_name, "rb");
    if (err != 0)
    {
        printf("Нельзя открыть файл");
        free(file_name);
        return(1);
    }
    RGBQUAD* palitr = NULL;
    BMPfile* picture = load_picture(file, &palitr);
    fclose(file);
    int choice_task = 0;
    int go_choice = 0;

    void(**menu)(BMPfile*, RGBQUAD**) = (void(**)(BMPfile*, RGBQUAD**))calloc(4, sizeof(void(*)(BMPfile*, RGBQUAD**)));
    if (menu != NULL)
    {
        menu[0] = &negative;
        menu[1] = &black_and_white;
        menu[2] = &median_filtration;
        menu[3] = &gamma_correction;
        do
        {
            printf("\n\n\nМеню преобразования фотографии:\n1.Перевести в негатив.\n2.Перевести в черно-белое.\n3.Реализовать медианную фильтрацию\n4.Реализовать гамма-коррекцию.\nЕсли вы захотите закончить работу, то введите цифру <5>\n\nВыберите задание:");
            check_choice_task(&choice_task);
            if (choice_task == 5)
            {
                free(menu);
                return 0;
            }
            system("cls");
            printf("%d задача.\n\n", choice_task);
            menu[choice_task - 1](picture, palitr);
            printf("\n\nХочешь вернуться в меню?\n1-Да\n2-Нет\n\nОтвет:");
            check_go_choice(&go_choice);
            system("cls");
        } while (go_choice == 1);
    }
    free(menu);
    return 0;
}