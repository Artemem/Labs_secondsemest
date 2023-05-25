#include "Header.h"


void gamma_correction(BMPfile* picture, RGBQUAD** palitr)
{
    make_gamma_correction(picture, palitr);
    make_final_picture(picture, palitr, "Gamma_Correction.bmp");
    free_picture(&picture);
}
void median_filtration(BMPfile* picture, RGBQUAD** palitr)
{
    make_median_filtration(picture, palitr);
    make_final_picture(picture, palitr, "Median_Filtration.bmp");
    free_picture(&picture);
}
void black_and_white(BMPfile* picture, RGBQUAD** palitr)
{
    make_black_and_white(picture, palitr);
    make_final_picture(picture, palitr, "Black_and_White.bmp");
    free_picture(&picture);
}
void negative(BMPfile* picture, RGBQUAD** palitr)
{
    make_negative(picture, palitr);
    make_final_picture(picture, palitr, "Negative.bmp");
    free_picture(&picture);
}