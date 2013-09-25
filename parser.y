%{
#include "Node.h"
Node* syntaxTree_root;
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
%type <exp> exp;
%type <exp> term;
%type <exp> integer_exp;
%type <exp> binary_exp;
%type <exp> if_exp;
%type <exp> while_exp;

%type <token> op;
/*    
      Precedência de operadores Matemáticos
*/
%left PLUS MINUS
%left MUL DIV
%nonassoc OPLE OPL OPGE OPG OPDIF

%start program
/*
      Regras da Gramática
*/
%%
    program :
	exp { syntaxTree_root = $1; }
	;

    exp :
	integer_exp
	| binary_exp
	| if_exp
	| while_exp
	;	

    integer_exp :
	NUMBER { $$ = new NInteger($1); }
	;

    binary_exp :
	term op exp  { $$ = new NBinaryOperator(*$1, $2, *$3); }
	;

    op :
	PLUS    { $$ = PLUS;  }
	| MINUS { $$ = MINUS; }
	| MUL   { $$ = MUL;   }
	| DIV   { $$ = DIV;   }
	| OPG   { $$ = OPG;   }
	| OPGE  { $$ = OPGE;  }
	| OPL   { $$ = OPL;   }
	| OPLE  { $$ = OPLE;  }
	| OPDIF { $$ = OPDIF; }
	| EQUAL { $$ = EQUAL; }
	;

    term :
	LPAREN exp RPAREN { $$ = $2; }
	| integer_exp
	;

    if_exp :
	IF exp THEN exp { $$ = new NIf(*$2, *$4, *$4); }
	| IF exp THEN exp ELSE exp { $$ = new NIf(*$2, *$4, *$6); }
	;

    while_exp :
	WHILE exp DO exp { $$ = new NWhile(*$2, *$4); }
	;

%%
