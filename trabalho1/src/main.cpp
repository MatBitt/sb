#include <iostream>
#include <string.h>
#include <map>
#include "preprocessamento.h"
#include "primeirapassagem.h"
#include "segundapassagem.h"

using namespace std;

int main(int argc, char **argv){
   
    map<string, int> tabela_de_simbolos;
    string arquivo_asm;
    string arquivo_pre;

    switch(argc){
        case 1:
            cout << "Numero de argumentos abaixo do esperado!";
            return 0;

        case 2:
            arquivo_asm = argv[argc-1];
            arquivo_pre = arquivo_asm.substr(0, arquivo_asm.find(".asm")) + ".pre";

            pre_processamento(arquivo_asm);
            tabela_de_simbolos = primeira_passagem(arquivo_pre);
            segunda_passagem(arquivo_pre, tabela_de_simbolos);
            break;
        
        case 3:
            if(string(argv[1]) == "-p"){
                arquivo_asm = argv[argc-1];
                pre_processamento(arquivo_asm);
            }else if(string(argv[1]) == "-o"){
                arquivo_pre = argv[argc-1];
                tabela_de_simbolos = primeira_passagem(arquivo_pre);
                segunda_passagem(arquivo_pre, tabela_de_simbolos);
            }else{
                cout << "Argumento invalido!" << endl;
                return 0;
            }
            break;

        default:
            cout << "Numero de argumentos acima do esperado" << endl;
    }

}
