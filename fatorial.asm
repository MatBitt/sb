SECTION tEXT
MUL_N: mACRO ;;;;;;;;;;;;;;
MULT N ;Ahhh muleeeeke



STORE N ; Ihaaaaa
ENDMACRO
INPUT N
LOAD N
FAT: SUB ONE
JMPZ FIM
STORE AUX
MUL_N 
LOAD AUX
JMP FAT
FIM: OUTPUT N
STOP
SECTION DATA
AUX: SPACE
N: SPACE
ONE: CONST 1