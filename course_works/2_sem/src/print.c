#include "print.h"
#include <stdio.h>
#include <stdlib.h>

void err_limit_img(){
    printf("Указанные координаты не находятся в пределах изображения.\n");
    exit(-1);

}
void err_value(){
    printf("Указано неверное значение переменной.\n");
    exit(-1);

}
int check_color(int color) {
    return !(0 <= color && color <= 255);
}
void err_color(){
    printf("Указано неверное значение цвета.\n");
    exit(-1);
}
void err_file_extension(){
    printf("Программа работает только с файлами, у которых расширение .bmp. Работа программы завершена.\n");
    exit(-1);
};
void err_version(){
    printf("Программа работает только с фйлами 3 версии BMP. Работа программы завершена\n");
    exit(-1);
}
void err_find_file(){
    printf("Не удается загрузить файл.\n");
    exit(-1);
}
void count_bits(){
    printf("Программа работает только с файлами, у которых выделено 24 бита на цвет. Работа программы завершена.\n");
    exit(-1);
}
void print_bmp_pixels(BMP_file *bmp_file){
    for (int i = 0; i<bmp_file->dhdr.height; i++){
        for (int j = 0; j<bmp_file->dhdr.width; j++){
            printf("%02x %02x %02x ", bmp_file->pixels_arr[i][j].r, bmp_file->pixels_arr[i][j].g, bmp_file->pixels_arr[i][j].b);
        }
    }
    printf("\n");
}

void printHelp() {
    printf("Руководство по использованию программы:\n");
    printf("Программа обрабатывает BMP-файлы версии [...]. С глубиной изображения 24 бита на пиксель\n");
    printf("Формат ввода: <имя исполняемого файла> <имя BMP-файла для обработки> <функция> -<ключ>/--<полный ключ> <аргумент> ... \n");
    printf("Функции/ключи:\n");

    printf("Первый ключ: -g/--g_rectangle-- Рисование прямоугольника.\n");
    printf("\t-f/--first  [<x-координата>.<y-координата>] - координата левого верхнего угла фигуры.\n");
    printf("\t-s/--second [<x-координата>.<y-координата>] - координата правого нижнего угла фигуры.\n");
    printf("\t-w/--width  [<число>] - толщина линии\n");
    printf("\t-F/--line_color  [<число>.<число>.<число>] - цвет линии (RGB).\n");
    printf("\t-H/--shape  [<число>] - выбор наличия заливки фигуры (0 - не залит, 1 - залит).\n");
    printf("\t-S/--shape_color [<число>.<число>.<число>] - цвет заливки (RGB).\n");

    printf("Второй ключ: -d/--draw_frame -- Рисование рамки в виде узора.\n");
    printf("\t-p/--pattern [<число>] - номер узора рамки, число от 1 до 3.\n");
    printf("\t-F/--line_color  [<число>.<число>.<число>] - цвет рамки(RGB).\n");
    printf("\t-w/--width  [<число>] - ширина рамки.\n");

    printf("Третий ключ: -t/--turn -- Поворот изображения (части) на 90/180/270 градусов.\n");
    printf("\t-f/--first  [<x-координата>.<y-координата>] - координата левого верхнего угла фигуры.\n");
    printf("\t-s/--second [<x-координата>.<y-координата>] - координата правого нижнего угла фигуры.\n");
    printf("\t-a/--angle  [<число>] - угол поворота (90/180/270 градусов).\n");

    printf("Четвертый ключ: -с/--circle --Рисование окружности.\n");
    printf("\t-1/--path_1  [<радиус>.<x-координата>.<y-координата>] - радиус и координата центра окружности.\n");
    printf("\t-2/--path_2  [<x-координата>.<y-координата>.<x-координата>.<y-координата>] - координаты левого верхнего и правого нижнего углов фигуры.\n");
    printf("\t-w/--width  [<число>] - толщина линии\n");
    printf("\t-F/--line_color  [<число>.<число>.<число>] - цвет линии (RGB).\n");
    printf("\t-H/--shape  [<число>] - выбор наличия заливки фигуры (0 - не залит, 1 - залит).\n");
    printf("\t-S/--shape_color [<число>.<число>.<число>] - цвет заливки (RGB).\n");

    printf("-h/--help - вывод справки о работе программы\n");
    printf("-i/--info - вывод подробной информации о bmp-файле\n");
    printf("-o/--output [путь] - файл для вывода (по умолчанию исходный файл, путь - относительный)\n");
}

void print_bmp_info(BMP_file * bmp_file) {
    printf("Информация о bmp-файле:\n");
    printf("ID = \t\t\t%c%c\n",bmp_file->bhdr.ID[0], bmp_file->bhdr.ID[1]);
    printf("file_size = \t\t%d\n",bmp_file->bhdr.file_size);
    printf("pixel_offset = \t\t%d\n",bmp_file->bhdr.pixel_offset);
    printf("header_size = \t\t%d\n",bmp_file->dhdr.header_size);
    printf("width = \t\t%d\n",bmp_file->dhdr.width);
    printf("height = \t\t%d\n",bmp_file->dhdr.height);
    printf("planes = \t\t%d\n",bmp_file->dhdr.planes);
    printf("bits_per_pixel = \t%d\n",bmp_file->dhdr.bits_per_pixel);
    printf("compression = \t\t%d\n",bmp_file->dhdr.compression);
    printf("data_size = \t\t%d\n",bmp_file->dhdr.data_size);
    printf("x_pixels_per_meter = \t\t%d\n",bmp_file->dhdr.x_pixels_per_meter);
    printf("y_pixels_per_meter = \t\t%d\n",bmp_file->dhdr.y_pixels_per_meter);
    printf("colors_in_color_table = \t\t%d\n",bmp_file->dhdr.colors_in_color_table);
    printf("important_color_count = \t%d\n",bmp_file->dhdr.important_color_count);
}