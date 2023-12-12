.equ a 22 # 2+3+8+4+0+5
.equ b 7 #strlen("Валеева")
.equ c 5 #strlen("Алина")
.equ threshold 0 # arr[8] + arr[5] + arr[7] == 582
.data

const_values: .string "My const values: a = 22, b = 7, c = 5, threshold = "
result: .string "Answer: {r1, r2} = "
array_values: .string "This is my array: "
separator: .string ", "
endl:	.string ".\n"
array:	.word	0,0,0,0,0,0,0,0,0,0

.text
j start

print_separator:
	li a7, 4
	la a0, separator
	ecall
	ret
	
start:

	li a7, 4
	la a0, const_values #печать констант
	ecall

	li a7, 1
	li a0, threshold
	ecall
	
	li a7, 4
	la a0, endl
	ecall
	
	la a0, array #здесь храниться адрес на массив
	li a1, 10 #а здесь кол-во элементов
	
	call fill_array # заполним массив числами по формуле
	call print_array # и напечатаем его
	
	la a0, array
	li s6, threshold
	call calc #функция дл вычисления результата
	
	# печатаем результат
	li a7, 4
	la a0, result
	ecall
	
	li a7, 1
	mv a0, a3 #res1
	ecall
	call print_separator

	li a7, 1
	mv a0, t0 #res2
	ecall
	li a7, 4
	la a0, endl
	ecall
	
	# выход из программы
	li a7, 10
	ecall

fill_array:  # функция заполнения массива
	mv t0, a0 # начало
	li t1, 1 #кол-во

	#arr[0] = a + b + c
	li s0, a
	addi s0, s0, b
	addi s0, s0, c
	sw s0, 0(t0) # записываем в t0 (массив)
	addi t0, t0, 4 # смещаемся

	fill_continuation:
		#array[i+1] = arr[i] + a+ b -c
	
		addi s0, s0, a
		addi s0, s0, b
		addi s0, s0, -c  
		
		sw s0, 0(t0) # записываем в t0
		
		addi t1, t1, 1 # кол-во 
		addi t0, t0, 4  # смещаем указатель
		blt t1, a1, fill_continuation # если t1<a1 (пока не достигли нужного кол-во эл-ов) -> fill_continuation
	ret

print_array:
	
	mv t0, a0
	li t1, 0
	
	li a7, 4
	la a0, array_values
	ecall
	
	print_continuation:
		li a7, 1
		lw a0, 0(t0)
		ecall

		addi t1, t1, 1
		addi t0, t0, 4

		beq a1, t1, skip
		
		li a7, 4
		la a0, separator
		ecall

	skip:
		blt t1, a1, print_continuation 

	li a7, 4
	la a0, endl
	ecall
	ret
	
# если (arr[8] + arr[5] + arr[7] != threshold), то (res1 = arr[7] | arr[4]), иначе (res2 = arr[8] - b) 
# a0: адрес массива
# s6: threshold 
# a3: res1 
# t0: res2
calc:

	# 0 в регистрах с ответами
	mv a3, zero #res1
	mv t0, zero # res2

	lw s1, 32(a0) # s1 = arr[8]; 8*4
	lw s2, 20(a0) # s2 = arr[5] ;5*4
	add s1, s1, s2 # s1 += s2 (8+5)
	lw s2, 28(a0) # s2 = arr[7] ;7*4
	add s1, s1, s2 # s1 += s2 ; arr[8] + arr[5] + arr[7]

	bne s1, s6, res1 # если s1 != s6 то res1

	#иначе (res2 = arr[8] - b)  
	lw t0, 32(a0) # a4 = arr[8]
	addi t0, t0, -c # t0 = a4 - c
	j endif
	
	res1:  #res1 = arr[7] | arr[4]
		lw t1, 16(a0) # t1 = arr[4]
		lw s2, 28(a0) # s2 = arr[7]
		or a3, t1, s2 # a3 = t1|s2
	endif:
		ret
