%macro stdout 1
		mov rax, 1
		mov rdi, 1
		mov rsi, %1
		mov rdx, 256
		syscall
%endmacro

%macro statedump 0
		push rax
		push rbx
		push rcx
		push rdx
		push rsi
		push rdi
%endmacro

%macro declare 3
		%1: %2 %3
%endmacro

; Needs fix
%macro ambhello 0
		%%__message: db 'Welcome to Ambience, looks like your on the Linux kernel using a x86_64 CPU!', 10
		stdout %%__message
%endmacro

; Make sure to clear anything on stack which lays on top of the dump before trying to retrieve the dump
%macro getdump 0
		pop rdi
		pop rsi
		pop rdx
		pop rcx
		pop rbx
		pop rax
%endmacro

%macro stdin 0
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
