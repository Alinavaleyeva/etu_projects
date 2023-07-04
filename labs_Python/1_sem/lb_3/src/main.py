R, N, L = 1, 0, -1
table = {
    # начальное состояние
    'q_start': {
        ' ': [' ', R, 'q_start'],
        'a': ['a', N, 'q0'],
        'c': ['c', N, 'q0'],
        'b': ['b', N, 'q0']
    },
    # проверяется, есть ли символ b
    'q0':{
        ' ': [' ', L, 'q_find_1' ], # прописать удаление первого символа
        'a': ['a', R, 'q0'],
        'c': ['c', R, 'q0'],
        'b': ['b', R, 'q1']
    },
    # поиск первого символа (если нет b)
    'q_find_1': {
        'a': ['a', L, 'q_find_1'],
        'b': ['b', L, 'q_find_1'],
        'c': ['c', L, 'q_find_1'],
        ' ': [' ', R, 'q_del_1']
    },
    # удаление первого символа (если нет b)
    'q_del_1': {
        'a': [' ', N, 'q_end'],
        'b': [' ', N, 'q_end'],
        'c': [' ', N, 'q_end']
    },
    # что делать, когда встретили символ b
    'q1': {
        'a': ['0', R, 'q2'],
        'b': ['0', R, 'q2'],
        'c': ['0', R, 'q2'],
        ' ': [' ', L, 'q_special']
    },
    # второй символ после b
    'q2': {
        'a': ['0', R, 'q3'],
        'b': ['0', R, 'q3'],
        'c': ['0', R, 'q3'],
        ' ': [' ', L, 'q_special']
    },
    # частные случаи расположения b
    'q_special': {
        '0': [' ', N, 'q_end'], # если символ b предпоследний
        'b': [' ', N, 'q_end'], # если символ b последний
    },
    # нашли символ после двух удаляемых
    'q3': {
        'b': ['0', L, 'qbb'],
        'a': ['0', L, 'qaa'],
        'c': ['0', L, 'qcc'],
        ' ': [' ', L, 'q_replace_0']
    },
    # поиск символов после двух удаляемых
    'q5': {
        '0': ['0', R, 'q5'],
        'b': ['0', L, 'qbb'],
        'a': ['0', L, 'qaa'],
        'c': ['0', L, 'qcc'],
        ' ': [' ', L, 'q_replace_0']
    },
    # символы, замененные на 0 удаляем, пока не дойдем до конца слова
    'q_replace_0': {
        '0': [' ', L, 'q_replace_0'],
        'a': ['a', N, 'q_end'],
        'b': ['b', N, 'q_end'],
        'c': ['c', N, 'q_end']
    },
    # если нашли b
    'qbb':{
        '0': ['0', L, 'qbb'],
        'b': ['b', R, 'q_replace_b'],
        'a': ['a', R, 'q_replace_b'],
        'c': ['c', R, 'q_replace_b']
    },
    # замена на b
    'q_replace_b': {
        '0': ['b', R, 'q5']
    },
    # если нашли с
    'qcc': {
        '0': ['0', L, 'qcc'],
        'a': ['a', R, 'q_replace_c'],
        'b': ['b', R, 'q_replace_c'],
        'c': ['c', R, 'q_replace_c']
    },
    # замена на c
    'q_replace_c':{
        '0': ['c', R, 'q5']
    },
    # если нашли a
    'qaa': {
        '0': ['0', L, 'qaa'],
        'a': ['a', R, 'q_replace_a'],
        'b': ['b', R, 'q_replace_a'],
        'c': ['c', R, 'q_replace_a']
    },
    # замена на a
    'q_replace_a': {
        '0': ['a', R, 'q5']
    }
}

word = list(input())
state = 'q_start'
index = 0
while state != 'q_end':
    symbol, i, state = table[state][word[index]]
    word[index] = symbol
    index += i
print(*word, sep = '')