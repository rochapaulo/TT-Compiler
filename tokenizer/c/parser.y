%{
extern int yylex();
void yyerror(const char *error) {
    printf("ERROR: %s\n", error);
}
%}

%union {
    int t_number;
    char *t_string;
}

%token IF THEN ELSE FOR TO DO WHILE BREAK PRINT
%token PLUS MINUS MUL DIV EQUAL OPDIF OPGE OPLE OPG OPL AND OR
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <t_string> IDENTIFIER STRING
%token <t_number> NUMBER

%%
parser :
	IF 	{ printf("Bison found an <IF>\n"); }
	| THEN  { printf("Bison found an <THEN>\n"); }
%%

int yywrap(void){
    return 1;
}

int main(int argc, char * argv) {
    yyparse();
    return 0;
}
