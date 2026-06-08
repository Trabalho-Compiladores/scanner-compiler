#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>
#include <cstring>
#include "token.h"
#include "symboltable.h"

class Scanner 
{
    private: 
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int line;
        SymbolTable* st;
    
    public:
    //Construtor
        Scanner(string, SymbolTable*);

        int getLine();
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void lexicalError(string msg);
};

#endif