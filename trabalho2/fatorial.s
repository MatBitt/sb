global _start
section .text
_start:
INPUT N   ----- NAO TRADUZIDO
mov EAX, dword [N]
FAT: sub EAX, dword [ONE]
cmp EAX, 0
je FIM
mov dword [AUX+8], EAX
imul dword [MULTN+2]
mov dword [N+1], EAX
mov EAX, dword [AUX+20]
jmp FAT
FIM: OUTPUT N   ----- NAO TRADUZIDO
mov eax, 1
mov ebx, 0
int 80h
_LeerInteiro:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
call LeerString _aux, 5
mov AL, byte [_aux]
cmp AL, [_menos]
je _negativo
cmp AL, [_mais]
je _positivo

pop EDX
pop ECX
pop EBX
pop EAX
leave
ret 4
_EscreverInteiro:
ret
_LeerChar:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
mov EAX, 3
mov EBX, 0
mov ECX, _aux
mov EDX, 2
int 80h
movz dword [EBP + 8], byte [_aux]
pop EDX
pop ECX
pop EBX
pop EAX
leave
ret 4
_EscreverChar:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
mov EAX, 4
mov EBX, 1
mov ECX, dword [EBP + 8]
mov EDX, 1
int 80h
pop EDX
pop ECX
pop EBX
pop EAX
ret 4
_LeerString:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
mov EAX, 3
mov EBX, 0
mov ECX, dword [EBP + 12]
mov EDX, dword [EBP + 8]
int 80h
pop EDX
pop ECX
pop EBX
pop EAX
leave
ret 8
_EscreverString:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
mov EAX, 4
mov EBX, 1
mov ECX, dword [EBP + 12]
mov EDX, dword [EBP + 8]
int 80h
pop EDX
pop ECX
pop EBX
pop EAX
leave
ret 8
section .bss
_aux: resd 101
AUX: resd 10 
N: resd 5 
section .data
_menos: db '-'
_mais: db '+'
_enter: db 0dh, adh 
ONE: dd 1 
