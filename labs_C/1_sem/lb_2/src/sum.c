#include <stdio.h>
#include “abs_max.h”

int sum(int array[], int size){
	int max = abs_max(array, size);
	int sum = 0;
	int ready = 0;
	for (int i = 0; i < size; i++){
		if (abs(array[i]) == abs(max)){
			ready = 1;
		}
		if (ready){
			sum += array[i];			}
		}
	return sum;
}
