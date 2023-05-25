#include "File_picture.h"

BMPfile* load_picture(FILE* file, RGBQUAD** palitr)
{
    BMPfile* picture = (BMPfile*)malloc(sizeof(BMPfile));
    if (picture != NULL)
    {
        fread(&picture->bhdr, sizeof(BMPheader), 1, file);
        check_ID(&picture);
        fread(&picture->dhdr, sizeof(DIBheader), 1, file);
        picture->data = (pixel**)calloc(picture->dhdr.height, sizeof(pixel*));
        if (picture->data != NULL)
        {
            for (int i = 0; i < (int)picture->dhdr.height; i++)
            {
                picture->data[i] = (pixel*)calloc(picture->dhdr.width, sizeof(pixel));
                if (picture->data[i] == NULL)
                {
                    free(picture);
                    free(palitr);
                    exit(1);
                }
            }
        }
        make_pixel_array(file, &picture);
    }
    return picture;
}
void make_pixel_array(FILE* file, BMPfile** picture)
{
    fseek(file, (*picture)->bhdr.pixel_offset, SEEK_SET);

    int row_padding = (4 - ((*picture)->dhdr.width % 4)) % 4;

    for (unsigned int i = 0; i < (*picture)->dhdr.height; i++)
    {
        for (unsigned int j = 0; j < (*picture)->dhdr.width; j++)
        {
            fread(&(*picture)->data[i][j].blue, sizeof(unsigned char), 1, file);
            fread(&(*picture)->data[i][j].green, sizeof(unsigned char), 1, file);
            fread(&(*picture)->data[i][j].red, sizeof(unsigned char), 1, file);
            if (row_padding != 0)
            {
                fseek(file, row_padding * 3, SEEK_CUR);
            }
        }
    }
}
void make_final_picture(BMPfile* picture, RGBQUAD** palitr, char* file_name)
{
    FILE* file;
    errno_t err = fopen_s(&file, file_name, "w+b");

    if (err != 0)
    {
        printf("Cant open file");
        exit(1);
    }
    fwrite(&picture->bhdr, sizeof(BMPheader), 1, file);
    fwrite(&picture->dhdr, sizeof(DIBheader), 1, file);
    fseek(file, picture->bhdr.pixel_offset, SEEK_SET);
    int row_padding = (4 - ((picture)->dhdr.width % 4)) % 4;
    for (unsigned int i = 0; i < picture->dhdr.height; i++)
    {
        for (unsigned int j = 0; j < picture->dhdr.width; j++)
        {
            fwrite(&picture->data[i][j].blue, sizeof(unsigned char), 1, file);
            fwrite(&picture->data[i][j].green, sizeof(unsigned char), 1, file);
            fwrite(&picture->data[i][j].red, sizeof(unsigned char), 1, file);
        }
        unsigned char null_pixel = 0;
        if (row_padding != 0)
        {
            fwrite(&null_pixel, sizeof(unsigned char), (row_padding * 3), file);
        }
    }
}
void free_picture(BMPfile** picture)
{
    for (unsigned int i = 0; i < (*picture)->dhdr.height; i++)
    {
        free((*picture)->data[i]);
    }
    free(*picture);
}
