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

%token <token> IF THEN ELSE FOR TO DO WHILE BREAK PRINT
%token <token> PLUS MINUS MUL DIV EQUAL OPDIF OPGE OPLE OPG OPL AND OR
%token <token> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <t_string> IDENTIFIER STRING
%token <t_number> NUMBER

%%
parser :
	IF 	{ printf("Bison found an <IF>\n"); }
	| THEN  { printf("Bison found an <THEN>\n"); }
%%
