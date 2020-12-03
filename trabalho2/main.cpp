#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include "preprocessamento.h"
#include "tradutor.h"

using namespace std;

int main(int argc, char **argv){
   
    string arquivo_asm = (string)argv[argc-1];
    pre_processamento(arquivo_asm);
    traducao(arquivo_asm);
    arquivo_asm = arquivo_asm.substr(0, arquivo_asm.find(".asm")) + ".pre";
    remove(arquivo_asm.c_str());
}
