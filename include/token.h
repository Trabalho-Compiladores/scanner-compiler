#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,

    ID,
    INTEGERCONSTANT,
    CHARCONSTANT,
    STRINGCONSTANT,
    
    PLUS,// +
    MINUS,// -
    MULT,// *
    DIV,// '/'

    AS,// =
    EQ,// ==
    NE,//!=

    GT,// >
    GE,// >=
    LT,// <
    LE,// <=

    AND,// &&
    OR,// ||
    NOT,// !

    LPAR,// (
    RPAR,// )
    LBRACE, // {
    RBRACE, // }
    LBRACKET, // [
    RBRACKET, // ]

    COMMA,// ','
    SEMICOLON, // ';'
    
    CHAR,
    INT,
    VOID,
    IF,
    ELSE,
    WHILE,
    FOR,
    RETURN,
    
    ERROR_TOKEN,
    END_OF_FILE
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
            
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};

#endif