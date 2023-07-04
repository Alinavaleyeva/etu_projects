#include <stdio.h>
#include <stdlib.h>
#include "sum.h"
#include "diff.h"
#include "min.h"
#include "max.h"

#define MAX_SIZE(100)

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
