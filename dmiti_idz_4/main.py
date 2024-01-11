import random

field = [[2, -3],[-1, 2]] #заданное поле
#1 задание
def binary_generator(probability):
  return 0 if random.uniform(0, 1) < probability else 1

#для 2 задания
def all_experiments(n, probability_A, probability_B): # возвращает массив из n пар - результаты выбора строчки и столбца
   return [(binary_generator(probability_A), binary_generator(probability_B))
           for i in range(n)]
def experiments_to_points(experiments): # возвращает массив из результатов всех экспериментов
   answer_array = []
   for experiment in experiments:
       value = field[experiment[0]][experiment[1]]
       answer_array.append(value)
   return answer_array

#2.3
def calc_mathematical_expectation(points, events): # возвращает математическое ожидание
   return sum(point * occur for point, occur in zip(points, events))
def calc_variance(points, events): # Возвращает дисперсию
   return sum(event * (point - calc_mathematical_expectation(points, events)) ** 2 for point, event in zip(points, events))

#2 задание
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
   print(f"Мат ожидание: {calc_mathematical_expectation(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

#3 задание
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
   print(f"Мат ожидание: {calc_mathematical_expectation(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

#4 задание
def task4_1():
   print("Задание 4.1. Обучение с подкреплением")
   probability_A = 1 / 2
   probability_B = 1 / 4
   balls = [10, 10]  # изначально 10 шаров на 0 и 1 строчке
   count = 100
   # Обучение
   for i in range(count):
      experiment = binary_generator(probability_A), binary_generator(probability_B)
      points = field[experiment[0]][experiment[1]]
      if points > 0: # если в этой клетке положительное кол-во очков
         balls[experiment[0]] += points #в случае выигрыша помещает дополнительные шары того же цвета в количестве равном выигрышу в свою коробку
      probability_A = balls[0] / sum(balls)
   print(f"Вероятность выбора второй строчки после {count} экспериментов: {1 - probability_A}")
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
   print(f"Мат ожидание: {calc_mathematical_expectation(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

def task4_2():
   print("Задание 4.2. Обучение с наказанием")
   probability_A = 1/2  # Игрок A изначально выбирает строчку 1 с вероятностью 1/2
   probability_B = 1/4  # Игрок B выбирает столбец 1 с вероятностью 3/4
   balls = [100, 100]  # изначально 10 шаров на 0 и 1 строчке
   count = 100
   # Обучение
   for i in range(count):
      experiment = binary_generator(probability_A), binary_generator(probability_B)
      points = field[experiment[0]][experiment[1]]
      if points < 0:
         balls[experiment[0]] += points #вычитание = сложение с отрицательным points
      probability_A = balls[0]/sum(balls)
   print(f"Вероятность выбора второй строчки после {count} экспериментов: {1 - probability_A}")
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
   print(f"Мат ожидание: {calc_mathematical_expectation(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

def task4_3():
   print("Задание 4.3. Обучение с подкреплением обоих игроков")
   probability_A = 1/2  # Игрок A изначально выбирает строчку 0 с вероятностью 1/2
   probability_B = 1/2  # Игрок B изначально выбирает столбец 0 с вероятностью 1/2
   balls_A = [10,10]  # изначально 10 шаров на 0 и 1 строчке
   balls_B = [10, 10]  # изначально 10 шаров на 0 и 1 строчке
   count = 100
   # Обучение
   for i in range(count):
      experiment = binary_generator(probability_A), binary_generator(probability_B)
      points = field[experiment[0]][experiment[1]]
      if points > 0:
         balls_A[experiment[0]] += points #прибаляем шары игроку A
      elif points < 0:
         balls_B[experiment[1]] += abs(points) #прибавляем шары игроку B
      probability_A = balls_A[0]/sum(balls_A)
      probability_B = balls_B[0]/sum(balls_B)
   print(f"Вероятность выбора второй строчки игроком A после {count} экспериментов: {1 - probability_A}")
   print(f"Вероятность выбора второй строчки игроком B после {count} экспериментов: {1 - probability_B}")
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
   print(f"Мат ожидание: {calc_mathematical_expectation(points_values, events)}")
   variance = calc_variance(points_values, events)
   print(f"Дисперсия: {variance}")
   print(f"Теоретическое СКО: {variance ** 0.5}")
   print()

task2()
task3()
task4_1()
task4_2()
task4_3()
