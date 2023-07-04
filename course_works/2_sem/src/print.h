#pragma once
#include "bmp_processing.h"

void err_limit_img();
void err_value();
void err_color();
int check_color(int color);
void err_find_file();
void count_bits();
void err_version();
void err_file_extension();
void print_bmp_pixels(BMP_file *bmp_file);
void printHelp();
void print_bmp_info(BMP_file * bmp_file);