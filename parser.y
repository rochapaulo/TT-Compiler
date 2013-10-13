%{
#include "Node.h"
extern int yylex();
void yyerror(const char *error) 
{ 
printf("ERROR: %s\n", error); 
}
%}

%union {
    string              *identfier;
    string              *str_value;
    int                 integer;
    NExpression         *exp;
    NStatement          *dec;
    NSimpleVar          *var;
    NExpressionList     *exps;
    NStatementList      *decs;
    NFunctionDec        *fundec;
    NField              *field
    NFieldList          *field_list
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

%type <exp> program
%type <exp> exp
%type <exp> integer_exp
%type <exp> binary_exp
%type <exp> if_exp
%type <exp> while_exp
%type <exp> for_exp
%type <exp> break_exp
%type <exp> funcall_exp
%type <exp> array_creation
%type <exp> register_creation
%type <exps> exps
%type <exps> args
%type <var> lvalue
%type <identifier> identifier

%type <dec> dec
%type <dec> vardec
%type <dec> fundec
%type <decs> decs
%type <decs> decseq

%type <field> tyfield;
%type <field_lust> tyfields;
%%
program
    : exp
    {
        $$ = new AST_Program(@1.first_line, @1.first_column, $1);
    }
    | decs 
    {
        $$ = new AST_Program(@1.first_line, @1.first_column, $1);
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
    | register_creation
    {
        $$ = $1;
    }
    | funcall
    {
        $$ = $1;
    }
    ;


binary_exp
    : term op exp
    {
        $$ = new NBinaryOperation($1, $2, $3);
    }
    ;

term 
    : LPAREN exp RPAREN
    {
        $$ = $2;
    }
    | integer_exp
    {
        $$ = $1;
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

break_exp
    : BREAK
    {
        $$ = new NBreak();
    }
    ;

array_creation 
    : identifier LBRACKET exp RBRACKET
    {
        $$ = new NArray($1, $3);
    }
    ;

register_creation
    : identifier LBRACE recfields RBRACE
    {
        $$ = new NRecord($1, $3);
    }
    ;

recfields 
    : /* Empty */
    {
        $$ = NULL;
    }
    | recfield_list
    {
        $$ = $1;
    }
    ;

recfield_list
    : recfield
    {
        NExpressionList *recList;
        recList->push_back($1);
        $$ = recList;
    }
    | recfield_list COMMA recfield
    {
        $1->push_back($3);
        $$ = $1;
    }
    ;

recfield 
    : identifier EQ exp
    {
        $$ = new NField($1, $3);
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

args 
    : exp
    {
        NExpressionList *expList;
        expList->push_back($1);
        $$ = expList;
    }
    | args COMMA exp
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
        NStatementList * stmList;
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
    : vardec
    {
        $$ = $1;
    }
    | fundec
    {
        $$ = $1;
    }
    | import
    {
        $$ = $1;
    }
    ;

vardec 
    :   identifier ASSIGN exp
    {
        $$ = new NSimpleVar($1, $3);
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
        NFieldList *fieldList;
        field_list->push_back($1);
        $$ = fieldList;
    }
    | tyfields_list COMMA tyfield
    {
        $1->push_back($3);
        $$ = $1;
    }
    ;

tyfield 
    : identifier COLON identifier
    {
        $$ = new NField($1, $3);
    }
    ;

identifier 
    : IDENTIFIER
    {
        $$ = $1;
    }
    ;

%%
