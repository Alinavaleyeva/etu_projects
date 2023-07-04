#include <stdio.h>
#include <stdlib.h>
#define LIMIT_SIZE (100)

int abs_max(int array[], int size){
    int max_arr = array[0];
    for (int index = 1; index < size; index ++){
        if (abs(array[index]) > abs(max_arr)){
            max_arr = array[index];
        }     
    }
    return max_arr;
}


int abs_min(int array[], int size){
    int min_arr = array[0];
    for (int index = 1; index < size; index ++){
        if (abs(array[index]) < abs(min_arr)){
            min_arr = array[index];
        }
    }     
    return min_arr;
}

int diff(int array[], int size){
    int max = abs_max(array, size);
    int min = abs_min(array, size);
    return max-min;
}

int sum(int array[], int size){
    int max_arr = array[0];
    int max_index = 0;
    int sum = 0;
    for (int index = 1; index < size; index ++){
        if (abs(array[index]) > abs(max_arr)){
            max_arr = array[index];
            max_index = index;     
        }
    }

    for (int j = max_index; j < size; j++){
        sum = sum  + array[j];
    }

    return sum;
}

int main(){
    int value;
    int arr[LIMIT_SIZE];
    int current_size = 0;
    char symbol;
    scanf("%d%c", &value, &symbol);
    do{
        scanf("%d%c", &arr[current_size ++], &symbol);
        }while(symbol != '\n' && current_size < LIMIT_SIZE);

    switch (value){
        case 0:
        {
            printf("%d\n", abs_max(arr, current_size));
            break;
        }
        case 1:
        {
            printf("%d\n", abs_min(arr, current_size ));
            break;
        }
        case 2:
        {
            printf("%d\n", diff(arr, current_size));
            break;
        }
        case 3:
        {
            printf("%d\n", sum(arr, current_size));
            break;
        }
        default:
        {
            printf("Данные некорректны");
            break;
        }
    }
}
