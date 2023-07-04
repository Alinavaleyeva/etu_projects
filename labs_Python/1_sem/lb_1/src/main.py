import numpy as np
from math import *


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] <= robot[0] <= point2[0]:
        if point1[1] <= robot[1] <= point4[1]:
            return True
        else:
            return False
    else:
        return False


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i != j:
                s1 = np.array([coefficients[i][:2], coefficients[j][:2]])
                s2 = np.array([-coefficients[i][-1], -coefficients[j][-1]])
                try:
                    np.linalg.solve(s1, s2)
                    result.append((i, j))
                except:
                    pass

    return result


def check_path(points_list):
    way = 0
    for x in range(len(points_list) - 1):
        coordinate1_1 = points_list[x][0]
        coordinate1_2 = points_list[x][1]
        coordinate2_1 = points_list[x + 1][0]
        coordinate2_2 = points_list[x + 1][1]

        array1 = np.array((coordinate1_1, coordinate1_2))
        array2 = np.array((coordinate2_1, coordinate2_2))
        distance = np.linalg.norm(array1 - array2)
        way += distance

    result = round(way, 2)
    return result