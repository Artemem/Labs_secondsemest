#pragma once
#include "Header.h"

void gamma_correction(BMPfile* picture, RGBQUAD** palitr);
void median_filtration(BMPfile* picture, RGBQUAD** palitr);
void black_and_white(BMPfile* picture, RGBQUAD** palitr);
void negative(BMPfile* picture, RGBQUAD** palitr);