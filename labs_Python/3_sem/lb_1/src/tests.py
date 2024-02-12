from unrolled_list import Unrolled_list
import pytest

def test_len_list():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_tail(9)

    answer_arr = [3, 4, 8, 5]
    assert len(answer_arr) == my_list.len_list

def test_delete_value():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_tail(5)
    my_list.delete_value(4)
    answer_arr = [3, 4, 8, 5]
    answer_arr.remove(4)
    assert my_list.to_arr() == answer_arr


def test_delete_index():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_tail(5)
    my_list.delete_index(1)
    answer_arr = [3, 4, 8, 5]
    answer_arr.pop(1)
    assert my_list.to_arr() == answer_arr

def test_search_value():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_tail(5)
    answer_arr = [3, 4, 8, 5]
    answer_ind = answer_arr.index(8)
    assert my_list.search_value(8) == answer_ind

def test_search_index():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_tail(5)
    answer_arr = [3, 4, 8, 5]
    answer_ind = answer_arr[2]
    assert my_list.search_index(2) == answer_ind

def test_insert_to_tail():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    answer_arr = [3, 4]
    assert my_list.to_arr() == answer_arr

def test_insert_to_head():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_head(5)
    answer_arr = [5, 3,  4, 8]
    assert my_list.head.array == answer_arr

def test_insert_to_index():
    my_list = Unrolled_list()
    my_list.insert_to_tail(3)
    my_list.insert_to_tail(4)
    my_list.insert_to_tail(8)
    my_list.insert_to_index(5, 1)
    answer_arr = [3, 5,  4, 8]
    assert my_list.head.array == answer_arr
