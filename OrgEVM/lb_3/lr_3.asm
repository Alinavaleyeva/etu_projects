AStack SEGMENT STACK
	DW 12 DUP(?)
AStack ENDS

DATA SEGMENT
	a DW 0
	b DW 0
	i DW 0
	k DW 0
	i1 DW ?
	i2 DW ?
	res DW ?
DATA ENDS
	

CODE SEGMENT
	ASSUME CS: CODE, DS: DATA, SS: AStack

Main PROC FAR
	push DS ; подготовка сегмента стека и данных
	sub AX, AX
	push AX
	mov AX, DATA
	mov DS, AX
	
	mov dx, i ;подготовка -4i для дальнейших вычислений
	shl dx, 1 ; dx = 2 * i = 2i
	shl dx, 1 ; dx = 4i
	neg dx ; dx = -4i

	;проверка условия для ветвления
	mov ax, b 
	cmp a, ax ; сравниваем а и б
	jle F1LE; если а <= б то переходим к F1LE

	; случай a > b
	mov ax, dx ; ax = -4i
	add ax, 20 ; ax = -4i + 20
	mov i2, ax ; сохраняем i2 = -4i + 20
	mov ax, dx ; ax = -4i
	add ax, i ; ax = -4i + i = -3i
	add ax, i; ax = -3i + i = -2i
	add ax, 15 ; ax = 15 - 2i
	mov i1, ax ; сохраняем i1 = 15 - 2i
	jmp F1END ; переходим к концу первого оператора ветвления
	
F1LE: ; a <= b	
	mov cx, dx ; cx = -4i
	add cx, 6 ; cx = -4i + 6
	mov dx, cx ; dx = -4i + 6
	sub cx, i; cx = -5i + 6
	sub cx, i; cx = -6i + 6
	mov i2, cx ; сохраняем i2 = -6i + 6
	neg dx ; dx = -(-4i + 6) = 4i - 6
	sub dx, i; dx = 3i - 6
	add dx, 10; dx = 3i + 4
	mov i1, dx ; сохраянем i1 = 3i + 4
	
F1END: ; конец первого ветвления
	mov ax, i1 ; копируем i1 и i2 в РОН 
	mov bx, i2 ;?

F3:
	cmp k, 0 ; если k < 0, 
	jl F3E ; то переходим к F3L (f3 lower) 
	neg bx
	cmp bx, -6 ; если i2 >= -6
	jge I1GE ; переходим к I1GE
	mov res, -6 ; иначе res = -6
	jmp FIN ; завершаем п
	
F3E: 
	sub ax, bx ; i1 - i2
F3L:
	neg ax ; меняем знак i1-i2
	js F3L ; если i1-i2 < 0, то переходим к F3L и меняем знак ещё раз (проверяет SF)
	cmp ax, 2 ; if i1-i2>2 уходим (???)
	jl I1G; 
	mov res, 2 ; иначе ответ 2
	jmp FIN
I1G:
	mov res, ax
	jmp FIN
I1GE:
	mov res, bx
	
FIN:
	ret
Main ENDP
CODE ENDS
	END Main
