#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;

		void advance();
		void match(int);
		
	public:
		Parser(string input);
		void run();

        void program();
        void function();
        void varDeclaration();
        void type();
		void paramTypes();
		void statement();
		void statementSuffix();
		void assign();
		void expression();
		void unaryExpression();
		void primaryExpression();

        void error(string msg);
};

#endif