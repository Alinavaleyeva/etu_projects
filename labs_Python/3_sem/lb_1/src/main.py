from unrolled_list import Unrolled_list
import time
def check(arr1, arr2, n_array = 4):
    my_unrolled_list = Unrolled_list(n_array)
    for i in arr1:
        my_unrolled_list.insert_to_tail(i)
        my_unrolled_list.print_list()
    for i in arr2:
        my_unrolled_list.delete_value(i)
        my_unrolled_list.print_list()
    my_unrolled_list.print_list()
if __name__ == '__main__':
    check([1, 2, 3, 4, 5, 6], [2, 3, 8], 4)
