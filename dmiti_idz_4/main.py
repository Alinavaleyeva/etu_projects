import random

field = [
   [2, -3],
   [-1, 2]
]
#для 1 задания
def binary_generator(probability): #датчик случайных чисел
   if random.uniform(0, 1) < probability: #генерирует псевдослучайное число с плавающей точкой в заданном диапазоне
       return 0
   else:
       return 1

#для 2 задания
def points_from_one_exp(experiment): #принимает список и возвращает значение на поле
   return field[experiment[0]][experiment[1]]

#2.1
def n_experiments(n, probability_A, probability_B): # возвращает массив из n пар - результаты выбора строчки и столбца
   return [(binary_generator(probability_A), binary_generator(probability_B)) for i in range(n)]
def experiments_to_points(experiments): # возвращает массив из результатов всех экспериментов
   answer_array = []
   for i in experiments:
       answer_array.append(points_from_one_exp(i))
   return answer_array

#2.3
def calc_expected_value(points: list, occurs: list): # возвращает математическое ожидание
   return sum(point * occur for point, occur in zip(points, occurs))
def calc_variance(points: list, occurs: list): # Возвращает дисперсию
   return sum(occur * (point - calc_expected_value(points, occurs)) ** 2 for point, occur in zip(points, occurs))

def task2():
   print("Задание 2")
   p = 1 / 2 # Вероятность выбора столбца и строчки, равновероятно
   count = 5
   probability_A = p
   probability_B = p
   experiments_arr = n_experiments(count, probability_A, probability_B)
   points = experiments_to_points(experiments_arr)
   A_won = sum(points)
   print(f"Игрок А выиграл {A_won} очков")
   print(f"Среднее количество очков за игру у игрока А: {sum(points) / len(points)}")
   # события выбора
   events = [probability_A * probability_B, probability_A * (1 - probability_B), probability_B * (1 - probability_A),
             (1 - probability_A) * (1 - probability_B)]
   points_values = [point for row in field for point in row]
   print(
       f"Среднеквадратичное отклонение: {(sum((point - sum(points_values) / len(points_values)) ** 2 for point in points_values) / len(points_values)) ** 0.5}")
   print(f"Мат ожидание: {calc_expected_value(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

def task3():
   print("Задание 3")
   probability_A = 1 / 2 # Вероятность выбора строчки игроком А
   probability_B = 1 / 4 # Вероятность выбора столбца игроком Б
   count = 100
   experiments_arr = n_experiments(count, probability_A, probability_B)
   points = experiments_to_points(experiments_arr)
   A_won = sum(points)
   print(f"Игрок А выиграл {A_won} очков")
   print(f"Среднее количество очков за игру у игрока А: {sum(points) / len(points)}")
   # события выбора
   events = [probability_A * probability_B, probability_A * (1 - probability_B), probability_B * (1 - probability_A),
             (1 - probability_A) * (1 - probability_B)]
   points_values = [point for row in field for point in row]
   print(
       f"Среднеквадратичное отклонение: {(sum((point - sum(points_values) / len(points_values)) ** 2 for point in points_values) / len(points_values)) ** 0.5}")
   print(f"Мат ожидание: {calc_expected_value(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

task2()
task3()
