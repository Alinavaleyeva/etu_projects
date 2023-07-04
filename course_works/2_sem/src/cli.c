#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cw_functions.h"
#include "bmp_processing.h"
#include "print.h"

#pragma pack (push,1)

const struct option long_options[] = {
        {"g_rectangle",       no_argument,       NULL, 'g'},
        {"draw_frame",      no_argument,       NULL, 'd'},
        {"turn",         no_argument,       NULL, 't'},
        {"circle",       no_argument,       NULL, 'c'},
        {"white",      no_argument,       NULL, 'A'},
        {"first",        required_argument, NULL, 'f'},
        {"second",       required_argument, NULL, 's'},
        {"angle",         required_argument, NULL, 'a'},
        {"path_1", required_argument, NULL, '1'},
        {"path_2",       required_argument, NULL, '2'},
        {"width",        required_argument, NULL, 'w'},
        {"pattern_frame",        required_argument, NULL, 'p'},
        {"line_color",   required_argument, NULL, 'F'},
        {"shape_color",  required_argument, NULL, 'S'},
        {"shape", required_argument, NULL, 'H'},
        {"output",       required_argument, NULL, 'o'},
        {"help",         no_argument,       NULL, 'h'},
        {"info",         no_argument,       NULL, 'i'},
        {NULL,           no_argument,       NULL,  0 }
};

#pragma pack(pop)

void parse(int **arr, int count, char *opt_arg) {
    char *str;
    str = strtok(opt_arg, ".");
    *(arr[0]) = atoi(str);
    for(int i = 1; i < count; i++) {
        str = strtok(NULL, ".");
        if(str != NULL) *(arr[i]) = atoi(str);
        else {
            printf("Было введено недостаточно чисел в одном аргументе. Работа программы завершена.\n");
            exit(-1);
        }
    }
}


Arguments* choice(Arguments *arguments, int opt) {
    int **arr = malloc(5 * sizeof(int*));

    switch (opt) {
        case 'f':
            arr[0] = &(arguments->x1), arr[1] = &(arguments->y1);
            parse(arr, 2, optarg);
            break;
        case 's':
            arr[0] = &(arguments->x2), arr[1] = &(arguments->y2);
            parse(arr, 2, optarg);
            break;
        case 'a':
            arguments->angle = atoi(optarg);
            break;
        case 'p':
            arguments->pattern = atoi(optarg);
            break;
        case '1':
            arr[0] = &(arguments->radius), arr[1] = &(arguments->x_c), arr[2] = &(arguments->y_c);
            parse(arr, 3, optarg);
            break;
        case '2':
            arr[0] = &(arguments->x1), arr[1] = &(arguments->y1);
            arr[2] = &(arguments->x2), arr[3] = &(arguments->y2);
            parse(arr, 4, optarg);
            break;
        case 'w':
            arguments->line_width = atoi(optarg);
            break;
        case 'F':
            arr[0] = &(arguments->color1_r), arr[1] = &(arguments->color1_g), arr[2] = &(arguments->color1_b);
            parse(arr, 3, optarg);
            break;
        case 'S':
            arr[0] = &(arguments->color2_r), arr[1] = &(arguments->color2_g), arr[2] = &(arguments->color2_b);
            parse(arr, 3, optarg);
            break;
        case 'H':
            arguments->shape = atoi(optarg);
            break;
        case 'o':
            arguments->output = malloc(sizeof(optarg)+1);
            strcpy(arguments->output, optarg);
            break;
        case 'h':
            printHelp();
            break;
    };

    return arguments;
}

BMP_file * functions_choice(int opt, int prev_opt, Arguments *arguments, BMP_file * bmp_file) {
    if (opt == 'g' || opt == 'd' || opt == 't' || opt == 'c' || opt == 'A') {
        switch (prev_opt) {
            case 'g':
                bmp_file = rectangle(bmp_file, arguments);
                break;
            case 'd':
                bmp_file = draw_frame(bmp_file, arguments);
                break;
            case 't':
                bmp_file = turn(bmp_file, arguments);
                break;
            case 'c':
                bmp_file = circle(bmp_file, arguments);
                break;
            case 'A':
                bmp_file = draw_white(bmp_file, arguments);
                break;

        }
    }
    return bmp_file;
}

Arguments* arg_set_to_NULL(Arguments* arguments) {
    arguments->x1 = -1, arguments->x2 = -1, arguments->x_c = -1;
    arguments->y1 = -1, arguments->y2 = -1, arguments->y_c = -1;
    arguments->angle = -1, arguments->line_width = -1, arguments->output = NULL;
    arguments->color1_r = -1, arguments->color1_g = -1, arguments->color1_b = -1;
    arguments->color2_r = -1, arguments->color2_g = -1, arguments->color2_b = -1;
    arguments->shape = -1, arguments->radius = -1; arguments->pattern = -1;
    return arguments;
}


void cli(int argc, char **argv) {
    char *opts = "gdtAcf:s:1:a:2:w:F:H:S:p:o:m:hi";
    Arguments *arguments = malloc(sizeof(Arguments));
    arguments = arg_set_to_NULL(arguments);

    int opt;
    int prev_opt = 'N';
    int long_index;
    char* file_name = argv[1];

    if (argc == 1) {
        printHelp();
        exit(-1);
    }

    BMP_file * bmp_file = read_bmp(file_name);

    arguments->output = file_name;

    opt = getopt_long(argc, argv, opts, long_options, &long_index);
    while (opt != -1) {

        bmp_file = functions_choice(opt, prev_opt, arguments, bmp_file);

        if (opt == 'g' || opt == 'd' || opt == 't' || opt == 'c' || opt == 'A'){
            prev_opt = opt;
        }
        if (opt == 'i') {
            print_bmp_info(bmp_file);
        }

        arguments = choice(arguments, opt);

        opt = getopt_long(argc, argv, opts, long_options, &long_index);

    }

    bmp_file = functions_choice('g', prev_opt, arguments, bmp_file);

//    printf("wight = %d, height = %d\n", bmp_file->dhdr.width, bmp_file->dhdr.height);
//    printf("x1 = %d; y1 = %d; x2 = %d; y2 = %d; x_c = %d; y_c = %d, pattern = %d\n", arguments->x1, arguments->y1, arguments->x2, arguments->y2, arguments->x_c, arguments->y_c, arguments->pattern);
//    printf("angle = %d, line_width = %d, radius = %d\n", arguments->angle, arguments->line_width, arguments->radius);
//    printf("r1 = %d, g1 = %d, b1 = %d, r2 = %d, g2 = %d, b2 = %d\n", arguments->color1_r, arguments->color1_g, arguments->color1_b, arguments->color2_r, arguments->color2_g, arguments->color2_b);
//    printf("output = %s\n", arguments->output);
//    printf("file_name = %s\n",file_name);
//    printf("argc = %d\n",argc);

    output_bmp_file(bmp_file, arguments->output);
    free_bmp_file(bmp_file);
}