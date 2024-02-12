from my_sort import timesort
from my_sort import get_len_run
from my_sort import insertion_sort

def test_timsort_1():
    array = [-4, 7, 5, 3, 5, -4, 2, -1, -9, -8, -3, 0, 9, -7, -4, -10, -4, 2, 6, 1, -2, -3, -1, -8, 0, -8, -7, -3, 5, -1, -8, -8, 8, -1, -3, 3, 6, 1, -8, -1, 3, -9, 9, -6]
    timesort(array)
    answer_arr = [0, 0, 1, 1, -1, -1, -1, -1, -1, 2, 2, -2, 3, 3, 3, -3, -3, -3, -3, -4, -4, -4, -4, 5, 5, 5, 6, 6, -6, 7, -7, -7, 8, -8, -8, -8, -8, -8, -8, 9, 9, -9, -9, -10]
    assert array == answer_arr


def test_timsort_2():
    array = [1, -1, 1, 1, -1, 1]
    timesort(array)
    answer_arr = [1, 1, 1, 1, -1, -1]
    assert array == answer_arr

def test_len_run():
    array = [5, 6, 8, 9, 7]
    my_len = get_len_run(array, 0)
    len_answer = 4
    assert my_len == len_answer

def test_insert_sort():
    array = [3, -7, 6, 5, 4, 3]
    insertion_sort(array, 0, 6)
    answer_array = [3, 3, 4, 5, 6, -7]
    assert array == answer_array

