#include <stdio.h>

int abs_min(int array[], int size){
    int min_arr = array[0];
    for (int index = 1; index < size; index ++){
        if (abs(array[index]) < abs(min_arr)){
            min_arr = array[index];
        }
    }     
    return min_arr;
}
