
min_run = 3
def insertion_sort(arr, start, end):
    for i in range(start+1, end):
        current = arr[i]
        sort_ind = i-1
        while sort_ind >= start and (pow(current, 2) < pow(arr[sort_ind], 2) or ((pow(current, 2) == pow(arr[sort_ind], 2) and current > arr[sort_ind]) )):
            arr[sort_ind+1] = arr[sort_ind]
            sort_ind -= 1
        arr[sort_ind+1] = current
def merge(arr, start, mid, end):
    left = arr[start:mid+1]
    right = arr[mid+1:end+1]
    i = j = 0
    k = start

    while i < len(left) and j < len(right):
        if pow(left[i], 2) < pow(right[j], 2) or (pow(left[i], 2) == pow(right[j], 2) and left[i] > right[j]):
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1
    while i < len(left):
        arr[k] = left[i]
        i += 1
        k += 1
    while j < len(right):
        arr[k] = right[j]
        j += 1
        k += 1

def get_len_run(arr, start):
    len_run = 2
    if start == len(arr)-1:
        return 1
    is_ascending = arr[start] <= arr[start + 1]

    i = start + 1
    while i < len(arr)-1 and (arr[i] <= arr[i+1] if is_ascending else arr[i] > arr[i+1]):
        len_run += 1
        i += 1
    if not is_ascending:
        arr[start:len_run+start] = reversed(arr[start:len_run+start])
    return len_run
def timesort(arr):
    start = 0
    count_part = 0
    while start < len(arr):
        len_run = get_len_run(arr, start)
        if len_run < min_run and len_run != 1:
            len_run = min(len(arr) - start, min_run)
        insertion_sort(arr, start, start+len_run)
        print(f'Part {count_part}:', *arr[start:(start+len_run)])
        start += len_run
        count_part += 1
    curr_size = min_run
    while curr_size < len(arr):
        for start in range(0, len(arr), 2*curr_size):
            mid = min(start + curr_size - 1, len(arr) - 1)
            end = min(start + 2*curr_size - 1, len(arr) - 1)
            merge(arr, start, mid, end)
        curr_size *= 2

