SECTION TEXT
MUL_N: MACRO 
MULT N + 2
STORE N + 1
    
     
   ; é noooois


ENDMACRO
INPUT N
LOAD N
  ; no problem duuuude

FAT:

   
    
 SUB ONE

;I've said no problem at all
JMPZ FIM
STORE AUX + 2
MUL_N 
LOAD AUX + 5
JMP FAT
FIM: OUTPUT N
STOP
SECTION DATA
AUX: SPACE 10
N: SPACE 5
ONE: CONST 1