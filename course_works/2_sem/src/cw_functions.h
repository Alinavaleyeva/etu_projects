#pragma once
#include "bmp_processing.h"

void draw_point(RGB *elem, unsigned char r, unsigned char g, unsigned char b);
BMP_file * rectangle(BMP_file * bmp_file, Arguments *arguments);
BMP_file * draw_frame(BMP_file * bmp_file, Arguments *arguments);
BMP_file * turn(BMP_file * bmp_file, Arguments *arguments);
BMP_file * circle(BMP_file * bmp_file, Arguments *arguments);
BMP_file * draw_white(BMP_file * bmp_file, Arguments *arguments);