#include "scanner.h"

////////////////////
    string* vet;
    void print(Token*);
    void allocVetor();
    void freeVetor();
///////////////////

int main(int argc, char* argv[]) 
{
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    string input;
    
    //getline(cin, input);

    Scanner* scanner = new Scanner(argv[1]);

    allocVetor();

    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        print(t);
    }while (t->name != END_OF_FILE);

    delete scanner;
    freeVetor();
    
    return 0;
}

void allocVetor()
{
    vet = new string[29];

    vet[0] = "UNDEF";//0
    vet[1] = "ID";//1
    vet[2] = "INTEGERCONSTANT";//2
    vet[3] = "CHARCONSTANT";//3
    vet[4] = "STRINGCONSTANT";//4
    vet[5] = "PLUS"; //5
    vet[6] = "MINUS";//6
    vet[7] = "MULT";//7
    vet[8] = "DIV";//8
    vet[9] = "AS";//9
    vet[10] = "EQ";//10
    vet[11] = "NE";//11
    vet[12] = "GT";//12
    vet[13] = "GE";//13
    vet[14] = "LT";//14
    vet[15] = "LE";//15
    vet[16] = "AND";//16
    vet[17] = "OR";//17
    vet[18] = "NOT";//18
    vet[19] = "LPAR";//19
    vet[20] = "RPAR";//20
    vet[21] = "LBRACE";//21
    vet[22] = "RBRACE";//22
    vet[23] = "LBRACKET";//23
    vet[24] = "RBRACKET";//24
    vet[25] = "COMMA";//25
    vet[26] = "SEMICOLON";//26
    vet[27] = "ERROR_TOKEN";//27
    vet[28] = "END_OF_FILE";//28
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