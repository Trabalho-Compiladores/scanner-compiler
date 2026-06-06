Como compilar

No terminal, dentro da pasta do projeto:

g++ main.cpp src/scanner.cpp src/parser.cpp -o compiler

O programa possui dois modos:
Modo scanner (referente ao analisador lexico)
./compiler -s testes/nome_arquivo.cmm

Modo parser (referente ao analisador sintatico)
./compiler -p testes/nome_arquivo.cmm

Exemplo de teste do modo scanner:

int a = 10;
a = a + 5;

Exemplo de teste do modo parser:

int main(void) {
    int x;
    x = 10;
    return 0;
}