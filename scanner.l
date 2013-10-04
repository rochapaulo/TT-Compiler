%{
    #include <string>
    #include "Node.h"
    #include "parser.h"

    using namespace std;    

    string myStr;
   
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
    "}" 	         return(RBRACE);
    "[" 	         return(LBRACKET);
    "]"              return(RBRACKET);
    "(" 	         return(LPAREN);
    ")"  	         return(RPAREN);
    "function"       return(FUNCTION);
    {IDENTIFIER}     { *(yylval.t_string) = yytext; return(IDENTIFIER); }
    ([+|-]?){DIGIT}+ { yylval.t_number = atoi(yytext); return(NUMBER); }
    {WHITESPACE}+   ;
    {NEWLINE}+      ;
    "/*" 	    BEGIN(INCOMMENT);
    "\""	    myStr = "";
    . 		    yyterminate();
}
<INCOMMENT>
{
    "*/"        BEGIN(INITIAL);
    "[^*\n]+"   ;

}
<INSTRING>
{ 
   "\\\""  myStr = (myStr + "\"");
   "\""    { *(yylval.t_string) = myStr; return(STRING); }
   .	   myStr = (myStr + yytext);
}
%%
