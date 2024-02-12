import pytest
from hash_table import Hash_table

def test_1():
    ht = Hash_table(10)
    ht.insert(33, 45)
    ht.insert(36, 62)
    ht.insert(37, 54)
    my_answer = ht.return_element(2)
    answer = [36, 62]
    assert my_answer == answer

def test_2():
    ht = Hash_table(10)
    ht.insert(1, "hi!")
    ht.insert(1, "alina")
    my_answer = ht.return_element(2)[1]
    answer = "alina"
    assert my_answer == answer

def test_3():
    ht = Hash_table(10)
    ht.insert(1, "hi!")
    ht.insert(1, "alina")
    my_answer = ht.return_element(2)[1]
    answer = "alina"
    assert my_answer == answer

def test_4():
    ht = Hash_table(10)
    my_answer = ht.return_size()
    answer = 10
    assert my_answer == answer

def test_4():
    ht = Hash_table(10)
    my_answer = ht.return_element(3)
    answer = [None, None]
    assert my_answer == answer
