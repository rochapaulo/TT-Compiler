%{
#include "Node.h"
Node* syntaxTree_root;
extern int yylex();
void yyerror(const char *error) { printf("ERROR: %s\n", error); }
%}

%union {
    string *identifier;
    string *str;
    int integer;
    Node* node;
    NExpression* exp;
    NStatement* dec;
    NExpressionList* exps;
    NStatementList* decs;
    int token;
}

/*     
      Definição dos símbolos não-terminais (tokens)
*/
%token <token> IF THEN ELSE FOR TO DO WHILE BREAK PRINT RETURN IMPORT
%token <token> PLUS MINUS MUL DIV EQUAL OPDIF OPGE OPLE OPG OPL AND OR
%token <token> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <t_string> IDENTIFIER STRING FUNCTION
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
%type <exp> lvalue;

%type <decs> decs;
%type <dec> dec;
%type <dec> fundec;
%type <dec> import;
%type <dec> args;

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
    program 
    : exp 
    { 
        syntaxTree_root = $1; 
    }
    | decs 
    { 
        syntaxTree_root = $1; 
    }
	;

    exp
	: integer_exp
	| binary_exp
    | neg_exp
    | return_exp
	| if_exp
	| while_exp
    | for_exp
    | break_exp
    | lvalue
	;

    decs 
    : dec 
    {
        vector<NStatement> * stmlist = new vector<NStatement>;
        list->push_back($1);
        $$ = list;
    }
    | decs dec
    {
        $1->push_back($2);
        $$ = $1;
    }
    ;

    dec 
    : fundec
    | import
    ;

    fundec
    : FUNCTION IDENTIFIER LPAREN args RPAREN 
    { 
        $$ = new NFunctionDec(*$2, *$4);
    }
    ;

    import
    : IMPORT OPL IDENTIFIER OPG
    {
        $$ = new NImport(*$3);
    }
    ;

    args 
    : /* empty */
    {
        vector<string> * arglist = new vector<string>;
        $$ = arglist;
    }
    | IDENTIFIER
    {
        vector<string> * arglist = new vector<string>;
        arglist->push_back($1);
        $$->arglist;
    }
    | args ',' IDENTIFIER
    {
        $1->push_back($3);
        $$ = $1;
    }
    ;

    integer_exp 
    : NUMBER 
    { 
        $$ = new NInteger($1); 
    }
	;

    binary_exp 
    : term op exp  
    { 
        $$ = new NBinaryOperation(*$1, $2, *$3); 
    }
	;

    op 
    : PLUS    { $$ = PLUS;  }
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

    neg_exp
    : MINUS exp 
    { 
        $$ = new NNegExp(*$2);
    }
    ;

    return_exp
    : RETURN exp 
    { 
        $$ = new NReturn(*$2);
    }
    ;

    term
	: LPAREN exp RPAREN 
    { 
        $$ = $2; 
    }
	| integer_exp
	;

    if_exp 
    : IF exp THEN exp 
    { 
        $$ = new NIf(*$2, *$4, *$4); 
    }
	| IF exp THEN exp ELSE exp 
    { 
        $$ = new NIf(*$2, *$4, *$6);
    }
	;

    while_exp
	: WHILE exp DO exp 
    { 
        $$ = new NWhile(*$2, *$4); 
    }
	;

    for_exp
    : FOR exp TO exp DO exp 
    { 
        $$ = new NFor(*$2, *$4, *$6); 
    }
    ;

    break_exp
    : BREAK 
    { 
        $$ = new NBreak(); 
    }
    ;

    lvalue
    : IDENTIFIER ':''=' exp
    { 
        $$ = new NSimpleVar(*$1, *$1); 
    }
    ;

%%
