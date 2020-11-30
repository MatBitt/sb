global _start
section .text
_start:
INPUT N   ----- NAO TRADUZIDO
mov EAX, dword [N]
FAT: sub EAX, dword [ONE]
cmp EAX, 0
je FIM
mov dword [AUX+2], EAX
MULT N + 2   ----- NAO TRADUZIDO
mov dword [N+1], EAX
mov EAX, dword [AUX+5]
jmp FAT
FIM: OUTPUT N   ----- NAO TRADUZIDO
mov eax, 1
mov ebx, 0
int 80h
section .bss
AUX: resd 10 
N: resd 5 
section .data
ONE: dd 1 
