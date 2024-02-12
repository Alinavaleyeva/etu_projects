class Hash_table:
   def __init__(self, size_value):
       self.size = size_value
       self.hash_table = [[None, None] for _ in range(self.size)]

   def hash_func(self, key, i):
       hash_key = ((key**2 - 1) % self.size + 2*i + 5*(i**2) )
     
       return hash_key % self.size

   def insert(self, key, value):
       i = 0
       hash_key = self.hash_func(key, 0)
       while (self.hash_table[hash_key][0] is not None): #ячейка занята
           if self.hash_table[hash_key][0] == key: # но ключи совпали
               self.hash_table[hash_key][1] = value #перезаписываю
               return
           i += 1 #иначе ищу другую ячейку
           hash_key = self.hash_func(key, i)

       self.hash_table[hash_key][0] = key
       self.hash_table[hash_key][1] = value
   def print_table(self):
       for i in range(self.size):
           my_set = self.hash_table[i]
           if my_set[1] is not None:
                print(f"index: {i}, key: {my_set[0]}, value: {my_set[1]}")

   def return_element(self, ind):
       return self.hash_table[ind]

   def return_size(self):
       return self.size
