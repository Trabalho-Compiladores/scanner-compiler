#include "../include/scanner.h"    

//Função para verificar 


//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in); //input = nome arquivo  && inputFile = leitura do arquivo
    string line;

    if (inputFile.is_open()) // verificar se o arquivo foi aberto 
    {
        while (getline(inputFile,line) ) // ler linha por linha
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    //cout << this->input;

}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* Scanner::nextToken()
{
    string lexeme = "";
    int state = 0;//estado inicial
    Token* tok;

while (true)
    {
        switch (state)
        {
            case 0:
                lexeme = "";

                if (pos >= input.size())
                {
                    tok = new Token(END_OF_FILE);
                    return tok;
                } 
                else if (isspace(input[pos])) // Ignorar espaços
                {
                    if (input[pos] == '\n')
                        line++;

                    pos++;
                    state = 0;
                    break;
                }
                else if (pos < input.size() && input[pos] == '/')
                {
                    state = 1;
                    pos++;
                    break;
                }
                else if (isalpha(input[pos]))
                {
                    lexeme += input[pos];
                    pos++;
                    state = 6;
                    break;
                }
                else if (isdigit(input[pos]))
                {
                    lexeme += input[pos];
                    pos++;
                    state = 8;
                    break;
                }
                else if(pos < input.size() && input[pos] == '+')
                {
                    state = 10;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '-')
                {
                    state = 11;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '*')
                {
                    state = 12;
                    pos++;
                    break;
                }
                else if (pos < input.size() && input[pos] == '=')
                {
                    state = 13;
                    pos++;
                    break;
                }
                else if (pos < input.size() && input[pos] == '<')
                {
                    state = 16;
                    pos++;
                    break;
                }
                else if (pos < input.size() && input[pos] == '>')
                {
                    state = 19;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '!')
                {
                    state = 22;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '&')
                {
                    state = 25;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '|')
                {
                    state = 27;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '(')
                {
                    state = 29;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == ')')
                {
                    state = 30;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '{')
                {
                    state = 31;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '}')
                {
                    state = 32;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '[')
                {
                    state = 33;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == ']')
                {
                    state = 34;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == ',')
                {
                    state = 35;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == ';')
                {
                    state = 36;
                    pos++;
                    break;
                }
                else if (pos < input.size() && input[pos] == '\'')
                {
                    state = 37;
                    pos++;
                    break;
                }
                else if(pos < input.size() && input[pos] == '"')
                {
                    state = 40;
                    pos++;
                    break;
                }
                
                else
                    {
                        lexicalError("erro lexico");
                        return new Token(ERROR_TOKEN);
                    }

                break;

            case 1:
                if (pos >= input.size())
                {
                    state = 5; // trata como DIV
                    break;
                }

                if (input[pos] == '/')
                {
                    state = 2; // comentário de linha
                    pos++;
                }
                else if (input[pos] == '*')
                {
                    state = 3; // comentário de bloco
                    pos++;
                }
                else
                {
                    state = 5; // operador DIV
                }
                break;
            
            case 2:
                if (pos >= input.size())
                {
                    state = 0; // terminou comentário no EOF
                    break;
                }

                if (input[pos] == '\n')
                {
                    line++;
                    pos++;
                    state = 0;
                }
                else
                {
                    pos++;
                }
                break;
            case 3:

                if (pos >= input.size())
                {
                    lexicalError("comentario de bloco nao fechado");
                    return new Token(ERROR_TOKEN);
                }

                if (input[pos] == '\n')
                    line++;

                if (input[pos] == '*')
                {
                    pos++;
                    state = 4;
                }
                else
                {
                    state = 3;
                    pos++;
                }
                break;
            case 4:

                if (pos >= input.size())
                {
                    lexicalError("comentario de bloco nao fechado");
                    return new Token(ERROR_TOKEN);
                }

                if(input[pos] == '/')
                {
                    pos++;
                    state = 0;
                }
                else if(input[pos] == '*')
                {
                    pos++;
                    state = 4;
                }
                else{
                    pos++;
                    state = 3;
                }
                break;
            case 5:
                tok = new Token(DIV);
                return tok;
            case 6:
                if (pos < input.size() && (isalnum(input[pos]) || input[pos] == '_'))
                {
                    lexeme += input[pos];
                    pos++;
                }
                else
                {
                    state = 7;
                }
                break;
            case 7:
                tok = new Token(ID);
                tok->lexeme = lexeme;
                return tok;
            case 8:
                if (pos < input.size() && isdigit(input[pos]))
                {
                    lexeme += input[pos];
                    pos++;
                }
                else if (pos < input.size() &&
                        (isalpha(input[pos]) || input[pos] == '_'))
                {
                    lexicalError("identificador iniciado por numero");
                    return new Token(ERROR_TOKEN);
                }
                else
                {
                    state = 9; 
                }
                break;
            case 9:
                tok = new Token(INTEGERCONSTANT);
                tok->lexeme = lexeme;
                return tok;
            case 10:
                tok = new Token(PLUS);
                return tok;
            case 11:
                tok = new Token(MINUS);
                return tok;
            case 12:
                tok = new Token(MULT);
                return tok;
            case 13:
                if (pos < input.size() && input[pos] == '=')
                    state = 14;
                else
                    state = 15;
                
                pos++;

                break;
            case 14:
                tok = new Token(EQ);
                return tok;
            case 15:
                pos--;
                tok = new Token(AS);
                return tok;
            case 16:
                if (pos < input.size() && input[pos] == '=')
                    state = 17;
                else
                    state = 18;
                
                pos++;

                break;
            case 17:
                tok = new Token(LE);
                return tok;
            case 18:
                pos--;
                tok = new Token(LT);
                return tok;
            case 19:
                if (pos < input.size() && input[pos] == '=')
                    state = 20;
                else
                    state = 21;
                
                pos++;

                break;
            case 20:
                tok = new Token(GE);
                return tok;
            case 21:
                pos--;
                tok = new Token(GT);
                return tok;
            case 22:
                if (pos < input.size() && input[pos] == '=')
                    state = 23;
                else
                    state = 24;
                
                pos++;

                break;
            case 23:
                tok = new Token(NE);
                return tok;
            case 24:
                pos--;
                tok = new Token(NOT);
                return tok;
            case 25:
                if (pos < input.size() && input[pos] == '&')
                {
                    pos++;
                    state = 26;
                }
                else
                {
                    lexicalError("esperado &&");
                    return new Token(ERROR_TOKEN);
                }
                break;
            case 26:
                tok = new Token(AND);
                return tok;
            case 27:
                if (pos < input.size() && input[pos] == '|')
                {
                    pos++;
                    state = 28;
                }
                else
                {
                    lexicalError("esperado ||");
                    return new Token(ERROR_TOKEN);
                }
                break;
            case 28:
                tok = new Token(OR);
                return tok;
            case 29:
                tok = new Token(LPAR);
                return tok;
            case 30:
                tok = new Token(RPAR);
                return tok;
            case 31:
                tok = new Token(LBRACE);
                return tok;
            case 32:
                tok = new Token(RBRACE);
                return tok;
            case 33:
                tok = new Token(LBRACKET);
                return tok;
            case 34:
                tok = new Token(RBRACKET);
                return tok;
            case 35:
                tok = new Token(COMMA);
                return tok;
            case 36:
                tok = new Token(SEMICOLON);
                return tok;
            case 37:
                if (pos >= input.size())
                {
                    lexicalError("char nao fechado");
                    return new Token(ERROR_TOKEN);
                }

                if (input[pos] == '\\') // escape
                {
                    pos++;
                    state = 39;
                }
                else if (isprint(input[pos]) && input[pos] != '\'' && input[pos] != '\\')
                {
                    lexeme += input[pos];
                    pos++;
                    state = 38;
                }
                else
                {
                    lexicalError("char invalido");
                    return new Token(ERROR_TOKEN);
                }
                break;
            case 38:
                if (pos < input.size() && input[pos] == '\'')
                {
                    pos++;
                    return new Token(CHARCONSTANT, lexeme);
                }
                else
                {
                    lexicalError("char nao fechado");
                    return new Token(ERROR_TOKEN);
                }
            case 39:
                if (pos < input.size() && (input[pos] == 'n' || input[pos] == '0'))
                {
                    lexeme += '\\';
                    lexeme += input[pos];
                    pos++;
                    state = 38;
                }
                else
                {
                    lexicalError("escape invalido");
                    return new Token(ERROR_TOKEN);
                }
                break;
            case 40:
            if (pos >= input.size())
            {
                lexicalError("string nao fechada");
                return new Token(ERROR_TOKEN);
            }

            if (input[pos] == '"')
            {
                pos++;
                return new Token(STRINGCONSTANT, lexeme);
            }
            else if (input[pos] == '\n')
            {
                lexicalError("string nao pode ter quebra de linha");
                return new Token(ERROR_TOKEN);
            }
            else if (isprint(input[pos]) && input[pos] != '"')
            {
                lexeme += input[pos];
                pos++;
            }
            else
            {
                lexicalError("caractere invalido na string");
                return new Token(ERROR_TOKEN);
            }
            break;

            default:
                lexicalError("caractere invalido: " + string(1, input[pos]));
                pos++;
                return new Token(ERROR_TOKEN);
        
        }

    }
}


void 
Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
