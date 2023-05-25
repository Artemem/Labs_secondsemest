#include "Header.h" 

void make_negative(BMPfile* picture, RGBQUAD** palitr)
{
    for (unsigned int i = 0; i < (picture)->dhdr.height; i++)
    {
        for (unsigned int j = 0; j < (picture)->dhdr.width; j++)
        {
            (picture)->data[i][j].blue = MAX_ID - (picture)->data[i][j].blue;
            (picture)->data[i][j].green = MAX_ID - (picture)->data[i][j].green;
            (picture)->data[i][j].red = MAX_ID - (picture)->data[i][j].red;
        }
    }
}


void make_black_and_white(BMPfile* picture, RGBQUAD** palitr)
{
    for (unsigned int i = 0; i < picture->dhdr.height; i++)
    {
        for (unsigned int j = 0; j < picture->dhdr.width; j++)
        {
            int b = (int)picture->data[i][j].blue;
            int g = (int)picture->data[i][j].green;
            int r = (int)picture->data[i][j].red;
            int aver = (b + g + r) / 3;
            picture->data[i][j].blue = aver;
            picture->data[i][j].green = aver;
            picture->data[i][j].red = aver;
        }
    }
}


void make_median_filtration(BMPfile* picture, RGBQUAD** palitr)
{
    int n_times = check_median_choice();
    unsigned char** temp_arr_palitr = NULL;
    pixel**temp_arr = (pixel**)calloc((picture->dhdr.height) - 2, sizeof(pixel*));
    if (temp_arr == NULL)
    {
        free_picture(&picture);
        exit(1);
    }

    for (int i = 0; i < (int)picture->dhdr.height - 2; i++)
    {
        temp_arr[i] = (pixel*)calloc((picture->dhdr.width) - 2, sizeof(pixel));
        if (temp_arr[i] == NULL)
        {
            free_picture(&picture);
            free(temp_arr);
            exit(1);
        }
    }
    for (int n = 0; n < n_times; n++)
    {
        for (unsigned int i = 1; i < picture->dhdr.height - 1; i++)
        {
            for (unsigned int j = 1; j < picture->dhdr.width - 1; j++)
            {
                int sum_b = 0;
                int sum_g = 0;
                int sum_r = 0;

                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        if (a != 0 || b != 0)
                        {
                            sum_b += (int)picture->data[i + a][j + b].blue;
                            sum_g += (int)picture->data[i + a][j + b].green;
                            sum_r += (int)picture->data[i + a][j + b].red;
                        }
                    }
                }
                temp_arr[i - 1][j - 1].blue = (unsigned char)(sum_b / 8);
                temp_arr[i - 1][j - 1].green = (unsigned char)(sum_g / 8);
                temp_arr[i - 1][j - 1].red = (unsigned char)(sum_r / 8);
            }
        }
        for (unsigned int i = 1; i < picture->dhdr.height - 1; i++)
        {
            for (unsigned int j = 1; j < picture->dhdr.width - 1; j++)
            {
                picture->data[i][j].blue = temp_arr[i - 1][j - 1].blue;
                picture->data[i][j].green = temp_arr[i - 1][j - 1].green;
                picture->data[i][j].red = temp_arr[i - 1][j - 1].red;
            }
        }
    }
    for (int i = 0; i < (int)picture->dhdr.height - 2; i++)
    {
        free(temp_arr[i]);
    }
}


void make_gamma_correction(BMPfile* picture, RGBQUAD** palitr)
{
    float ratio = check_gamma();
    /*float temp_arr[MAX_ID+1] = { '\n' };
    for (int i = 0; i < MAX_ID; i++)
    {
        float first_num = (float)((float)i / (float)MAX_ID);
        float sqrt_num = (float)pow(first_num, ratio);
        temp_arr[i] = (float)(sqrt_num * (float)MAX_ID);
    }*/
    for (unsigned int i = 0; i < picture->dhdr.height; i++)
    {
        for (unsigned int j = 0; j < picture->dhdr.width; j++)
        {
            double r = pow((double)picture->data[i][j].red / 255.0, (double)1 / (double)ratio) * 255.0;
            double g = pow((double)picture->data[i][j].green / 255.0, (double)1 / (double)ratio) * 255.0;
            double b = pow((double)picture->data[i][j].blue / 255.0, (double)1 / (double)ratio) * 255.0;
            picture->data[i][j].blue = (unsigned char)b;
            picture->data[i][j].green = (unsigned char)g;
            picture->data[i][j].red = (unsigned char)r;
            /*picture->data[i][j].blue = (unsigned char)temp_arr[(int)picture->data[i][j].blue];
            picture->data[i][j].green = (unsigned char)temp_arr[(int)picture->data[i][j].green];
            picture->data[i][j].red = (unsigned char)temp_arr[(int)picture->data[i][j].red];*/
        }
    }

}