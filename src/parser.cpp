#include "../include/parser.h"
#include <cstdlib>

// Construtor
Parser::Parser(string input)
{
    currentST = globalST = new SymbolTable();
	initSimbolTable();

	scanner = new Scanner(input, globalST);
}

// Avança para o próximo token
void Parser::advance()
{
    lToken = scanner->nextToken();
}

// Verifica se o token atual é o esperado; consome e avança ou reporta erro
void Parser::match(int expected)
{
    if (lToken->name == expected || lToken->attribute == expected)
        advance();
    else
        error("erro inesperado");
}

// Reporta erro sintático com a linha atual e encerra
void Parser::error(string msg)
{
    cout << "Linha " << scanner->getLine() << ": " << msg << endl;
    exit(EXIT_FAILURE);
}

// Inicia a análise sintática
void Parser::run()
{
    advance();
    program();
    cout << "Compilacao encerrada com sucesso.\n";
}

// <Program> → (<Function>)* EOF
void Parser::program()
{
    while (lToken->name != END_OF_FILE)
        function();
    match(END_OF_FILE);
}

// <Function> → (<Type> | void) ID ( <ParamTypes> ) { ( <Type> <VarDeclaration> ( , <VarDeclaration> )* ; )* ( <Statement> )* }
void Parser::function()
{
    // (<Type> | void)
    if (lToken->name == VOID)
        match(VOID);          // consome "void"
    else
        type();             // consome "char" ou "int"

    match(ID);              // nome da função
    match(LPAR);            // '('
    paramTypes();           // parâmetros
    match(RPAR);            // ')'
    match(LBRACE);          // '{'

    // ( <Type> <VarDeclaration> ( , <VarDeclaration> )* ; )*
    while (lToken->name == CHAR || lToken->name == INT)
    {
        type();                     // tipo
        varDeclaration();           // primeira variável
        while (lToken->name == COMMA)
        {
            match(COMMA);
            varDeclaration();       // próxima variável
        }
        match(SEMICOLON);           // fim da declaração
    }

    // ( <Statement> )*
    while (lToken->name != RBRACE && lToken->name != END_OF_FILE)
        statement();

    match(RBRACE);          // '}'
}

// <Type> → char | int
void Parser::type()
{
    if (lToken->name == CHAR)
        match(CHAR);
    else if(lToken->name == INT)
        match(INT);
    else
        error("tipo esperado: char ou int");
}

// <VarDeclaration> → ID [integerconstant]? 
void Parser::varDeclaration()
{
    match(ID);
    if (lToken->name == LBRACKET)
    {
        match(LBRACKET);        // '['
        match(INTEGERCONSTANT);
        match(RBRACKET);        // ']'
    }
}

// <ParamTypes> → void | <Type> ID  [] ? ( , <Type> ID ( [] )? )*
void Parser::paramTypes()
{
    // caso tenha só o "void" 
    if (lToken->name == VOID)
    {
        match(VOID);
        return;
    }
    // pelo menos um parâmetro: <Type> ID []?
    type();
    match(ID);
    if (lToken->name == LBRACKET) //[]
    {
        match(LBRACKET);
        match(RBRACKET);
    }
    // ( , <Type> ID ( [] )? )*
    while (lToken->name == COMMA)
    {
        match(COMMA);
        type();
        match(ID);
        if (lToken->name == LBRACKET)
        {
            match(LBRACKET);
            match(RBRACKET);
        }
    }
}

// <Statement> → if ( <Expression> ) <Statement> ( else <Statement> )?
//             | while ( <Expression> ) <Statement>
//             | for ( <Assign>? ; <Expression>? ; <Assign>? ) <Statement>
//             | return <Expression>? ;
//             | ID <StatementSuffix>
//             | { <Statement>* }
//             | ;
void Parser::statement()
{
    if (lToken->name == IF)
    {
        match(IF);
        match(LPAR);
        expression();
        match(RPAR);
        statement();
        if (lToken->name == ELSE)
        {
            match(ELSE);
            statement();
        }
    }    
    else if (lToken->name == WHILE)
    {
        match(WHILE);
        match(LPAR);
        expression();
        match(RPAR);
        statement();
    }
    else if (lToken->name == FOR)
    {
        match(FOR);
        match(LPAR);
        // <Assign>?
        if (lToken->name != SEMICOLON)
            assign();
        match(SEMICOLON);
        // <Expression>?
        if (lToken->name != SEMICOLON)
            expression();
        match(SEMICOLON);
        // <Assign>?
        if (lToken->name != RPAR)
            assign();
        match(RPAR);
        statement();
    }
    else if (lToken->name == RETURN)
    {
        match(RETURN);
        if (lToken->name != SEMICOLON)
            expression();
        match(SEMICOLON);
    }
    else if(lToken->name == ID)
    {
        match(ID); //consome o id
        statementSuffix();
    }
    else if (lToken->name == LBRACE)
    {
        match(LBRACE);
        while (lToken->name != RBRACE && lToken->name != END_OF_FILE)
            statement();
        match(RBRACE);
    }
    else if (lToken->name == SEMICOLON)
    {
        match(SEMICOLON);
    }
    else
    {
        error("erro de estrutura");
    }
}

// <StatementSuffix> → [ <Expression> ]? = <Expression> ;
//                   | ( <Expression> ( , <Expression> )* )? ;
void Parser::statementSuffix()
{
    //o ID ja foi consumido na funcao anterior
    if (lToken->name == LBRACKET || lToken->name == AS)
    {
        // [ <Expression> ] ? = <Expression> ;
        if (lToken->name == LBRACKET)
        {
            match(LBRACKET);
            expression();
            match(RBRACKET);
        }
        match(AS);
        expression();
        match(SEMICOLON);
    }
    else if (lToken->name == LPAR)
    {
        // ( ( <Expression> ( , <Expression> )* )? ) ;
        match(LPAR);
        if (lToken->name != RPAR)
        {
            expression();
            while (lToken->name == COMMA)
            {
                match(COMMA);
                expression();
            }
        }
        match(RPAR);
        match(SEMICOLON);
    }
    else
    {
        error("esperado '=', '[' ou '(' após identificador");
    }
}

// <Assign> → ID [ <Expression> ]? = <Expression>
void Parser::assign()
{
    match(ID);
    if (lToken->name == LBRACKET)
    {
        match(LBRACKET);
        expression();
        match(RBRACKET);
    }
    match(AS);
    expression();
}

// <Expression> → <UnaryExpression> ( ( <BinOp> | <RelOp> | <LogOp> ) <UnaryExpression> )*
void Parser::expression()
{
    unaryExpression();
    while (lToken->name == PLUS || lToken->name == MINUS ||
           lToken->name == MULT || lToken->name == DIV ||
           lToken->name == EQ || lToken->name == NE ||
           lToken->name == LT || lToken->name == LE ||
           lToken->name == GT || lToken->name == GE ||
           lToken->name == AND || lToken->name == OR)
    {
        advance();          // consome o operador
        unaryExpression();
    }
}

// <UnaryExpression> → - <UnaryExpression> | ! <UnaryExpression> | <PrimaryExpression>
void Parser::unaryExpression()
{
    if (lToken->name == MINUS || lToken->name == NOT)
    {
        advance();
        unaryExpression();
    }
    else
    {
        primaryExpression();
    }
}

// <PrimaryExpression> → ID
//                     | ID ( <Expression> ( , <Expression> )* )?
//                     | ID [ <Expression> ]
//                     | ( <Expression> )
//                     | integerconstant
//                     | charconstant
//                     | stringconstant
void Parser::primaryExpression()
{
    switch (lToken->name)
    {
        case ID:
        {
            match(ID); //consome o ID
            if (lToken->name == LPAR)
            {
                // ID ( <Expression> ( , <Expression> )* )?
                match(LPAR);
                if (lToken->name != RPAR)
                {
                    expression();
                    while (lToken->name == COMMA)
                    {
                        match(COMMA);
                        expression();
                    }
                }
                match(RPAR);
            }
            else if (lToken->name == LBRACKET)
            {
                // ID [ <Expression> ]
                match(LBRACKET);
                expression();
                match(RBRACKET);
            }
            //break caso tenha apenas o ID 
            break;
        }
        case LPAR:
            match(LPAR);
            expression();
            match(RPAR);
            break;
        case INTEGERCONSTANT:
        case CHARCONSTANT:
        case STRINGCONSTANT:
            advance();
            break;
        default:
            error("expressão primaria invalida");
    }
}

void
Parser::initSimbolTable()
{
	Token* t;
        
	t = new Token(CHAR, "char");
	globalST->add(new STEntry(t, true));
	t = new Token(INT, "int");
    globalST->add(new STEntry(t, true));
    t = new Token(VOID, "void");
    globalST->add(new STEntry(t, true));
    t = new Token(IF, "if");
    globalST->add(new STEntry(t, true));
    t = new Token(ELSE, "else");
    globalST->add(new STEntry(t, true));
    t = new Token(WHILE, "while");
    globalST->add(new STEntry(t, true));
    t = new Token(FOR, "for");
    globalST->add(new STEntry(t, true));
    t = new Token(RETURN, "return");
    globalST->add(new STEntry(t, true));
}

