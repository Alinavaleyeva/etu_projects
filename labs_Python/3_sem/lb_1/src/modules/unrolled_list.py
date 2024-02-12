from node import Node

class Unrolled_list:
    def __init__(self, n_array = 4):
        self.n_array = n_array # максимальный размер массива(ноды списка)
        self.head = None
        self.tail = None
        self.len_list = 0 #общая длина всеэ элементов списка


    def search_index(self, index):
        if index >= self.len_list:
            print("Индекс выходит за границы спика")
        else:
            count = 0
            temp = self.head
            while temp != None:
                if (count + temp.length_arr > index) and (count <= index):
                    return temp.array[index-count]
                else:
                    count += temp.length_arr
                temp = temp.next

            print("Элемент под таким индексом не найден")
    def search_value(self, value):
        temp = self.head
        flag = False
        ind = 0
        while temp != None and ind < self.len_list:
            if value not in temp.array:
                ind += temp.length_arr
            else:
                for i in range(len(temp.array)):
                    if temp.array[i] == value:
                        ind += i
                        flag = 1
                break
            temp = temp.next
        if flag:
            return ind
        return -1

    def insert_to_tail(self, elem):
        if self.head == None:
            self.head = Node()
            self.head.array.append(elem)
            self.head.length_arr += 1
            self.tail = self.head

        # если еще есть место в последнем элементе
        elif self.tail.length_arr + 1 <= self.n_array: #если еще есть место в последнем элементе
            self.tail.array.append(elem) #вставляем туда элемент
            self.tail.length_arr += 1

        else:
            new_node = Node()
            half_length = self.tail.length_arr // 2
            new_node.array = self.tail.array[half_length:]
            new_node.array.append(elem)
            new_node.length_arr = len(new_node.array)

            self.tail.array = self.tail.array[0:half_length]
            self.tail.length_arr = half_length
            self.tail.next = new_node
            self.tail = new_node

        self.len_list += 1

    def insert_to_head(self, elem):
        if self.head == None:
            self.insert_to_tail(elem)
        elif (self.head.length_arr + 1 <= self.n_array):
            self.head.array.insert(0, elem)
            self.head.length_arr += 1
        else:
            prev = self.head.next

            new_node = Node()
            half_length = self.head.length_arr // 2
            new_node.array = self.head.array[half_length:]
            new_node.length_arr = len(new_node.array)
            self.head.array.insert(0, elem)
            self.head.array = self.head.array[0:half_length+1]
            self.head.length_arr = len(self.head.array)

            self.head.next = new_node
            new_node.next = prev

        self.len_list += 1

    def insert_to_index(self, value, index):
        if index < 0 or index > self.len_list:
            print("Введено неверное значение. Индекс выходит за границы списка")

        if self.len_list == 0 or self.len_list <= index:
            self.insert_to_tail(value)
        else:
            count = 0
            temp = self.head
            while temp is not None:
                for i in range(len(temp.array)):
                    if count == index:
                        if len(temp.array) + 1 <= self.n_array:
                            temp.array.insert(i, value)
                            temp.length_arr += 1
                        else:
                            new_node = Node()
                            half_ind = self.n_array // 2
                            new_node.array = temp.array[half_ind:]
                            new_node.length_arr = len(new_node.array)
                            temp.array = temp.array[:half_ind]
                            temp.length_arr = len(temp.array)

                            if (temp.next is not None):
                                new_node.next = temp.next
                                temp.next = new_node
                            else:
                                temp.next = new_node

                            if i < half_ind:
                                temp.array.insert(i, value)
                                temp.length_arr += 1
                            else:
                                new_node.array.insert(i - half_ind, value)
                                new_node.length_arr += 1
                        self.len_list += 1
                        return
                    count += 1
                temp = temp.next

    def print_list(self):
        if self.head == None:
            print("Пустой список\n")
        temp = self.head
        while temp != None:
            for i in range(0, temp.length_arr):
                print(temp.array[i], end=" ")
            # print("end of array \n")

            temp = temp.next
        # print("длина всего списка = ", self.len_list)

    def delete_index(self, index):
        if self.len_list == 0:
            return
        if index >= self.len_list or index < 0:
            print('Нет элемента с таким индексом')
        temp = self.head
        count = 0
        while index >= count + temp.length_arr and temp:
            count += temp.length_arr
            temp = temp.next
        ind = index - count
        del temp.array[ind]
        temp.length_arr -= 1
        self.len_list -= 1


    def delete_value(self, value):
        if self.len_list == 0:
            return
        ind = self.search_value(value)
        while ind >= 0:
            self.delete_index(ind)
            ind = self.search_value(value)

    def delete_empty_arr(self):
        temp = self.head
        while temp.next != None:
            if (temp.next.length_arr == 0):
                if (temp.next.next != None):
                    temp.next = temp.next.next
                    temp = temp.next
                else:
                    temp.next = None

    def to_arr(self):
        temp = self.head
        arr_result = []

        while temp:
            arr_result.extend(temp.array)
            temp = temp.next
        return arr_result
