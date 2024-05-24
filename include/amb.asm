; This file gets included before any sections are loaded to prevent any corruptions, it servers as a library file for easier syscalls.

%macro output 1
    __out: %1
    __outLen equ $-__out

    mov rax, 1
    mov rdi, 1
    mov rsi, __out
    mov rdx, __outLen
    syscall
%endmacro

%macro input 1
    output %1

    mov rax, 0
    mov rdi, 0
    mov rsi, __in
    mov rdx, 256
    syscall
%endmacro

%macro s_reg
    push rax
    push rbx
    push rcx
    push rdx
    push r10
    push r9
    push r8
    push rsi
    push rdi
%endmacro

%macro r_reg
    pop rdi
    pop rsi
    pop r8
    pop r9
    pop r10
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro flush_in
    mov [__in], 0
%endmacro

%macro exit 1
    mov rax, 60
    mov rdi, %1
    syscall
%endmacro