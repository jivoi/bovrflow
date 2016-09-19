global _start

section .text

_start:
	xor eax, eax
	push eax

	push 0x68732f2f		;//sh
	push 0x6e69622f		;/bin
	mov ebx, esp		;moving the pointer to "/bin//sh" to ebx

	push eax			;push 0 (=eax)
	mov edx, esp		;moving 0 to edx

	push ebx
	mov ecx, esp		;moving the pointer to "/bin//sh" to ecx

	mov al, 11
	int 0x80			;execv syscall

