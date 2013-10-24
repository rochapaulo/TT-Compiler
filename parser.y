%{

#include "Node.h"
extern int yylex();
extern int yywrap();
AST_Program* ast_program;

void yyerror(const char *error) 
{ 
printf("ERROR: %s\n", error); 
}
%}

%union {
    Node 	               	*program;
    string             		*str_value;
    string                  *str_identifier;
    int                 	integer;
    int		        		op;
    NExpression         	*exp;
    NStatement          	*dec;
    NIdentifier             *identifier;
    NLValue                 *leftValue;
    vector<NExpression*>	*exps;
    vector<NStatement*>     *decs;
    vector<NIdentifier*>    *tyfields;
    NFunctionDec        	*fundec;
}

%token <integer> NUMBER
%token <str_value> STRING

%token IDENTIFIER
%token IF THEN ELSE FOR TO DO WHILE BREAK PRINT RETURN IMPORT FUNCTION
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
%type <exp> assign
%type <exps> exps
%type <exps> dimension_acc
%type <exps> args

%type <op>op

%type <dec> dec
%type <dec> fundec
%type <dec> import
%type <decs> decs
%type <decs> decseq

%type <tyfields> tyfields
%type <leftValue> leftValue
%type <identifier> identifier
%type <integer> dimensions

%%
program
    : decs exp
    {
        ast_program = new AST_Program($1, $2);
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
    | LPAREN exps RPAREN
    {
        $$ = new NExpressionList($2);
    }
    ;


binary_exp
    : term op term
    {
        $$ = new NBinaryOperation($1, $2, $3);
    }
    ;

term 
    : LPAREN exp RPAREN
    {
        $$ = $2;
    }
    | NUMBER
    {
        $$ = new NInteger(yylval.integer);
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
    :  leftValue ASSIGN exp
    {
        $$ = new NAssign($1, $3);
    }
    ;

leftValue
    : identifier 
    {
          $$ = new NLValue($1, NULL);
    }
    | identifier dimension_acc
    {
          $$ = new NLValue($1, $2);
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
        $$ = new NArrayCreation($1, 0);
    }
    ;

dimensions
    : LBRACKET RBRACKET
    {
        $$ = 1;
    }
    | dimensions COLON LBRACKET RBRACKET
    {
       $$ = $1 + 1;
    }
    ;

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
        $$ = new NFunctionDec($2, $4, $7);
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
        vector<NIdentifier*> *identifierList;
        $$ = identifierList;
    }
    | identifier
    {
        vector<NIdentifier*> *fieldList;
        fieldList->push_back($1);
        $$ = fieldList;
    }
    | tyfields COLON identifier
    {
        $1->push_back($3);
        $$ = $1;
    }
    ;

identifier 
    : IDENTIFIER
    {
        $$ = new NIdentifier(yylval.str_identifier);
    }
    ;

%%
