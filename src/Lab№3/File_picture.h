#pragma once
#include "Header.h"
BMPfile* load_picture(FILE* file, RGBQUAD** palitr);
void make_pixel_array(FILE* file, BMPfile** picture);
void make_final_picture(BMPfile* picture, RGBQUAD** palitr, char* file_name);
void free_picture(BMPfile** picture);
