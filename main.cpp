#include <iostream>
#include <string>
#include <cstring>
#include "include/scanner.h"
#include "include/parser.h"

using namespace std;


string* vet;
void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        cout << "Uso:\n";
        cout << "  ./compiler -s arquivo.mj   (modo scanner: exibe tokens)\n";
        cout << "  ./compiler -p arquivo.mj   (modo parser: análise sintática)\n";
        return 1;
    }

    string option = argv[1];
    char* filename = argv[2];

    if (option == "-s")
    {
        // MODO SCANNER
        Scanner* scanner = new Scanner(filename);
        allocVetor();
        Token* t;
        do
        {
            t = scanner->nextToken();
            print(t);
        } while (t->name != END_OF_FILE);
        delete scanner;
        freeVetor();
    }
    else if (option == "-p")
    {
        // MODO PARSER
        Parser* parser = new Parser(filename);
        parser->run();
        delete parser;
    }
    else
    {
        cout << "Opção inválida. Use -s ou -p.\n";
        return 1;
    }

    return 0;
}


void allocVetor()
{
    vet = new string[29];
    vet[0] = "UNDEF";
    vet[1] = "ID";
    vet[2] = "INTEGERCONSTANT";
    vet[3] = "CHARCONSTANT";
    vet[4] = "STRINGCONSTANT";
    vet[5] = "PLUS";
    vet[6] = "MINUS";
    vet[7] = "MULT";
    vet[8] = "DIV";
    vet[9] = "AS";
    vet[10] = "EQ";
    vet[11] = "NE";
    vet[12] = "GT";
    vet[13] = "GE";
    vet[14] = "LT";
    vet[15] = "LE";
    vet[16] = "AND";
    vet[17] = "OR";
    vet[18] = "NOT";
    vet[19] = "LPAR";
    vet[20] = "RPAR";
    vet[21] = "LBRACE";
    vet[22] = "RBRACE";
    vet[23] = "LBRACKET";
    vet[24] = "RBRACKET";
    vet[25] = "COMMA";
    vet[26] = "SEMICOLON";
    vet[27] = "ERROR_TOKEN";
    vet[28] = "END_OF_FILE";
}

void freeVetor()
{
    delete[] vet;
}

void print(Token* t)
{
    cout << "[" << vet[t->name];
    if (t->name == ID ||
        t->name == INTEGERCONSTANT ||
        t->name == CHARCONSTANT ||
        t->name == STRINGCONSTANT)
    {
        cout << ": " << t->lexeme;
    }
    cout << "]" << endl;
}