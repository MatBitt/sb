#ifndef DIRETIVAS_H_INCLUDED
#define DIRETIVAS_H_INCLUDED

#include <iostream>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

map<string, vector<int>> getDiretivas(){
    map<string, vector<int>> diretiva;
    // diretiva = {operando, tamanho}
    diretiva["SECTION"] = {1, 0};
    diretiva["SPACE"] = {0, 1};
    diretiva["CONST"] = {1, 1};
    diretiva["EQU"] = {1, 0};
    diretiva["IF"] = {1, 0};
    diretiva["MACRO"] = {0, 0};
    diretiva["ENDMACRO"] = {0, 0};
    return diretiva;
}

#endif