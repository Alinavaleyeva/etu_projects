#include <stdlib.h>
#include <math.h>
#include "print.h"
#include "cw_functions.h"
#include "bmp_processing.h"

// закрашивание точки
void draw_point(RGB *elem, unsigned char r, unsigned char g, unsigned char b) {
    elem->r = r;
    elem->g = g;
    elem->b = b;
}

// 1 функция - рисование прямоугольника
BMP_file* rectangle(BMP_file * bmp_file, Arguments *arguments) {
    int *x1 = &(arguments->x1), *y1 = &(arguments->y1);
    int *x2 = &(arguments->x2), *y2 = &(arguments->y2);
    int *line_wight = &(arguments->line_width);
    int *line_color_r = &(arguments->color1_r);
    int *line_color_g = &(arguments->color1_g);
    int *line_color_b = &(arguments->color1_b);
    int *shape_fill = &(arguments->shape);
    int *color_fill_r = &(arguments->color2_r);
    int *color_fill_g = &(arguments->color2_g);
    int *color_fill_b = &(arguments->color2_b);

    if (check_color(*line_color_r) || check_color(*line_color_g) || check_color(*line_color_b)){
        err_color();
    }    if (check_color(*color_fill_r) || check_color(*color_fill_g) || check_color(*color_fill_b)){
        err_color();
    }
    if (*x1 < 0 || *y1 < 0 || *x2 >= bmp_file->dhdr.width || *y2 >= bmp_file->dhdr.height) {
        err_limit_img();
    }
    if(*line_wight < 0 ||  (*shape_fill != 0 && *shape_fill != 1)) {
        err_value();
    }

    for (int i = 0; i < *line_wight; i++) {
        for (int j = *x1; j <= *x2; j++) {
            // Верхняя граница
            draw_point(&bmp_file->pixels_arr[*y1+i][j], *line_color_r, *line_color_g, *line_color_b);
            // Нижняя граница
            draw_point(&bmp_file->pixels_arr[*y2 - i][j], *line_color_r, *line_color_g, *line_color_b);
        }
        for (int j = *y1; j <= *y2; j++) {
            // Левая граница
            draw_point(&bmp_file->pixels_arr[j][*x1 + i], *line_color_r, *line_color_g, *line_color_b);
            // Правая граница
            draw_point(&bmp_file->pixels_arr[j][*x2 - i], *line_color_r, *line_color_g, *line_color_b);
        }
    }

//     закраска прямоугольникa, если shape_fill = 1
    if (*shape_fill == 1) {
        for (int i = *y1 + *line_wight; i <= *y2 - *line_wight; i++) {
            for (int j = *x1 + *line_wight; j <= *x2 - *line_wight; j++) {
                draw_point(&bmp_file->pixels_arr[i][j], *color_fill_r, *color_fill_g, *color_fill_b);
            }
        }
    }
    *x1 = -1, *y1 = -1, *x2 = -1, *y2 = -1, *line_wight = -1, * shape_fill = -1;
    *line_color_r = -1, *line_color_g = -1, *line_color_b = -1;
    *color_fill_r = -1, *color_fill_g = -1, *color_fill_b = -1;

    return bmp_file;
}

// 2 функция - поворот изображения
BMP_file * turn(BMP_file * bmp_file, Arguments *arguments) {
    int *x1 = &(arguments->x1), *y1 = &(arguments->y1);
    int *x2 = &(arguments->x2), *y2 = &(arguments->y2);
    int *angle = &(arguments->angle);
    if (*x1 < 0 || *y1 < 0 || *x2 >= bmp_file->dhdr.width || *y2 >= bmp_file->dhdr.height) {
        err_limit_img();
        exit(-1);
    }
    if (*angle % 90 != 0 || *angle > 270 || *angle < 0) {
        err_value();
    }
    RGB **tmp_arr = malloc((bmp_file->dhdr.height + 1) * sizeof(RGB *));
    for (int i = 0; i < bmp_file->dhdr.height; i++) {
        tmp_arr[i] = calloc((bmp_file->dhdr.width + 1), sizeof(RGB));
    }
    if (*angle == 90) {
        if ((*x2 - *x1) >= (*y2 - *y1)) {
            int t_h = ((*x2 - *x1) - (*y2 - *y1)) / 2 ;
            int t_h1 = t_h;
            int t_h2 = t_h;
            if (t_h >= *y1) {
                t_h1 = *y1;
            }
            if (t_h >= bmp_file->dhdr.height - *y2) {
                t_h2 = bmp_file->dhdr.height - *y2 - 1;
            }
            int tx = 0;
            int ty = 0;
            for (int j = *y1; j <= *y2; j++) {
                tx = 0;
                for (int i = *x1 + t_h - t_h1; i <= *x2 - t_h + t_h2; i++) {
                    tmp_arr[ty][tx] = bmp_file->pixels_arr[j][i];
                    tx++;
                }
                ty++;
            }
            tx = 0;
            ty = 0;
            for (int j = *x2 - t_h; j > *x1 + t_h; j--) {
                for (int i = *y1 - t_h1; i < *y2 + t_h2; i++) {
                    bmp_file->pixels_arr[i][j] = tmp_arr[ty][tx];
                    tx++;
                }
                tx = 0;
                ty++;
            }
        } else {
            int t_h = ((*y2 - *y1) - (*x2 - *x1)) / 2;
            int t_h1 = t_h;
            int t_h2 = t_h;
            if (t_h >= *x1) {
                t_h2 = *x1;
            }
            if (t_h > bmp_file->dhdr.width - *x2) {
                t_h1 = bmp_file->dhdr.width - *x2 - 1;
            }
            int tx = 0;
            int ty = 0;
            for (int j = *y1 + t_h - t_h1; j <= *y2 - t_h + t_h2; j++) {
                tx = 0;
                for (int i = *x1; i <= *x2; i++) {
                    tmp_arr[ty][tx] = bmp_file->pixels_arr[j][i];
                    tx++;
                }
                ty++;
            }
            tx = 0;
            ty = 0;
            for (int i = *x2 + t_h1; i >= *x1 - t_h2; i--) {
                tx = 0;
                for (int j = *y1 + t_h; j <= *y2 - t_h; j++) {
                    bmp_file->pixels_arr[j][i] = tmp_arr[ty][tx];
                    tx++;
                }
                ty++;
            }
        }
    }
    if (*angle == 180) {
        int tx = 0;
        int ty = 0;
        for (int j = *y1; j <= *y2; j++) {
            for (int i = *x1; i <= *x2; i++) {
                tmp_arr[ty][tx] = bmp_file->pixels_arr[j][i];
                tx++;
            }
            tx = 0;
            ty++;
        }
        tx = 0;
        ty = 0;
        for (int j = *y2; j >= *y1; j--) {
            for (int i = *x2; i >= *x1; i--) {
                bmp_file->pixels_arr[j][i] = tmp_arr[ty][tx];
                tx++;
            }
            tx = 0;
            ty++;
        }
    }
    if (*angle == 270) {
        if ((*x2 - *x1) > (*y2 - *y1)) {
            int t_h = ((*x2 - *x1) - (*y2 - *y1)) / 2;
            int t_h1 = t_h;
            int t_h2 = t_h;
            if (t_h > *y1) {
                t_h1 = *y1;
            }
            if (t_h > bmp_file->dhdr.height - *y2) {
                t_h2 = bmp_file->dhdr.height - *y2 - 1;
            }
            int tx = 0;
            int ty = 0;
            for (int j = *y1; j <= *y2; j++) {
                for (int i = *x1 + t_h - t_h2; i <= *x2 - t_h + t_h1; i++) {
                    tmp_arr[ty][tx] = bmp_file->pixels_arr[j][i];
                    tx++;
                }
                tx = 0;
                ty++;
            }
            tx = 0;
            ty = 0;
            for (int i = *x1 + t_h; i < *x2 - t_h; i++) {
                for (int j = *y2 + t_h2; j > *y1 - t_h1; j--) {
                    bmp_file->pixels_arr[j][i] = tmp_arr[ty][tx];
                    tx++;
                }
                tx = 0;
                ty++;
            }
        } else {
            int t_h = ((*y2 - *y1) - (*x2 - *x1)) / 2 - ((*y2 - *y1) - (*x2 - *x1)) % 2;
            int t_h1 = t_h;
            int t_h2 = t_h;
            if (t_h > *x1) {
                t_h1 = *x1;
            }
            if (t_h > bmp_file->dhdr.width - *x2) {
                t_h2 = bmp_file->dhdr.width - *x2 - 1;
            }
            int tx = 0;
            int ty = 0;
            for (int j = *y1 + t_h - t_h1; j <= *y2 - t_h + t_h2; j++) {
                for (int i = *x1; i <= *x2; i++) {
                    tmp_arr[ty][tx] = bmp_file->pixels_arr[j][i];
                    tx++;
                }
                tx = 0;
                ty++;
            }
            tx = 0;
            ty = 0;
            for (int i = *x1 - t_h1; i < *x2 + t_h2; i++) {
                for (int j = *y2 - t_h; j > *y1 + t_h; j--) {
                    bmp_file->pixels_arr[j][i] = tmp_arr[ty][tx];
                    tx++;
                }
                tx = 0;
                ty++;
            }
        }
    }
    for (int i = 0; i < bmp_file->dhdr.height; i++) {
        free(tmp_arr[i]);
    }
    free(tmp_arr);

    *x1 = -1, *y1 = -1, *x2 = -1, *y2 = -1, *angle = -1;
    return bmp_file;
}

void frame_pattern_1(int frame_width, int frame_r, int frame_g, int frame_b, BMP_file* new_bmp_file){
    for (int i = 0; i < new_bmp_file->dhdr.height; i++){
        for (int j = 0; j < new_bmp_file->dhdr.width; j++){
            if ( sin(6.0 * i / frame_width) < sin(6.0 * j / frame_width) ){
                draw_point(&new_bmp_file->pixels_arr[i][j], frame_r, frame_g, frame_b);
            } else{
                draw_point(&new_bmp_file->pixels_arr[i][j], 255, 255,255);
            }
        }
    }
}

void frame_pattern_2(int frame_width, int frame_r, int frame_g, int frame_b, BMP_file* new_bmp_file){
    for (int i = 0; i < new_bmp_file->dhdr.height; i++){
        for (int j = 0; j < new_bmp_file->dhdr.width; j++){
            if ( tan(60.0/frame_width * i/10.0 - sin(60.0/frame_width * j/10.0)) <= sin(60.0/frame_width * j/10.0)){
                draw_point(&new_bmp_file->pixels_arr[i][j], frame_r, frame_g, frame_b);
            } else{
                draw_point(&new_bmp_file->pixels_arr[i][j], 255, 255,255);
            }
        }
    }
}
void frame_pattern_3(int frame_width, int frame_r, int frame_g, int frame_b, BMP_file* new_bmp_file){
    for (int i = 0; i < new_bmp_file->dhdr.height; i++){
        for (int j = 0; j < new_bmp_file->dhdr.width; j++){
            double a = atan(tan(57.0/frame_width * j/10.0));
            double b = atan(tan(-57.0/frame_width * i/10.0));
            if ( (a*a + (b - sqrt(fabs(a))) * (b - sqrt(fabs(a)))) <= 1  ){
                draw_point(&new_bmp_file->pixels_arr[i][j], frame_r, frame_g, frame_b);
            } else{
                draw_point(&new_bmp_file->pixels_arr[i][j], 255, 255,255);
            }
        }
    }
}
// 3 функция - рамка
BMP_file * draw_frame(BMP_file *bmp_file, Arguments *arguments) {
    int *pattern = &(arguments->pattern);
    int *frame_width = &(arguments->line_width);
    int *color_r = &(arguments->color1_r), *color_g = &(arguments->color1_g), *color_b = &(arguments->color1_b);
    if (check_color(*color_r) || check_color(*color_g) || check_color(*color_b) || *frame_width < 0){
        err_value();
    }
    // новое изображение
    BMP_file* new_bmp_file;
    new_bmp_file = new_bmp(bmp_file->dhdr.width + 2*(*frame_width), bmp_file->dhdr.height + 2*(*frame_width), bmp_file);
//    fprintf(stderr, "error");

    // рамка на новом изображении
    switch (*pattern) {
        case 1:
            frame_pattern_1(*frame_width, *color_r, *color_b, *color_g, new_bmp_file);
            break;
        case 2:
            frame_pattern_2(*frame_width, *color_r, *color_b, *color_g, new_bmp_file);
            break;
        case 3:
            frame_pattern_3(*frame_width, *color_r, *color_b, *color_g, new_bmp_file);
            break;
        default:
            err_value();
            break;
    }
    // отрисовка старого
    for (int i = 0; i < bmp_file->dhdr.height; i++){
        for (int j = 0; j < bmp_file->dhdr.width; j++){
            RGB* pixel = &bmp_file->pixels_arr[i][j];
            draw_point(&new_bmp_file->pixels_arr[i + *frame_width][j + *frame_width], pixel->r, pixel->g, pixel->b);
        }
    }
    free_bmp_file(bmp_file);
    *frame_width = -1,   *color_r = -1, *color_g = -1, *color_b = -1;
    return new_bmp_file;
}

// 4 функция - окружность
BMP_file * circle(BMP_file * bmp_file, Arguments *arguments) {

    int *radius = &(arguments->radius);
    int *x_center = &(arguments->x_c), *y_center = &(arguments->y_c);
    int *x1 = &(arguments->x1), *y1 = &(arguments->y1);
    int *x2 = &(arguments->x2), *y2 = &(arguments->y2);
    int *line_wight = &(arguments->line_width);
    int *line_color_r = &(arguments->color1_r);
    int *line_color_g = &(arguments->color1_g);
    int *line_color_b = &(arguments->color1_b);
    int *shape_fill = &(arguments->shape);
    int *color_fill_r = &(arguments->color2_r);
    int *color_fill_g = &(arguments->color2_g);
    int *color_fill_b = &(arguments->color2_b);

    // проверка  коррекности введенных значений
    if ( (*radius != -1 && *radius < 0) || (*x_center != -1 && *x_center < 0) || (*y_center != -1 && *y_center < 0)){
        err_value();
    }
    if ( (*x1 != -1 && *x1 < 0) || (*x2 != -1 && *x2 < 0)){
        err_value();
    }
    if ( (*y1 != -1 && *y1 < 0) || (*y2 != -1 && *y2 < 0) ){
        err_value();
    }
    if ((*shape_fill != 0 && *shape_fill != 1) || *line_wight < 0){
        err_value();
    }
    if (check_color(*line_color_r) || check_color(*line_color_g) || check_color(*line_color_b)){
        err_color();
    }
    if (check_color(*color_fill_r) || check_color(*color_fill_g) || check_color(*color_fill_b)){
        err_color();
    }
    // проверка выхода за картинку
    if ((*x2 > 0 && *x2 >= bmp_file->dhdr.width) || (*y2 > 0 && *y2 >= bmp_file->dhdr.width)){
        err_limit_img();
    }
    int sum_radius_x = (*radius + *line_wight );
    if ( (*radius > 0) && (sum_radius_x > *x_center || sum_radius_x > *y_center || sum_radius_x > bmp_file->dhdr.width - *x_center || sum_radius_x > bmp_file->dhdr.height - *y_center ) ){
        err_limit_img();
    }
    // 2 способ - через две точки
    if (*radius == -1){
        *radius = (*x2 - *x1)/2 - *line_wight;
        if (*radius < 0){
            err_value();
        }
        *x_center = *x1 + *radius + *line_wight;
        *y_center = *y1 + *radius + *line_wight;
        for (int y = 0; y < bmp_file->dhdr.height; y++){
            for (int x = 0; x < bmp_file->dhdr.width; x++){
                int dx = x - *x_center;
                int dy = y - *y_center;
                int hypotenuse = dx*dx + dy*dy;
                if (hypotenuse < (*radius) * (*radius) && *shape_fill == 1 ){
                    draw_point(&bmp_file->pixels_arr[x][y], *color_fill_r, *color_fill_g, *color_fill_b);
                }
                if (hypotenuse >= (*radius)*(*radius) && hypotenuse < (*radius + 2 *(*line_wight))*(*radius + 2*(*line_wight))){
                    draw_point(&bmp_file->pixels_arr[x][y], *line_color_r, *line_color_g, *line_color_b);
                }
            }
        }
    }
    else{
        for (int y = 0; y < bmp_file->dhdr.height; y++){
            for (int x = 0; x < bmp_file->dhdr.width; x++){
                int dx = x - *x_center;
                int dy = y - *y_center;
                int hypotenuse = dx*dx + dy*dy;
                if (hypotenuse < (*radius) * (*radius) && *shape_fill == 1 ){
                    draw_point(&bmp_file->pixels_arr[x][y], *color_fill_r, *color_fill_g, *color_fill_b);
                }
                if (hypotenuse >= (*radius)*(*radius) && hypotenuse < (*radius + *line_wight)*(*radius + *line_wight)){
                    draw_point(&bmp_file->pixels_arr[x][y], *line_color_r, *line_color_g, *line_color_b);
                }
            }
        }
    }

    *x1 = -1, *y1 = -1, *x2 = -1, *y2 = -1, *line_wight = -1, * shape_fill = -1;
    *line_color_r = -1, *line_color_g = -1, *line_color_b = -1;
    *color_fill_r = -1, *color_fill_g = -1, *color_fill_b = -1;
    *radius = -1; *x_center = -1; *y_center = -1;

    return bmp_file;
}

BMP_file * draw_white(BMP_file * bmp_file, Arguments *arguments) {
    int *line_color_r = (&arguments->color1_r);
    int *line_color_g = (&arguments->color1_g);
    int *line_color_b = (&arguments->color1_b);
    int *line_width = (&arguments->line_width);
    if (*line_width < 0){
        err_value();
    }
    for (int y = 0; y < bmp_file->dhdr.height; y++) {
        for (int x = 0; x < bmp_file->dhdr.width; x++) {
            if (bmp_file->pixels_arr[y][x].r == 255 && bmp_file->pixels_arr[y][x].g == 255 && bmp_file->pixels_arr[y][x].b == 255) {
                for (int y1 = y - *line_width; y1 <= y + *line_width; y1++){
                    for (int x1 = x - *line_width; x1 <= x + *line_width; x1++){
                        if (y1 < 0 || y1 >= bmp_file->dhdr.height || x1 < 0 || x1 > bmp_file->dhdr.width){
                            err_limit_img();
                        }
                        if(bmp_file->pixels_arr[y1][x1].r != 255 && bmp_file->pixels_arr[y1][x1].g != 255 && bmp_file->pixels_arr[y1][x1].b != 255){
                            draw_point(&bmp_file->pixels_arr[y1][x1], *line_color_r, *line_color_g, *line_color_b);
                        }
                    }
                }
            }
        }
    }
    *line_color_b = -1, *line_color_r = -1; *line_color_g = -1, *line_width = -1;
    return bmp_file;
}