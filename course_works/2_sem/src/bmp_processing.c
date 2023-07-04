#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_processing.h"
#include "print.h"

// заполняем pixels_arr
void fill_img(FILE* fp, BMP_file** bmp_file) {
    int bytes_per_pixel = (*bmp_file)->dhdr.bits_per_pixel / 8; // количество байт на пиксель
    int row_size = bytes_per_pixel * (*bmp_file)->dhdr.width; // размер одной строки в байтах
    int row_padding = (4 - (row_size % 4)) % 4; // количество добавочных байт для выравнивания
    // последнее действие, если количество байт и так кратно 4
    int cur_col;
    int height = (*bmp_file)->dhdr.height - 1;
    unsigned char *row = malloc(row_size + row_padding); // место для считывания строки полностью (+выравнивание)
    fseek(fp, (*bmp_file)->bhdr.pixel_offset, SEEK_SET);
    // точка смещения: SEEK_SET – смещение отсчитывается от начала файла
    for (int cur_row = 0; cur_row < height + 1; cur_row++) {
        cur_col = 0;
        fread(row, row_size+row_padding, 1, fp); // считывание данных из потока
        for (int i = 0; i < row_size; i += bytes_per_pixel){ // проходимся по пикселям в строке
            (*bmp_file)->pixels_arr[height - cur_row][cur_col].b = row[i];
            (*bmp_file)->pixels_arr[height - cur_row][cur_col].g = row[i+1];
            (*bmp_file)->pixels_arr[height - cur_row][cur_col].r = row[i+2];
            cur_col++;
        }
    }
    free(row);
}

BMP_file* read_bmp(char* f_name){
    FILE* fp = fopen(f_name, "r");
    if (!fp){
        err_find_file();
    }
    BMP_file* bmp_file = malloc(sizeof (BMP_file));
    fread(&bmp_file->bhdr, sizeof (BMPHeader ), 1, fp);
    fread(&bmp_file->dhdr, sizeof (DIBHeader), 1, fp);

    // проверка на расширение файла
    if (strlen(f_name) > 4 && strcmp(f_name + strlen(f_name) - 4, ".bmp")){
        err_file_extension();
    }
    // проверка на весию файла
    if (bmp_file->dhdr.header_size != 40){
        err_version();
    }
    // проверка на количество бит
    if (bmp_file->dhdr.bits_per_pixel != 24) {
        count_bits();
    }

    bmp_file->pixels_arr = malloc(bmp_file->dhdr.height * sizeof(RGB*));
    for(int i = 0; i < bmp_file->dhdr.height; i++) {
        bmp_file->pixels_arr[i] = malloc(bmp_file->dhdr.width * sizeof(RGB));
    }
    fill_img(fp, &bmp_file);
    fclose(fp);

    return bmp_file;
}

unsigned char* rgb_to_str(BMP_file* bmp_file) {
    int bytes_per_pixel = bmp_file->dhdr.bits_per_pixel / 8 ;
    int row_size = bytes_per_pixel * bmp_file->dhdr.width;
    int row_padding = (4 - (row_size % 4)) % 4;
    int height = bmp_file->dhdr.height;
    int width = bmp_file->dhdr.width;

    unsigned char *data = malloc((row_size + row_padding) * bmp_file->dhdr.height);
    int index = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            data[index++] = bmp_file->pixels_arr[height - i - 1][j].b;
            data[index++] = bmp_file->pixels_arr[height - i - 1][j].g;
            data[index++] = bmp_file->pixels_arr[height - i - 1][j].r;
        }
        for(int j = 0; j < row_padding; j++) {
            data[index++] = (unsigned char)0;
        }
    }
    return data;
}

void output_bmp_file(BMP_file * bmp_file, char* output_file) {
    FILE *fp = fopen(output_file, "wb"); // "wb" - создает двоичный файл для записи.
    if (!fp) {
        printf("Проблемы с созданием файла для вывода. Работа программы завершена\n");
        exit(-1);
    }
    fwrite(&bmp_file->bhdr, 1, sizeof(BMPHeader),fp);
    fwrite(&bmp_file->dhdr, 1, sizeof(DIBHeader),fp);

    unsigned char* data = rgb_to_str(bmp_file);

    int bytes_per_pixel = bmp_file->dhdr.bits_per_pixel / 8 ;
    int row_size = bytes_per_pixel * bmp_file->dhdr.width;
    int row_padding = (4 - (row_size % 4)) % 4;

    fwrite(data, 1, (row_size + row_padding) * bmp_file->dhdr.height, fp);
    // записывает до count эл из буффера в fp
    free(data);
    fclose(fp);
}
BMP_file * new_bmp(int wight_f, int height_f, BMP_file* bmp_file) {
    BMP_file* new_file = calloc(1, sizeof (BMP_file));
    new_file->dhdr.width = wight_f;
    new_file->dhdr.height = height_f;
    new_file->bhdr.file_size = sizeof (RGB) * wight_f * height_f + sizeof (BMPHeader) + sizeof (DIBHeader);
    new_file->dhdr.data_size = sizeof (RGB) * wight_f * height_f;

    new_file->bhdr.ID[0] = bmp_file->bhdr.ID[0];
    new_file->bhdr.ID[1] = bmp_file->bhdr.ID[1];
    new_file->bhdr.pixel_offset = bmp_file->bhdr.pixel_offset;
    new_file->bhdr.unused[0] = bmp_file->bhdr.unused[0];
    new_file->bhdr.unused[1] = bmp_file->bhdr.unused[1];
    new_file->bhdr.unused[2] = bmp_file->bhdr.unused[2];
    new_file->bhdr.unused[3] = bmp_file->bhdr.unused[3];

    new_file->dhdr.header_size = bmp_file->dhdr.header_size;
    new_file->dhdr.planes = bmp_file->dhdr.planes;
    new_file->dhdr.bits_per_pixel = bmp_file->dhdr.bits_per_pixel;
    new_file->dhdr.compression = bmp_file->dhdr.compression;
    new_file->dhdr.x_pixels_per_meter = bmp_file->dhdr.x_pixels_per_meter;
    new_file->dhdr.y_pixels_per_meter = bmp_file->dhdr.y_pixels_per_meter;
    new_file->dhdr.colors_in_color_table = bmp_file->dhdr.colors_in_color_table;
    new_file->dhdr.important_color_count = bmp_file->dhdr.important_color_count;
    new_file->bhdr.pixel_offset = bmp_file->bhdr.pixel_offset;
    new_file->pixels_arr = malloc(height_f * sizeof(RGB*));
    for(int i = 0; i < height_f; i++) {
        new_file->pixels_arr[i] = calloc(wight_f,sizeof(RGB));
    }
    return new_file;
}
void free_bmp_file(BMP_file* bmp_file) {
    if (bmp_file) {
        for(int i = 0; i < bmp_file->dhdr.height; i++) {
            free(bmp_file->pixels_arr[i]);
        }
        free(bmp_file->pixels_arr);
        free(bmp_file);
    }
}