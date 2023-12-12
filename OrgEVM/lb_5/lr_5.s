.equ a 22 # 2+3+8+4+0+5
.equ b 7 # len("Валеева")
.equ c 5 # len("Алина")
.equ x_1 10
.equ y_1 73
.equ z_1 -6
.equ x_2 -14
.equ y_2 55
.equ z_2 64

.data
	my_func: .string "R = ((x & (-a)) ^ (y >> c)) + (z << b)\n"
	const_values: .string "my const values: a = 22, b = 7, c = 5\n"

	newline: .string "\n"
	str_x1: .string "x1 = "
	str_x2: .string "x2 = "
	str_y1: .string "y1 = "
	str_y2: .string "y2 = "
	str_z1: .string "z1 = "
	str_z2: .string "z2 = "
	line_end: .string "\n"
	result: .string "Answer: {r1, r2} = "
	separator: .string ", "

.text
    j start

    print:
	
	    li a7, 4 #печать строки
		ecall
	
		mv a0, a1 #печать числа
		li a7 1
		ecall
		
		li a7, 4 # печать Enter
		la a0, line_end
		ecall
		ret
    
    start:
    
		# для начала напечатаем все значение введенных переменных, константы a, b, c зафиксированы в одной строке, т.к. она несменяемы
		la a0, my_func # загружаем адрес строки
		li a7, 4 # аргумент 4 в регистре a7 нужен для вывода строки в консоль
		ecall
		
		la a0, const_values # строка, содержащая константы. Не беру из регистров s0,s1,s2, так как это несменяемые данные
		li a7, 4 
		ecall
		
		
		la a0, str_x1  # печать x1
		la a1, x_1
		jal print
		
		la a0, str_y1  # печать y1
		la a1, y_1
		jal print

		la a0, str_z1  # печать z1
		la a1, z_1
		jal print
		
		la a0, str_x2  # печать x2
		la a1, x_2
		jal print
		
		la a0, str_y2  # печать y2
		la a1, y_2
		jal print

		la a0, str_z2  # печать z2
		la a1, z_2
		jal print

		# выполнение функции R
		li a2, x_1 # загружаем значения в регистры
		li a3, y_1
		li a4, z_1
		li a5, x_2
		li a6, y_2
		li a7, z_2

		call calc
		
		# выводим результат 
		la a0, result # печатаем строку
		li a7, 4
		ecall

		li a7, 1 
		mv a0, a1  # r1 находится в регистре a1, откуда мы его копируем в a0 для печати
		ecall

		li a7, 4
		la a0, separator 
		ecall

		li a7, 1 
		mv a0, a2 # r2 находится в регистре a2, откуда мы его копируем в a0 для печати
		ecall

		li a7, 4 
		la a0, line_end 
		ecall

		# Выход из программы 
		li a7, 10  # выход через аргумент 10 
		ecall

		calc: # подсчет моего выражения

			addi s0, zero, a #s0 = a
			addi s1, zero, b #s1 = b
			addi s2, zero, c #s2 = c
			neg s0, s0 #в s0 лежит a -> (-a)

			# x1 в a2, y1 в a3, z1 в a4
			and s3, a2, s0 # x&(-a) -> s3
			sra s4, a3, s2 # y>>c -> s4
			xor s5, s3, s4 # (x&(-a)) ^ (y>>c) -> s5
			sll s6, a4, s1 # z<<b -> s6
			add a1, s5, s6 # (x&(-a)) ^ (y>>c) + (z<<b) -> a1 (в этом регистре 1-й ответ)
			

			# x2 в a5, y2 в a6, z2 в a7
			and s3, a5, s0 # x&(-a) -> s3
			sra s4, a6, s2 # y>>c -> s4
			xor s5, s3, s4 # (x&(-a)) ^ (y>>c) -> s5
			sll s6, a7, s1 # z<<b -> s6
			add a2, s5, s6 # (x&(-a)) ^ (y>>c) + (z<<b) -> a2 (в этом регистре 2-й ответ)

			jr x1
