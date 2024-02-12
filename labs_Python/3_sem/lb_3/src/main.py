from node import Node, insert, remove, in_order
def in_order_print(node): # выводит левого потомка, затем родителя, затем правого потомка
    if node:
        in_order_print(node.left)
        print(node.val)
        in_order_print(node.right)

if __name__ == '__main__':
    my_tree = Node(55)
    my_tree = insert(50, my_tree)
    my_tree = insert(40, my_tree)
    my_tree = insert(80, my_tree)
    my_tree = insert(34, my_tree)
    my_tree = insert(12, my_tree)
    remove(34, my_tree)
    in_order_print(my_tree)


