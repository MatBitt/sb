SECTION TEXT
MUL_N: MACRO 
MULT N
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
AUX: SPACE
N: SPACE
ONE: CONST 1