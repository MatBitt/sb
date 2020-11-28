SECTION TEXT
MUL_N: MACRO 
MULT N + 2
STORE N
    
     
   ; é noooois


ENDMACRO
INPUT N
LOAD N
  ; no problem duuuude

FAT:

   
    
 SUB ONE

;I've said no problem at all
JMPZ FIM
STORE AUX
MUL_N 
LOAD AUX
JMP FAT
FIM: OUTPUT N
STOP
SECTION DATA
AUX: SPACE 10
N: SPACE 5
ONE: CONST 1