global _start
section .text
_start:
;Ainda não traduzi isso aqui
mov EAX, dword [N]
mov EBX, dword [AUX]
mov dword [N], EBX
FAT: sub EAX, dword [ONE]
cmp EAX, 0
je FIM
mov dword [AUX], EAX
imul dword [N]
jo _overflow
mov dword [N], EAX
mov EAX, dword [AUX]
jmp FAT
FIM: ;Ainda não traduzi isso aqui
mov EAX, 1
mov EBX, 0
int 80H
jmp _fim
_overflow:
mov EAX, 1
mov EBX, 1
mov ECX, _msgOvf
mov EDX, _tamMsgOvf
mov EAX, 1
mov EBX, 0
int 80H
_fim:
section .data
_msgOvf: db 'Ocorreu overflow!'
_tamMsgOvf: equ $-_msgOvf
ONE: dd 1
section .bss
AUX: resd 10
N: resd 2
