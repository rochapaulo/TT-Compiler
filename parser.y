%{
#include "Node.h"
Node* root;
extern int yylex();
void yyerror(const char *error) { printf("ERROR: %s\n", error); }
%}

%union {
    Node* node;
    NExpression* exp;
    NStatement* stm;
    int token;
    int t_number;
    string *t_string;
}

/*     
      Definição dos símbolos não-terminais (tokens)
*/
%token <token> IF THEN ELSE FOR TO DO WHILE BREAK PRINT
%token <token> PLUS MINUS MUL DIV EQUAL OPDIF OPGE OPLE OPG OPL AND OR
%token <token> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <t_string> IDENTIFIER STRING
%token <t_number> NUMBER


/*     
      Definição dos tipos dos símbolos não-terminais
*/
%type <exp> exp
%type <token> binop


/*    
      Precedência de operadores Matemáticos
*/
%left PLUS MINUS
%left MUL DIV

%start program
/*
      Regras da Gramática
*/
%%
    program : exp   { root = $1; }
	    ;

    exp : WHILE exp DO exp { $$ = new NWhile(*$2, *$4) }
	| exp binop exp    { $$ = new NBinaryOperator(*$1, $2, *$3); }
	| NUMBER           { $$ = new NInteger($1);  }
	;

    binop : PLUS | MINUS | MUL | DIV
	  ;
%%
