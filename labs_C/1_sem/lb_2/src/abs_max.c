#include <stdio.h>
int abs_max(int array[], int size){
    int max_arr = array[0];
    for (int index = 1; index < size; index ++){
        if (abs(array[index]) > abs(max_arr)){
            max_arr = array[index];
        }     
    }
    return max_arr;
}
