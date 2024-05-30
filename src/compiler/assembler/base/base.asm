%include "../macro/linux64.asm"

section .bss
		__in resb 256

section .text
		global _start

_start:
		ambhello
		exit 0
