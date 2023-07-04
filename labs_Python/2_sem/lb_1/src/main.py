def check_positive_int(num):
    return isinstance(num, int) and num > 0


def check_color(color):
    return color in ['r', 'g', 'b']


def check_bool(a):
    return isinstance(a, bool)  # isinstance проверка на класс, True False - тип bool


class Figure:
    def __init__(self, perimeter, area, color):
        if check_positive_int(perimeter) and check_positive_int(area) and check_color(color):
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError('Invalid value')


class Polygon(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, angle_count, equilateral, biggest_angle):
        super().__init__(perimeter, area, color)
        if check_positive_int(angle_count) and angle_count > 2 and check_bool(equilateral) and check_positive_int(biggest_angle):
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return self.area == other.area and self.perimeter == other.perimeter and self.angle_count == other.angle_count


class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self, perimeter, area, color, radius, diametr):
        super().__init__(perimeter, area, color)
        if check_positive_int(radius) and check_positive_int(diametr) and diametr == 2 * radius:
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}."

    def __add__(self):
        return self.area + self.perimeter

    def __eq__(self, other):
        return self.radius == other.radius


class PolygonList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, Polygon):
            super().append(p_object)
        else:
            raise TypeError(f"Invalid type {type(p_object)}")

    def print_colors(self):
        st = ""
        for i in range(
                len(self)):  
            st += f"{i + 1} многоугольник: {self[i].color}\n"
        print(st[:len(st) - 1])

    def print_count(self):
        print(len(self))


class CircleList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        arr = [i for i in iterable if isinstance(i, Circle)]
        super().extend(arr)

    def print_colors(self):
        st = ""
        for i in range(len(self)):
            st += f"{i + 1} окружность: {self[i].color}\n"
        print(st[:len(st) - 1])

    def total_area(self):
        Area = 0
        for i in self:
            Area += i.area
        print(Area)
