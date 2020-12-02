#include <iostream>
#include <string.h>
#include <map>
#include "preprocessamento.h"
#include "tradutor.h"

using namespace std;

int main(int argc, char **argv){
   
    string arquivo_asm = (string)argv[argc-1];
    pre_processamento(arquivo_asm);
    traducao(arquivo_asm);
}
