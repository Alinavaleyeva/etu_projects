from node import Node, insert, remove, in_order

def test_new_tree():
    my_tree = insert(55, None)

    result = [55]
    my_answer = in_order(my_tree)
    assert result == my_answer

def test_insert():
    my_tree = insert(55, None)
    my_tree = insert(50, my_tree)
    my_tree = insert(40, my_tree)
    my_tree = insert(80, my_tree)
    my_tree = insert(34, my_tree)
    my_tree = insert(12, my_tree)

    my_answer = in_order(my_tree)
    result = [12, 34, 40, 50, 55, 80]
    assert result == my_answer

def test_remove_min():
    my_tree = insert(55, None)
    my_tree = insert(50, my_tree)
    my_tree = insert(40, my_tree)
    my_tree = insert(80, my_tree)
    my_tree = insert(34, my_tree)
    my_tree = insert(12, my_tree)

    my_tree = remove(12, my_tree)
    my_answer = in_order(my_tree)
    result = [34, 40, 50, 55, 80]
    assert result == my_answer

def test_remove_max():
    my_tree = insert(55, None)
    my_tree = insert(50, my_tree)
    my_tree = insert(40, my_tree)
    my_tree = insert(80, my_tree)
    my_tree = insert(34, my_tree)
    my_tree = insert(12, my_tree)

    my_tree = remove(80, my_tree)
    my_answer = in_order(my_tree)
    result = [12, 34, 40, 50, 55]
    assert result == my_answer

def test_remove_some_node():
    my_tree = insert(55, None)
    my_tree = insert(50, my_tree)
    my_tree = insert(40, my_tree)
    my_tree = insert(80, my_tree)
    my_tree = insert(34, my_tree)
    my_tree = insert(12, my_tree)

    my_tree = remove(34, my_tree)
    my_tree = remove(55, my_tree)

    my_answer = in_order(my_tree)
    result = [12, 40, 50, 80]
    assert result == my_answer