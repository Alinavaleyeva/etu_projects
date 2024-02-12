from algoritm import algoritm_rabin_karp
import time

if __name__ == '__main__':
    my_pat = input()
    my_text = input()
    answer = algoritm_rabin_karp(my_pat, my_text,  101)
    print(*answer)
