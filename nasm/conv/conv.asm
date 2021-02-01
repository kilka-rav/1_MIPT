global _start

section .bss
buf: resb 256 ; аллоцируем буфер размером 256 байт
buflen: equ $-buf
base_in: resq 1; основание входного числа
base_out: resq 1; основание для печати числа
number: resq 1; само число
section .rodata
hwstr: db '', 0dh, 0ah
hwsz: equ $-hwstr
error: db 'ERROR FOUND', 0dh, 0ah
errorsz: equ $-error
section .text


decode:
	; converts buffer to number in rax
	; адрес буфера - rsi
	; основание - rbx
	; результат - rax
	push rsi ; сохраняем регистры на стек
	push rdx
	push rcx
	xor rax, rax
	xor rdx, rdx
	xor rcx, rcx

.cycle:
	mov cl, [rsi] ; читаем байт из строки
	cmp cl, '0'
	jb .exit
	cmp cl, '9'
	ja .check_alpha
	sub cl, '0' ; сформировать инкремент 
	jmp .inc    ; идти дальше

.check_alpha: ;check 'a' - 'z'
	cmp cl, 'z'
	ja .exit
	cmp cl, 'a'
	jb .check_beta
	sub cl, 'a'-36
	jmp .inc

.check_beta: ; проверяем попадание в диап. 'A'-'Z'
	cmp cl, 'A'
	jb .exit
	cmp cl, 'Z'
	ja .exit
	; формируем инкремент
	sub cl, 'A'-10
	jmp .inc
.inc:
	; сдвигаем разряд
	mul rbx
	; прибавляем смещение
	add rax, rcx
	; двигаемся дальше по буферу
	inc rsi
	jmp .cycle
.exit:
	pop rcx
	pop rdx
	pop rsi
	ret
	
encode:
	; encode rsi -- конец буфера, rax (число) rbx (основание)
	mov BYTE [rsi], 0 ; конец строки
	mov rdi, rsi ; сохраняем адрес конца строки
.cycle:
	xor rdx, rdx
	div rbx;  [rdx, rax] / rbx ->  rdx (остаток), rax (частное)
	cmp dl, 9
	ja .process_alpha
	add dl, '0'
	jmp .proc

.process_alpha:
	cmp dl, 35
	ja .process_beta	
	add dl, 'A'-10
	jmp .proc
	
.process_beta:
	add dl, 'a'-36
	jmp .proc


.proc:	
	dec rsi
	mov [rsi], dl
	test rax, rax ; быстрый тест на 0
	jnz .cycle
	mov rax, rdi 
	sub rax, rsi ; количество символов -- в rax	
	inc rax ; не забываем символ 0 на конце 
	ret

read_buf:
	push rbx
	push rcx
	push rdx
	mov rax, 0x3 ; системный вызов read(rbx, rcx, rdx)
	mov rbx, 0x0 ; stdin	
	mov rcx, buf ;
	mov rdx, 256 ;
	; количество прочитанных байт возвращается в rax
	int 80h
	pop rdx
	pop rcx
	pop rbx
	ret

print_buf:
	mov rdx, rax ; количество выводимых символов -- в rdx
	mov rcx, rsi ; буфер - в rcx
	mov rax, 0x4 ; syscall write
	mov rbx, 0x1 ; to stdout	
	int 80h
	ret

_error:
	call _xor
	mov rax, 0x4 ; write
	mov rbx, 0x1 ; stdout
	mov rcx, error ; strlen
	mov rdx, errorsz ; size
	int 80h
	
	mov rax, 0x1 ; syscall exit(0) 
	ret

_xor: ; обнуляем регистры
	xor rbx, rbx
	xor rdx, rdx
	xor rax, rax
	xor rcx, rcx
	ret

strlen: ; после цикла переносим каретку на следующую строчку
	mov rax, 0x4 ; write(fd, buf, size)
        mov rbx, 0x1 ; stdout
        mov rcx, hwstr ; 
	mov rdx, hwsz ;
        int 80h

        mov rax, 0x1 ; syscall exit(0)
	ret	

_start:		
	; читаем основание по основанию 10		

.loop:	
	call read_buf ; читаем с клавиатуры
	mov BYTE [buf+rax], 0 ; обнуляем последний символ
	mov rbx, 10 ; загружаем базу в rbx
	mov rsi, buf ; а в rsi -- адрес глобального буфера
	call decode ; пытаемся распознать в строке число
	mov [base_in], rax ; сохранить в base_in
	cmp rax, 61
	ja .final_error
	; читаем число по основанию base_in
	call read_buf ;
	mov BYTE [buf+rax], 0
	mov rbx, [base_in]
	call decode
	mov [number], rax ; результат сохраняем в number

	; читаем основание по основанию 10
	call read_buf ;
	mov BYTE [buf+rax], 0
	mov rbx, 10
	mov rsi, buf
	call decode
	mov [base_out], rax
	cmp rax, 61
	ja .final_error

	; выводим число
	mov rbx, [base_out] ; основание -- в rbx
	mov rax, [number] ; само число -- в rax
	lea rsi, [buf+buflen-1] ; буфер -- в rsi
	call encode
	; результат -- в rsi
	; количество символов -- в rax
	call print_buf
	call _xor
	call strlen
	call _xor
	jmp .loop

.final_error:
	call _error
	jmp .final

.final:
	mov rax, 0x1
	mov rbx, 0x0
	int 80h
