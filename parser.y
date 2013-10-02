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
    NExpressionList* expList;
    NStatementList* stmList;
    int token;
    int t_number;
    string *t_string;
}

/*     
      Definição dos símbolos não-terminais (tokens)
*/
%token <token> IF THEN ELSE FOR TO DO WHILE BREAK PRINT RETURN
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
%type <exp> neg_exp;
%type <exp> return_exp;
%type <exp> if_exp;
%type <exp> while_exp;
%type <exp> for_exp;
%type <exp> break_exp;

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
    | neg_exp
    | return_exp
	| if_exp
	| while_exp
    | for_exp
    | break_exp
	;	

    integer_exp :
	NUMBER { $$ = new NInteger($1); }
	;

    binary_exp :
	| term op exp  { $$ = new NBinaryOperator(*$1, $2, *$3); }
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

    neg_exp :
    MINUS exp { $$ = new NNegExp(*$2) }
    ;

    return_exp :
    RETURN exp { $$ = new NReturn(*$2) }
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

    for_exp :
    FOR exp TO exp DO exp { $$ = new NFor(*$2, *$4, *$6); }
    ;

    break_exp :
    BREAK { $$ = new NBreak(); }
    ;

%%
