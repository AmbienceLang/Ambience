%macro stdout 1
		mov rax, 1
		mov rdi, 1
		mov rsi, %1
		mov rdx, 256
		syscall
%endmacro

%macro statedump
		push rax
		push rbx
		push rcx
		push rdx
		push rsi
		push rdi
%endmacro

; Make sure to clear anything on stack which lays on top of the dump before trying to retrieve the dump
%macro getdump
		pop rdi
		pop rsi
		pop rdx
		pop rcx
		pop rbx
		pop rax
%endmacro

%macro stdin
		mov rax, 0
		mov rdi, 0
		mov rsi, __in
		mov rdx, 256
		syscall
%endmacro

%macro exit 1
		mov rax, 60
		mov rsi, %1
		syscall
%endmacro
