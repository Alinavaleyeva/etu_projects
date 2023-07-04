#include <stdio.h>
#include "abs_min.h"
#include "abs_max.h"

int diff(int array[], int size){
    int max = abs_max(array, size);
    int min = abs_min(array, size);
    return max-min;
}
