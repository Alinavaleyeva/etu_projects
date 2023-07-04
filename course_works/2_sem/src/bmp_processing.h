#pragma once
#include <stdio.h>
#include <getopt.h>
#pragma pack (push, 1)

typedef struct Arguments {
    int x1, y1;
    int x2, y2;
    int x_c, y_c;
    int radius;
    int angle;
    int shape;
    int pattern;
    int line_width;
    int color1_r, color1_g, color1_b;
    int color2_r, color2_g, color2_b;
    char *output;
} Arguments;

typedef struct BMPHeader{
    unsigned char ID[2];
    unsigned int file_size;
    unsigned char unused[4];
    unsigned int pixel_offset;
} BMPHeader;

typedef struct DIBHeader{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes; // слои
    unsigned short bits_per_pixel; // бит на пиксель
    unsigned int compression; // сжатие
    unsigned int data_size; // размер информации о пикселях
    unsigned int x_pixels_per_meter;
    unsigned int y_pixels_per_meter;
    unsigned int colors_in_color_table; // количество цветов в палитре
    unsigned int important_color_count; // количество важных цветов в палитре
} DIBHeader;

typedef struct RGB{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;

typedef struct BMP_file{
    BMPHeader bhdr;
    DIBHeader dhdr;
    unsigned char *data;
    RGB **pixels_arr; // память для набора пикселей (цвет)
} BMP_file;

#pragma pack(pop)

void fill_img(FILE* fp, BMP_file** bmp_file);
BMP_file* read_bmp(char* f_name);
void free_bmp_file(BMP_file* bmp_file);
unsigned char* rgb_to_str(BMP_file* bmp_file);
void output_bmp_file(BMP_file * bmp_file, char* output_file);
BMP_file * new_bmp(int wight, int height, BMP_file* bmp_file);