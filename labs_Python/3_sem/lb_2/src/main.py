from my_sort import timesort

if __name__ == '__main__':
    n = int(input())
    arr = list(map(int, input().split()))
    timesort(arr)
    print("Answer:", *arr)