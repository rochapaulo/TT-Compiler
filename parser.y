%{
#include "Node.h"
Node * root;
extern int yylex();
void yyerror(const char *error) { printf("ERROR: %s\n", error); }
%}

%union {
    Node * node;
    Expression * exp;
    Integer * integer;
    int token;
    int t_number;
    string *t_string;
}

/*     Definição dos símbolos não-terminais (tokens)
 */
%token <token> IF THEN ELSE FOR TO DO WHILE BREAK PRINT
%token <token> PLUS MINUS MUL DIV EQUAL OPDIF OPGE OPLE OPG OPL AND OR
%token <token> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <t_string> IDENTIFIER STRING
%token <integer> NUMBER


/*     Definição dos tipos dos símbolos não-terminais
*/
%type <exp> exp

/*    Precedência de operadores Matemáticos
 */

%%
    exp : NUMBER { $$ = $1 ; }
%%
