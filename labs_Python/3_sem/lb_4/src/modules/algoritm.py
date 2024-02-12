def algoritm_rabin_karp(pat, txt, q): #q - простое число
    d = 256 # мощность алфавита
    pattern_len = len(pat)
    text_len = len(txt)
    result = []
    hash_pattern = 0
    hash_text = 0
    h = d**(pattern_len - 1) % q

    if (pattern_len <= text_len):
    # вычисляем хеш-знчение для искомой строки и первого окна текста
        for i in range(pattern_len):
            hash_pattern = (d * hash_pattern + ord(pat[i])) % q
            hash_text = (d*hash_text + ord(txt[i])) % q
    else:
        print("Введен слишком большой паттер")

    for i in range(text_len - pattern_len + 1):
        flag = 1
        if hash_text == hash_pattern: #проверим - коллизия или правда искомая подстрока
            for j in range(pattern_len): # проходим посимвольно по паттерну
                if txt[i+j] != pat[j]:
                    flag = 0
                    break # коллизия
            if flag == 1:
                result.append(i)

        # вычисляем хеш-значение для следующего окна текста
        if i < text_len - pattern_len: #если оставшийся кусок текста меньше длины паттерна
            # для сдвига убираем уже ненужный символ и добавляем следующий символ строки текста
            hash_text = (d * (hash_text - ord(txt[i]) * h) + ord(txt[i + pattern_len])) % q

            # преобразуем отрицательные хэш-значение в положительные при необходимости
            if hash_text < 0:
                hash_text += q

    return result #массив с индексами вхождений подстроки в текст

