AStack SEGMENT STACK
DW 512 DUP(?) ; allocate 1 kb for stack
AStack ENDS

DATA SEGMENT
	header DB 64h, 0 ; header for input string
	InputString DB 64h DUP('?'), 0dh, 0ah, '$' ; память для вводимой строчки
	ProcessedStr DB 190h DUP('?'), 0dh, 0ah, '$' ; буфер для обрабатываемой строки (размер больше,т к больше символов)
	HelloMessage DB 'Hello! Input your string: ', 0dh, 0ah, '$'
	Waiting DB 'Press any ke...', 0dh, 0ah, '$'
	overwritten DB 0 ; flag which shows if 9h is overwritten
	KEEP_IP DW 0 ;хранит смещение прерывания
	KEEP_CS DW 0 ;хранит сегмент заменяемого прерывания (9h)
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:AStack

; функция печати строки
WriteMsg proc near
	push ax
	mov ah,9
	int 21h
	pop ax
	ret
WriteMsg endp

ReadString PROC ; функция чтения введенной строки

; сохраним регистры
	push ax
	push bp
	push bx

	mov ah, 0ah ; ;функция ввода строки
	push DX ; смещение заголовка строки
	int 21h
	pop bp ; помещаем заголовок в bp
	xor bx, bx ; обнуляем bx
	mov bl, ds:[bp + 1] ; теперь в bl факт.размер введенных символов
	add bx, bp ; bx указывает на конечный введенный символ
	add bx, 2 ; bx указывает на байт, следующий за финальным 0dh
	mov word ptr [bx + 1], 240ah ;обавляем в конец строки 0ah и '$'(перевод строки и конец строки)

	;восстановим регистры
	pop bx
	pop bp
	pop ax
	ret
ReadString ENDP

; ф-я восстановления прерывания
RestoreInterruption PROC
	push ax
	push ds
	push dx

	cmp overwritten, 0 ; если уже восставновили прерывание - то делать нечего
	jz already_restored
	; восстановление оригинального 9h
	push ds ; сохраняем адрес сегмента данных в стэке

	mov dx, KEEP_IP ; записываем в dx смещение оригинального прерывания 9h
	mov ax, KEEP_CS ; записываем в ax сегмент оригинального прерывания 9h
	mov ds, ax ; записываем в ds ax (сегмент оригинального прерывания 9h)
	mov ah, 25h ; функция для замены вектора
	mov al, 9h ; номер вектора прерывания
	int 21h ; восстанавливаем 9h

	pop ds ; восстанавливаем сегмент данных

	mov overwritten, 0 ; прерывание восстановили

	already_restored:
	; восставновление регистров
	pop dx
	pop ds
	pop ax
	ret
RestoreInterruption ENDP

ChangeInterruption PROC
	push ax
	push bx
	push es

	cmp overwritten, 1 ; если прерывание уже перезаписано, то делать нечего
	je already_changed ; прыгаем в нужную функцию

	; запоминание СЕГМЕНТ:СМЕЩЕНИЕ вектора прерывания с номером 9h
	mov ah, 35h ; функция для получения СЕГМЕНТ:СМЕЩЕНИЕ вектора прерывания
	mov al, 9h ; номер вектора прерывания
	int 21h ; прерывание записывает сегмент прерывания в es, а смещение в bx
	mov KEEP_IP, bx ; запоминаем смещение в KEEP_IP
	mov KEEP_CS, es ; запоминаем сегмент в KEEP_ES

	; замена прерывания 9h на пользовательское
	push ds ; сохраняем адрес сегмента данных в стэке
	mov dx, offset MyFunction ; записываем смещение моей функции в dx
	mov ax, seg MyFunction ; записываем сегмент моей функции в ax
	mov ds, ax ; записываем в ds значение ax
	mov ah, 25h ; функция для замены вектора
	mov al, 9h ; номер вектора для замены
	int 21h ; заменяем 9h

	pop ds ; восстанавливаем сегмент данных

	mov overwritten, 1; теперь прерывание перезаписано

	already_changed:
	pop es
	pop bx
	pop ax
	ret
ChangeInterruption ENDP

; функция обработки строки, выполнение работы прерыванием 9h
MyFunction PROC
	;восстановление регистров
	push ax
	push si
	push di
	push dx

	mov ax, DATA ; записываем сегмент данных в ax
	mov ds, ax ; инициализируем ds
	mov es, ax ; и es

	cld ; сброс флага для продвидения вперед
	lea si, InputString ; в si сохраняем адрес моей входной строки
	lea di, ProcessedStr ; а в di - выводимой (обрабатываемой)

	strproc:
	lodsb ; побайтово загружаем входную строку для обработки
	cmp al, '$' ;сравниваем с символом конца строки
	je end_proc ; если он - то переходим в конец
	cmp al, '0' ; если текущий символ по ASCII меньше 0
	jl notDigit
	cmp al, '9' ;или же больше 9 -> это не цифра
	jg notDigit ; ничего с ним не делаем, просто пишем в новую строку

	; иначе - это число
	mov dl, al ; скопируем оригинал числа
	sub dl, '0' ; через ASCII делаем число-строку числом
	mov ah, 1000b ; идея преобразования - через маску 8=1000(2)

		mov bx, offset ProcessedStr; копируем смещение обрабатываемой строки
		cmp di, bx ; сравниваем текущее смещение
		je skip
		mov al, ' ' ; пробел перед числом
		stosb; запишем содержимое(пробел) из al в память(пробел)

		skip:
		mov cl, 4
		mov bh, 1

		push di

		convert:
		mov dh, ah; скопируем маску в dh
		and dh, dl ; тут происходит побитовое сравнение маски с числом (в2) &
		cmp dh, 0 ; сравним полученный результат (он записывается в dh) с 0
		jnz one; если не 0

		zero: ; обработка случая с 0
			mov al, '0' ; в al копируем 0
			stosb; запишем содержимое из al в память(пробел)

			cmp bh, 0 
			je next ;число 0 - пишем 0
			dec di ; если нет, то это 0 в начале числа, его убираем
			jmp next; переход к следующему

		one:
			mov al, '1' ; тогда это 1, которую сохр в нашу строку
			stosb ; запишем содержимое из al в память
			mov bh, 0

			next: ; переход дальше
			shr ah, 1; через сдвиг право делим маску на 2(1000->100->10..)
		loop convert; дальше побитово сравниваем (пока маска не 0)

		convert_end: ; маска 0, дошли до конца числа
			pop dx
			cmp di, dx ;
			jnz add_space; если не равно, то пробел
			inc di ; +1

			add_space:
			; когда маска 0, не забываем отделить полученное число пробелом
			mov al, ' '

		;ф-я, если не число
		notDigit:
			stosb ; просто берем символ из al
			jmp strproc ; и продолжаем читать строку

		end_proc: ; конец чтения строки
		stosb; запишем содержимое из al в память

		mov dx, offset ProcessedStr ; сохраняем смещение ProcessedStr в dx
		call WriteMsg ; печать строки

		mov al, 20h ; для разрешения обработки прерываний
		out 20h, al ; более низким уровнем, чем обработанное

		pop dx
		pop di
		pop si
		pop ax
		
		call RestoreInterruption ; ф-я восстановления прерывания

		jmp dword ptr [KEEP_IP] ; вызываем оригинальное прерывание 9h
		

MyFunction ENDP

    ; Головная процедура
    Main PROC FAR
    push ds ;сохраняем в стэк адрес начала PSP
    sub ax, ax ; обнуляем регистр ax
    push ax ; сохраним нулевое смещение
    mov ax, DATA ; переносим в решистра сегмент data
    mov ds, ax ; иниц-я ds
    mov es, ax ; и es

    ; тут печатаем строку
    mov dx, offset HelloMessage ; копирование смещения HelloMessage в dx
    call WriteMsg ; вызываем ф-ю печати

    ; теперь считываем строку пользователя
    mov dx, offset header ; копируем заголовок смешения
    call ReadString

    ;выведем на жкран строчку, введенную пользователем
    mov dx, offset InputString
    call WriteMsg

    ; задержка по времени перед заменой 9h
    mov cx, 0eh ; 14 * 65535 мкс задержки
    mov dx, 0ffffh ; ещё 65535 мкс задержки
    mov ah, 86h ; функция "ждать"
    int 15h ; вызов функции ожидания

    ;через ф-ю для замены прерываний меняем 9h
    call ChangeInterruption

    ;печатаем строку-ожидания нажатия
    mov dx, offset Waiting
    call WriteMsg
    ; ждем ввод
    mov ah, 0 ; 0 - это команда для считывания одного ключа (al будет иметь ascii-код, а ah - флаги)
    int 16h ; ожидание нажатия кнопки

    ;done:
    ; восстанавляем прерывание в любом случае
    ret
    Main ENDP
    CODE ENDS
    END Main

Ещё
