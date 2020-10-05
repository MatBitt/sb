#ifndef UTILIDADE_H_INCLUDED
#define UTILIDADE_H_INCLUDED

#include <string>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

template <class Container>

void split(const string& linha, Container& cont){
    istringstream iss(linha);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}

void escreve_linha_no_arquivo(vector<string> palavras, ofstream& arquivo){
    int i;
    for(i = 0; i< (int) palavras.size(); i++){
        arquivo << palavras[i] + ' ';
    }
    if(palavras[i-1] != "\n") arquivo << endl;
}

#endif