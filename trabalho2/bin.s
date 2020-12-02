global _start
section .text
_start:
mov EAX, 1
mov EBX, 0
int 80h
section .bss
section .data
