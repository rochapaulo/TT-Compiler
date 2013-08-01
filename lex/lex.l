%{
    #include <stdio.h>
    char *str;
%}
LETTER [a-zA-Z]
DIGIT [0-9]
WHITESPACE [\t\ ]
NEWLINE [\n\r]
IDENTIFIER ({LETTER}|_)({LETTER}|{DIGIT}|_)* 
%soption noyywrap
%s INCOMMENT
%s INSTRING
%s IF
%s THEN
%s ELSE
%s FOR
%s TO
%s DO
%s WHILE
%s BREAK
%s OP_DIF
%s OP_GE
%s OP_LE
%s AND
%s OR
%s IDENTIFIER
%%
<INITIAL>
{
    "if"      	 {printf("Saw an: %s\n", yytext); return(IF);}
    "then"    	 {printf("Saw an: %s\n", yytext); return(THEN);}
    "else"     	 {printf("Saw an: %s\n", yytext); return(ELSE);}
    "for"      	 {printf("Saw an: %s\n", yytext); return(FOR);}
    "to"       	 {printf("Saw an: %s\n", yytext); return(TO);}
    "do"       	 {printf("Saw an: %s\n", yytext); return(DO);}
    "while"    	 {printf("Saw an: %s\n", yytext); return(WHILE);}
    "break"    	 {printf("Saw an: %s\n", yytext); return(BREAK);}
    "<>"       	 {printf("Saw an: %s\n", yytext); return(OP_DIF);}
    ">="       	 {printf("Saw an: %s\n", yytext); return(OP_GE);}
    "<="         {printf("Saw an: %s\n", yytext); return(OP_LE);}
    "and"      	 {printf("Saw an: %s\n", yytext); return(AND);}
    "or"       	 {printf("Saw an: %s\n", yytext); return(OR);}
    "+"        	 {printf("Saw an: %s\n", yytext); return('+');}
    "-"        	 {printf("Saw an: %s\n", yytext); return('-');}
    "*"        	 {printf("Saw an: %s\n", yytext); return('*');}
    "/"        	 {printf("Saw an: %s\n", yytext); return('/');}
    "="        	 {printf("Saw an: %s\n", yytext); return('=');}
    ">"        	 {printf("Saw an: %s\n", yytext); return('>');}
    "<"       	 {printf("Saw an: %s\n", yytext); return('<');}
    {IDENTIFIER} {printf("Identifier: %s\n", yytext); return(IDENTIFIER);}
    {DIGIT}+     {printf("Digit: %s\n", yytext); return(atoi(yytext));}
    {WHITESPACE}+ ;
    {NEWLINE}+    ;
    "/*" 	 {printf("INCOMMENT\n"); BEGIN(INCOMMENT);}
    "\"" 	 {printf("INSTRING\n"); BEGIN(INSTRING);}
    . 		 printf("invalid token.");
}
<INCOMMENT>
{
    "*/" {printf("back to INITIAL\n"); BEGIN(INITIAL);}
    [^*\n]+            ;
}
<INSTRING>
{
    "\"" {printf("back to INITIAL\n"); BEGIN(INITIAL);}
    . 	 {printf("append string: %s \n", yytext);}
}
%%

int main(void)
{
    yylex();
    return 0;
}
