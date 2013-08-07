%{
    #include <string>
    extern int yylex();
    void yyerror(const string message) {
        printf("ERROR: %s\n", message);
    }

%}

%union {
   string t_string;
   int t_number;
}

%token <t_string> IDENTIFIER STRING
%token <t_number> NUMBER
%token <token> IF THEN ELSE WHILE DO FOR TO BREAK
%token <token> PLUS MINUS MULT DIV EQUAL DIFF G_OP L_OP GE_OP LE_OP AND OR
%token <token> L_PAREN, R_PAREN, L_BRACKET, R_BRACKET, L_BRACE, R_BRACE

%type <block> program
%type <expr> op

%%
program :
            op
            ;

op : PLUS | MINUS | MULT | DIV | EQUAL | DIFF | G_OP | L_OP | GE_OP | LE_OP | AND | OR
%%
