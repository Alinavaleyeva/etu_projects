import random
import time
from hash_table import Hash_table

def main():
    ht = Hash_table(10)
    print("Введите число от 0 до 100: ")
    n = int(input())
    start_time = time.time()
    for i in range(n):
        key = random.randint(0, 10)
        value = random.randint(-1000, 1000)
        ht.insert(key, value)
    end_time = time.time()
    execution_time = end_time - start_time
    ht.print_table()
    answer = ht.return_element(2)
    print(answer)
    print(f"Время выполнения: {execution_time} секунд")

if __name__ == '__main__':
    main()
