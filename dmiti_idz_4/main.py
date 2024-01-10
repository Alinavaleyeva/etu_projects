import random

field = [[2, -3],[-1, 2]] #заданное поле
#1 задание
def binary_generator(probability):
  return 0 if random.uniform(0, 1) < probability else 1

#2 задание
def all_experiments(n, probability_A, probability_B): # возвращает массив из n пар - результаты выбора строчки и столбца
   return [(binary_generator(probability_A), binary_generator(probability_B)) for i in range(n)]
def experiments_to_points(experiments): # возвращает массив из результатов всех экспериментов
   answer_array = []
   for experiment in experiments:
       value = field[experiment[0]][experiment[1]]
       answer_array.append(value)
   return answer_array

#2.3
def calc_expected_value(points, events): # возвращает математическое ожидание
   return sum(point * occur for point, occur in zip(points, events))
def calc_variance(points, events): # Возвращает дисперсию
   return sum(event * (point - calc_expected_value(points, events)) ** 2 for point, event in zip(points, events))

def one_experiment(probability_A, probability_B):  # возвращает результат одного эксперимента в виде пары значений
   return binary_generator(probability_A), binary_generator(probability_B)


def task2():
   print("Задание 2")
   count = 100
   probability_A = 1 / 2 # Вероятность выбора столбца и строчки, равновероятно
   probability_B = 1 / 2 # Вероятность выбора столбца и строчки, равновероятно
   experiments_arr = all_experiments(count, probability_A, probability_B)
   points = experiments_to_points(experiments_arr)
   A_won = sum(points)
   print(f"Игрок А выиграл {A_won} очков")
   print(f"Среднее количество очков за игру у игрока А: {sum(points) / len(points)}")
   # события выбора
   events = [probability_A * probability_B, probability_A * (1 - probability_B), probability_B * (1 - probability_A),
             (1 - probability_A) * (1 - probability_B)]
   points_values = [point for row in field for point in row]
   print(f"Среднеквадратичное отклонение: {(sum((point - sum(points_values) / len(points_values)) ** 2 for point in points_values) / len(points_values)) ** 0.5}")
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
   experiments_arr = all_experiments(count, probability_A, probability_B)
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
