#include <iostream>
#include <string.h>
#include <map>
#include "instrucoes.h"
#include "diretivas.h"
#define OPERANDOS 0
#define TAMANHO 1
#define CODIGO 2

using namespace std;

int main(int argc, char **argv){
    map<string, vector<int>> instrucao = getInstrucoes();
    cout << instrucao["ADD"][OPERANDOS] << endl;
    cout << instrucao["ADD"][TAMANHO] << endl;
    cout << instrucao["ADD"][CODIGO] << endl;
    map<string, vector<int>> diretiva = getDiretivas();
    cout << diretiva["SECTION"][OPERANDOS] << endl;
    cout << diretiva["SECTION"][TAMANHO] << endl;
}
