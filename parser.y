%{

#include "Node.h"
extern int yylex();
void yyerror(const char *error) 
{ 
printf("ERROR: %s\n", error); 
}
%}

%union {
    Node 	               	*program;
    string      	       	*identfier;
    string             		*str_value;
    int                 	integer;
    int				op;
    NExpression         	*exp;
    NStatement          	*dec;
    vector<NExpression*>	*exps;
    vector<NStatement*>      	*decs;
    NFunctionDec        	*fundec;
    NField              	*field;
    NFieldList          	*field_list;
}

%token <identifier> IDENTIFIER
%token <integer> NUMBER
%token <str_value> STRING

%token  IF THEN ELSE FOR TO DO WHILE BREAK PRINT RETURN IMPORT FUNCTION
%token PLUS MINUS MUL DIV EQUAL OPDIF OPGE OPLE OPG OPL AND OR ASSIGN
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET SEMICOLON
%token COMMA DOT COLON

%nonassoc ASSIGN
%left OR
%left AND

%nonassoc EQUAL OPL OPLE OPGE OPG OPDIF 
%left PLUS MINUS
%left MUL DIV

%type <program> program
%type <exp> exp
%type <exp> binary_exp
%type <exp> term
%type <exp> neg_exp
%type <exp> if_exp
%type <exp> while_exp
%type <exp> for_exp
%type <exp> return_exp
%type <exp> break_exp
%type <exp> funcall
%type <exp> array_creation
%type <exp> lvalue
%type <exp> assign
%type <exp> dimensions
%type <exp> dimension_acc
%type <exps> exps
%type <exps> args
%type <identifier> identifier

%type <op>op

%type <dec> dec
%type <dec> fundec
%type <dec> import
%type <decs> decs
%type <decs> decseq

%type <field> tyfield
%type <field_list> tyfields
%type <field_list> tyfield_list

%%
program
    : decs exp
    {
        $$ = new AST_Program($1, $2);
    }
    ;

exp
    : binary_exp
    {
        $$ = $1;
    }
    | neg_exp
    {
        $$ = $1;
    }
    | return_exp
    {
        $$ = $1;
    }
    | assign
    {
        $$ = $1;
    }
    | lvalue
    {
        $$ = $1;
    }
    | if_exp
    {
        $$ = $1;
    }
    | while_exp
    {
        $$ = $1;
    }
    | for_exp
    {
        $$ = $1;
    }
    | break_exp
    {
        $$ = $1;
    }
    | array_creation
    {
        $$ = $1;
    }
    | funcall
    {
        $$ = $1;
    }
    ;


binary_exp
    : term op term
    {
        $$ = new NBinaryOperation($1, $2, $3);
    }
    ;

term 
    : exp
    {
        $$ = $1;
    }
    | NUMBER
    {
        $$ = $1;
    }
    | LPAREN exps RPAREN
    {
        $$ = $2;
    }
    ;

op 
    : PLUS
    {
        $$ = PLUS;
    }
    | MINUS
    {
        $$ = MINUS;
    }
    | MUL
    {
        $$ = MUL;
    }
    | DIV 
    {
        $$ = DIV;
    }
    | OPG
    {
        $$ = OPG;
    }
    | OPGE
    {
        $$ = OPGE;
    }
    | OPL
    {
        $$ = OPL;
    }
    | OPLE
    {
        $$ = OPLE;
    }
    | OPDIF
    {
        $$ = OPDIF;
    }
    | EQUAL
    {
        $$ = EQUAL;
    }
    ;

neg_exp
    : MINUS exp
    {
        $$ = new NNegation($2);
    }
    ;

assign 
    :   lvalue ASSIGN exp
    {
        $$ = new NAssign($1, $3);
    }
    ;

lvalue
    : identifier 
    {
        $$ = new NIdentifier($1);
    }
    | identifier dimension_acc
    {
        $$ = new NArrayAccess($1, $2);
    }
    ;

dimension_acc
    :  LBRACKET exp RBRACKET
    {
        vector<NExpression*> *expList;
	expList->push_back($2);
	$$ = expList;
    }
    |  LBRACKET exp RBRACKET dimension_acc
    {
        $4->push_back($2);
	$$ = $4;
    }

if_exp 
    : IF exp THEN exp
    {
        $$ = new NIf($2, $4, NULL);
    }
    | IF exp THEN exp ELSE exp
    {
        $$ = new NIf($2, $4, $6);
    }
    ;

while_exp 
    : WHILE exp DO exp
    {
        $$ = new NWhile($2, $4);
    }
    ;

for_exp
    : FOR identifier ASSIGN exp TO exp DO exp
    {
        $$ = new NFor($2, $4, $6, $8);
    }
    ;

return_exp
    : RETURN exp
    {
        $$ = new NReturn($2);
    }
    ;

break_exp
    : BREAK
    {
        $$ = new NBreak();
    }
    ;

array_creation 
    : identifier dimensions
    {
        $$ = new NArray($1, $2);
    }
    ;

dimensions
    : LBRACKET RBRACKET
    {
        int i = 1;
	$$ = i;
    }
    | LBRACKET RBRACKET COLON dimensions
    {
       $$ = $4 + 1; 
    }

funcall 
    : identifier LPAREN RPAREN
    {
        $$ = new NFunctionCall($1, NULL);
    }
    | identifier LPAREN args RPAREN
    {
        $$ = new NFunctionCall($1, $3);
    }
    ;

exps
    : exp
    {
	vector<NExpression*> *expList;
	expList->push_back($1);
	$$ = expList;
    }
    | exps SEMICOLON exp
    {
        $1->push_back($3);
	$$ = $1;
    }
    ;

args 
    : exp
    {
        vector<NExpression*> *expList;
        expList->push_back($1);
        $$ = expList;
    }
    | args COLON exp
    {
        $1->push_back($3);
        $$ = $1;
    }
    ;

decs
    : /* Empty */
    {
        $$ = NULL;
    }
    | decseq
    {
        $$ = $1;
    }
    ;

decseq
    : dec
    {
        vector<NStatement*> * stmList;
        stmList->push_back($1);
        $$ = stmList;
    }
    | decseq dec
    {
        $1->push_back($2);
        $$ = $1;
    }
    ;

dec 
    : fundec
    {
        $$ = $1;
    }
    | import
    {
        $$ = $1;
    }
    ;

fundec 
    : FUNCTION identifier LPAREN tyfields RPAREN EQUAL exp
    {
        $$ = new NFunctionDec($2, $4, %7);
    }
    ;


import 
    : IMPORT OPL identifier OPG
    {
        $$ = new NImport($3);
    }
    ;

tyfields 
    : /* Empty */
    {
        $$ = NULL;
    }
    | tyfield_list
    {
        $$ = $1;
    }
    ;

tyfield_list 
    : tyfield
    {
        vector<NIdentifier*> *fieldList;
        field_list->push_back($1);
        $$ = fieldList;
    }
    | tyfield_list COLON tyfield
    {
        $1->push_back($3);
        $$ = $1;
    }
    ;

tyfield
    : identifier
    {
        $$ = new NIdentifier($1);
    }
    ;

identifier 
    : IDENTIFIER
    {
        $$ = $1;
    }
    ;

%%
