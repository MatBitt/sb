global _start
section .text
_start:
push dword AUX
call _LeerInteiro ; ---------------------- NAO FINALIZADO
push dword AUX 
call _EscreverInteiro ; ---------------------- NAO FINALIZADO
mov eax, 1
mov ebx, 0
int 80h
_EsqueceuStop:
mov EAX, 1
mov EBX, 0
int 80h
_overflow:
mov EAX, _msgovf
mov EBX, _tamovf
push EAX
push EBX
call _EscreverString
jmp _EsqueceuStop
_LeerInteiro:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
push ESI
mov EAX, _aux
mov EBX, 5
push EAX
push EBX
call _LeerString
movzx EAX, byte [_aux]
movzx EBX, byte [_menos]
cmp EAX, EBX
jne _positivo
_negativo:
mov EBX, _aux
inc EBX
movzx EDX, byte [_enter]
mov ECX, 2
sub EAX, 30h
neg EAX
inc EBX
cmp dword [EBX], EDX
je _fimloop
jmp _loop
_positivo:
mov EBX, _aux
movzx EDX, byte [_enter]
mov ECX, 2
sub EAX, 30h
inc EBX
cmp dword [EBX], EDX
je _fimloop
_loop:
mul dword [_dez]
movzx ESI, byte [EBX]
sub ESI, 30h
add EAX, ESI
inc EBX
cmp dword [EBX], EDX
je _fimloop
loop _loop
_fimloop:
mov dword [EBP + 8], EAX
pop ESI
pop EDX
pop ECX
pop EBX
pop EAX
leave
ret 4
_EscreverInteiro:
enter 0, 0
push EAX
push EBX
push ECX
push EDX
call _calcula_tam
mov EAX, 4
mov EBX, 1
mov ECX, _aux
mov EDX, [_tamint]
int 80h
pop EDX
pop ECX
pop EBX
pop EAX
leave
ret 4
_calcula_tam:
push EAX
push EBX
push ECX
push EDX
push ESI
mov ECX, 0
mov EBX, [EBP + 8]
mov EAX, [EBX]
_contagem:
inc ECX
cdq
div dword [_dez]
cmp EDX, 0
add EDX, 30h
push EDX
jne _contagem
pop EDX
add EAX, 30h
push EAX
mov ESI, _aux
mov dword [_tamint], ECX
call _pop
pop ESI
pop EDX
pop ECX
pop EBX
pop EAX
ret
_pop:
pop EAX
mov dword [ESI], EAX
inc ESI
loop _pop
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
movzx EAX, byte [_aux]
mov EBX, dword [EBP + 8]
mov [EBX], EAX
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
leave
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
_tamint: resd 2
AUX: resd 20 
section .data
_menos: db '-'
_msgovf: db 'A operacao deu overflow!'
_tamovf: equ $-_msgovf
_enter: db 0dh, 0ah 
_dez: dd 10
