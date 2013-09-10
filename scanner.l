%{
    #include <stdio.h>
    #include <string.h>
    #include "parser.tab.h"
    char *str_ptr;
    int number;

    void initString();
    void appendString(char *text);
    void printMessage(char *str);
%}
LETTER [a-zA-Z]
DIGIT [0-9]
WHITESPACE [\t\ ]
NEWLINE [\n\r]
IDENTIFIER ({LETTER}|_)({LETTER}|{DIGIT}|_)* 
%soption noyywrap

%x INCOMMENT
%x INSTRING

%%
<INITIAL>
{
    "if"      	     return(IF);
    "then"    	     return(THEN);
    "else"     	     return(ELSE);
    "for"      	     return(FOR);
    "to"       	     return(TO);
    "do"       	     return(DO);
    "while"    	     return(WHILE);
    "break"    	     return(BREAK);
    "print"          return(PRINT);
    "<>"       	     return(OPDIF);
    ">="       	     return(OPGE);
    "<="             return(OPLE);
    "and"      	     return(AND);
    "or"       	     return(OR);
    "+"              return(PLUS);
    "-"        	     return(MINUS);
    "*"        	     return(MUL);
    "/"        	     return(DIV);
    "="        	     return(EQUAL);
    ">"        	     return(OPG);
    "<"       	     return(OPL);
    "{"     	     return(LBRACE);
    "}" 	     return(RBRACE);
    "[" 	     return(LBRACKET);
    "]"              return(RBRACKET);
    "(" 	     return(LPAREN);
    ")"  	     return(RPAREN);
    {IDENTIFIER}     { yylval.t_string = yytext; return(IDENTIFIER);   }
    ([+|-]?){DIGIT}+ { yylval.t_number = atoi(yytext); return(NUMBER); }
    {WHITESPACE}+   ;
    {NEWLINE}+      ;
    "/*" 	    BEGIN(INCOMMENT);
    "\""	    initString();
    . 		    yyterminate();
}
<INCOMMENT>
{
    "*/"        BEGIN(INITIAL);
    "[^*\n]+"   ;

}
<INSTRING>
{ 
   "\\\""  appendString("\""); 
   "\""    { yylval.t_string = str_ptr; return(STRING); }
   .	   appendString(yytext);
}

%%

void initString() {
    str_ptr = malloc(sizeof(char) * 1);
    str_ptr[0] = '\0';
    BEGIN(INSTRING);
}

void appendString(char *text) {
    char *aux;
    aux = malloc(strlen(str_ptr) + strlen(text) + 1);
    strcat(aux, str_ptr);
    strcat(aux, text);
    str_ptr = aux;
}

