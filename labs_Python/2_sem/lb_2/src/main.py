class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.__next__ = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self.__next__ is not None:
            return f"data: {self.get_data()}, next: {self.__next__.get_data()}"
        else:
            return f"data: {self.get_data()}, next: None"


class LinkedList:
    def __init__(self, head=None):
        self.__head__ = head
        if head is None:
            self.__length = 0
        else:
            self.__length = 1

    def __len__(self):
        return self.__length

    def append(self, element):
        self.__length += 1
        if self.__head__ is None:
            self.__head__ = Node(element)
        else:
            tmp = self.__head__
            while tmp.__next__ is not None:
                tmp = tmp.__next__
            last_elem = Node(element)
            tmp.__next__ = last_elem

    def __str__(self):
        data = []
        tmp = self.__head__
        while tmp is not None:
            data.append(str(tmp))
            tmp = tmp.__next__
        return f"LinkedList[length = {self.__length}, [{'; '.join(data)}]]" if data else "LinkedList[]"

    def pop(self):
        if self.__head__ is None:
            raise IndexError("LinkedList is empty!")
        self.__length -= 1
        if self.__length == 0:
            self.__head__ = None
        else:
            temp = self.__head__
            while temp.__next__.__next__ is not None:
                temp = temp.__next__
            temp.__next__ = None

    def delete_on_start(self, n):
        tmp = self.__head__

        if self.__length < n or n < 1:
            raise KeyError(f"{n} doesn't exist!")

        elif n == 1:
            self.__head__ = tmp.__next__
        else:
            count = 1
            while count + 1 < n:
                tmp = tmp.__next__
                count += 1
            tmp.__next__ = tmp.__next__.__next__
        self.__length -= 1

    def clear(self):
        self.__length = 0
        self.__head__ = None
