#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h> 
#include <math.h>
#define MAX_ID 255
#define KB 1024

#pragma pack(pop,1) 

typedef struct BITMAPFILEHEADER
{
    unsigned char ID[2];
    unsigned file_size;
    unsigned char unused[4];
    unsigned int pixel_offset;
} BMPheader;


typedef struct BITMAPINFOHEADER
{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short colorplanes;
    unsigned short bits_per_pixel;
    unsigned int compr;
    unsigned int data_size;
    unsigned int pwidth;
    unsigned int pweight;
    unsigned int colors_count;
} DIBheader;
typedef struct colours_in_pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;
typedef struct BMPfile
{
    BMPheader bhdr;
    DIBheader dhdr;
    pixel** data;
} BMPfile;

typedef struct RGBQUAD
{
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  rgbReserved;
} RGBQUAD;


#pragma pack(pop) 


#include "Check_choice.h"
#include "Menu.h"
#include "File_picture.h"
void make_negative(BMPfile* picture, RGBQUAD** palitr);
void make_black_and_white(BMPfile* picture, RGBQUAD** palitr);
void make_median_filtration(BMPfile* picture, RGBQUAD** palitr);
void make_gamma_correction(BMPfile* picture, RGBQUAD** palitr);
