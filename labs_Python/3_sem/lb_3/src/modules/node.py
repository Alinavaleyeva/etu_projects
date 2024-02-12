from typing import Union
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left: Union[Node, None] = left
        self.right: Union[Node, None] = right
        self.height = 1
def height(root): # высота дерева = макс высота из поддеревьев + 1 на "голову"
    if (root is None):
        return 0
    return (1 + max(height(root.left), height(root.right)))

def override_height(root): # переобпределение высоты
    root.height = height(root)
    return root
def bfactor(root): #проверка баланс-фактора
    hl = height(root.left)
    hr = height(root.right)
    return hr - hl
def rotate_right(root): #правый поворот
    q = root.left
    root.left = q.right
    q.right = override_height(root)
    return override_height(q)
def rotate_left(root): #левый поворот
    children = root.right
    root.right = children.left
    children.left = override_height(root)
    return override_height(children)
def balance(root): # балансировка
    root = override_height(root)
    if (bfactor(root) == 2):
        if (bfactor(root.right) < 0):
            root.right = rotate_right(root.right)
        return rotate_left(root)
    if (bfactor(root) == -2):
        if(bfactor(root.left) > 0):
            root.left = rotate_left(root.left)
        return rotate_right(root)

    return root # балансировка не нужна

def insert(val, root): # вставка ноды
    if root is None:
        return Node(val)

    if val < root.val:
        root.left = insert(val, root.left)
    else:
        root.right = insert(val, root.right)
    return balance(root)

def find_min(root): # поиск минимального узла в дереве
    if (root.left is None):
        return root
    else:
        return find_min(root.left)
def remove_min(root): # "выписывание" минимального эоемента
    if (root.left is None):
        return root.right # левый является минимумом -> возвращаем его правого ребенка
    root.left = remove_min(root.left)
    return balance(root)
def remove(val, root): # удаление ноды
    if root is None:
        return 0
    if val < root.val:
        root.left = remove(val, root.left)
    elif val > root.val:
        root.right = remove(val, root.right)
    else: # val = root.val
        my_left = root.left
        my_right = root.right
        if my_right is None:
            return my_left
        node_min = find_min(my_right)
        node_min.right = remove_min(my_right)
        node_min.left = my_left
        return balance(node_min)
    return balance(root)
def check(root) : # проверка дерева на правильность
    if root is None:
        return True
    lh = height(root.left)
    rh = height(root.right)
    if (abs(lh - rh) <= 1 and check(root.left) and check(root.right)):
        return True
    return False
def calculate_diffs(root):
    if root is None or (root.left is None and root.right is None):
        return []
    diffs = []
    if root.left is not None:
        diffs.append(root.val - root.left.val)
    if root.right is not None:
        diffs.append(root.right.val - root.val)
    return diffs + calculate_diffs(root.left) + calculate_diffs(root.right)

def diff(root: Node): # мин разница между значениями связных нод
    return min(calculate_diffs(root))

def in_order(root): #объод дерева: левый->корень->правый
    if root is None:
        return []
    return [*in_order(root.left), root.val, *in_order(root.right)]

