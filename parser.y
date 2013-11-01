%{

#include "Node.h"
#include <cstdlib>
extern int yylex();
extern int yywrap();
extern int yylineno, yycolumn;
void yyerror(string err) 
{ 
    printf("error on line %d, column %d\n",  yylineno, yycolumn); 
}

AST_Program* ast_program;
%}

%union {
    Node 	               	*program;
    char             		*str_value;
    char                  	*str_identifier;
    int                 	integer;
    int	    	        	op;
    NExpression         	*exp;
    NStatement          	*dec;
    NIdentifier            	*identifier;
    NLValue                	*leftValue;
    vector<NExpression*>	*exps;
    vector<NStatement*>    	*decs;
    vector<NIdentifier*>   	*tyfields;
    NFunctionDec        	*fundec;
}

%token <integer> NUMBER
%token <str_value> STRING
%token <str_identifier> IDENTIFIER

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

%type <op> op

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
        ast_program = new AST_Program($1, $2, yylineno, yycolumn);
    }
    ;

exp
    : term
    {
        printf("exp->term\n");
        $$ = $1;
    }
    | binary_exp
    {
        printf("exp->binary_exp\n");
        $$ = $1;
    }
    | neg_exp
    {
        printf("exp->neg_exp\n");
        $$ = $1;
    }
    | return_exp
    {
        printf("exp->return_exp\n");
        $$ = $1;
    }
    | assign
    {
        printf("exp->assign\n");
        $$ = $1;
    }
    | if_exp
    {
        printf("exp->if_exp\n");
        $$ = $1;
    }
    | while_exp
    {
        printf("exp->while_exp\n");
        $$ = $1;
    }
    | for_exp
    {
        printf("exp->for_exp\n");
        $$ = $1;
    }
    | break_exp
    {
        printf("exp->break_exp\n");
        $$ = $1;
    }
    | array_creation
    {
        printf("exp->array_creation\n");
        $$ = $1;
    }
    | funcall
    {
        printf("exp->funcall\n");
        $$ = $1;
    } 
    | LPAREN exps RPAREN
    {
        printf("exp->exps\n");
        $$ = new NExpressionList($2, yylineno, yycolumn);
    }
    ;


binary_exp
    : term op term
    {
        printf("binary_exp->term op term\n");
        $$ = new NBinaryOperation($1, $2, $3, yylineno, yycolumn);
    }
    ;

term 
    : leftValue
    {
        printf("term->leftValue\n");
        $$ = $1;
    }
    | LPAREN exp RPAREN
    {
        printf("term->LPAREN exp RPAREN\n");
        $$ = $2;
    }
    | NUMBER
    {
        printf("term->NUMBER\n");
        $$ = new NInteger(yylval.integer, yylineno, yycolumn);
    }
    ;

op 
    : PLUS
    {
        printf("op->PLUS\n");
        $$ = PLUS;
    }
    | MINUS
    {
        printf("op->MINUS\n");
        $$ = MINUS;
    }
    | MUL
    {
        printf("op->MUL\n");
        $$ = MUL;
    }
    | DIV 
    {
        printf("op->DIV\n");
        $$ = DIV;
    }
    | OPG
    {
        printf("op->OPG\n");
        $$ = OPG;
    }
    | OPGE
    {
        printf("op->OPGE\n");
        $$ = OPGE;
    }
    | OPL
    {
        printf("op->OPL\n");
        $$ = OPL;
    }
    | OPLE
    {
        printf("op->OPLE\n");
        $$ = OPLE;
    }
    | OPDIF
    {
        printf("op->OPDIF\n");
        $$ = OPDIF;
    }
    | EQUAL
    {
        printf("op->EQUAL\n");
        $$ = EQUAL;
    }
    ;

neg_exp
    : MINUS exp
    {
        printf("neg_exp->MINUS exp\n");
        $$ = new NNegation($2, yylineno, yycolumn);
    }
    ;

assign 
    :  leftValue ASSIGN exp
    {
        printf("assign->leftValue ASSIGN exp\n");
        $$ = new NAssign($1, $3, yylineno, yycolumn);
    }
    ;

leftValue
    : identifier 
    {
        printf("leftValue->identifier\n");
        $$ = new NLValue($1, NULL, yylineno, yycolumn);
    }
    | identifier dimension_acc
    {
        printf("leftValue->identifier dimensions_acc\n"); 
        $$ = new NLValue($1, $2, yylineno, yycolumn);
    }
    ;

dimension_acc
    :  LBRACKET exp RBRACKET
    {
        printf("dimension_acc->LBRACKET exp RBRACKET\n");
        vector<NExpression*> *expList;
    	expList = (vector<NExpression*> *)malloc(sizeof(vector<NExpression*>));
    	expList->push_back($2);
	    $$ = expList;
    }
    |  LBRACKET exp RBRACKET dimension_acc
    {
        printf("dimenstion_acc->LBRACKET exp LBRACKET dimensions_acc\n");
        $4->push_back($2);
    	$$ = $4;
    }

if_exp 
    : IF exp THEN exp
    {
        printf("if_exp->IF exp THEN exp\n");
        $$ = new NIf($2, $4, NULL, yylineno, yycolumn);
    }
    | IF exp THEN exp ELSE exp
    {
        printf("if_exp->IF exp THEN exp ELSE exp\n");
        $$ = new NIf($2, $4, $6, yylineno, yycolumn);
    }
    ;

while_exp 
    : WHILE exp DO exp
    {
        printf("while_exp->WHILE exp DO exp\n");
        $$ = new NWhile($2, $4, yylineno, yycolumn);
    }
    ;

for_exp
    : FOR identifier ASSIGN exp TO exp DO exp
    {
        printf("for_exp->FOR identifier ASSIGN exp TO exp DO exp\n");
        $$ = new NFor($2, $4, $6, $8, yylineno, yycolumn);
    }
    ;

return_exp
    : RETURN exp
    {
        printf("return_exp->RETURN exp\n");
        $$ = new NReturn($2, yylineno, yycolumn);
    }
    ;

break_exp
    : BREAK
    {
        printf("break_exp->BREAK\n");
        $$ = new NBreak(yylineno, yycolumn);
    }
    ;

array_creation 
    : identifier dimensions
    {
        printf("array_creation->identifier dimensions\n");
        $$ = new NArrayCreation($1, $2, yylineno, yycolumn);
    }
    ;

dimensions
    : LBRACKET RBRACKET
    {
        printf("dimensions->LBRACKET RBRACKET\n");
        $$ = 1;
    }
    | dimensions LBRACKET RBRACKET
    {
       printf("dimensions->dimensions LBRACKET RBRACKET\n");
       $$ = $1 + 1;
    }
    ;

funcall 
    : identifier LPAREN RPAREN
    {
        printf("funcall->identifier LPAREN RPAREN\n");
        $$ = new NFunctionCall($1, NULL, yylineno, yycolumn);
    }
    | identifier LPAREN args RPAREN
    {
        printf("funcall->identifier LPAREN args RPAREN\n");
        $$ = new NFunctionCall($1, $3, yylineno, yycolumn);
    }
    ;

exps
    : exp
    {
        printf("exps->exp\n");
    	vector<NExpression*> *expList;
	    expList = (vector<NExpression*> *)malloc(sizeof(vector<NExpression*>));
	    expList->push_back($1);
    	$$ = expList;
    }
    | exps SEMICOLON exp
    {
        printf("exps->exps SEMICOLON exp\n");
        $1->push_back($3);
        $$ = $1;
    }
    ;

args 
    : exp
    {
        printf("args->exp\n");
        vector<NExpression*> *expList;
	    expList = (vector<NExpression*> *)malloc(sizeof(vector<NExpression*>));
        expList->push_back($1);
        $$ = expList;
    }
    | args COLON exp
    {
        printf("args->args COLON exp\n");
        $1->push_back($3);
        $$ = $1;
    }
    ;

decs
    : /* Empty */
    {
        printf("decs->Empty\n");
        $$ = NULL;
    }
    | decseq
    {
        printf("decs->decseq\n");
        $$ = $1;
    }
    ;

decseq
    : dec
    {
        printf("decseq->dec\n");
        vector<NStatement*> * stmList;
	    stmList = (vector<NStatement*> *)malloc(sizeof(vector<NStatement*>));
        stmList->push_back($1);
        $$ = stmList;
    }
    | decseq dec
    {
        printf("decseq->decseq dec\n");
        $1->push_back($2);
        $$ = $1;
    }
    ;

dec 
    : fundec
    {
        printf("dec->fundec\n");
        $$ = $1;
    }
    | import
    {
        printf("dec->import");
        $$ = $1;
    }
    ;

fundec 
    : FUNCTION identifier LPAREN tyfields RPAREN EQUAL exp
    {
        printf("fundec->FUNCTION identifier LPAREN typefields RPAREN EQUAL exp\n");
        $$ = new NFunctionDec($2, $4, $7, yylineno, yycolumn);
    }
    ;

import 
    : IMPORT OPL identifier OPG
    {
        printf("import->IMPORT OPL identifier OPG\n");
        $$ = new NImport($3, yylineno, yycolumn);
    }
    ;

tyfields
    : /* Empty */
    {
        printf("tyfields->Empty\n");
	    vector<NIdentifier*> *emptyList;
	    emptyList = (vector<NIdentifier*> *)malloc(sizeof(vector<NIdentifier*>));
        $$ = emptyList;
    }
    | identifier
    {
        printf("tyfields->identifier\n");
        vector<NIdentifier*> *fieldList;
        fieldList = (vector<NIdentifier*> *)malloc(sizeof(vector<NIdentifier*>));
        fieldList->push_back($1);
        $$ = fieldList;
    }
    | tyfields COLON identifier
    {
        printf("tyfields->tyfields COLON identifier\n");
        $1->push_back($3);
        $$ = $1;
    }
    ;

identifier 
    : IDENTIFIER
    {
        printf("identifier->IDENTIFIER\n");
        $$ = new NIdentifier(yylval.str_identifier, yylineno, yycolumn);
    }
    ;

%%
