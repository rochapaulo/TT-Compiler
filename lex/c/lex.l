%{
    #include <stdio.h>
    #include <string.h>

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
%s NUMBER
%s STRING
%%
<INITIAL>
{
    "if"      	    {printMessage("<IF>");      return(IF);}
    "then"    	    {printMessage("<THEN>");    return(THEN);}
    "else"     	    {printMessage("<ELSE>");    return(ELSE);}
    "for"      	    {printMessage("<FOR>");     return(FOR);}
    "to"       	    {printMessage("<TO>");      return(TO);}
    "do"       	    {printMessage("<DO>");      return(DO);}
    "while"    	    {printMessage("<WHILE>");   return(WHILE);}
    "break"    	    {printMessage("<BREAK>");   return(BREAK);}
    "<>"       	    {printMessage("<OP_DIFF>"); return(OP_DIF);}
    ">="       	    {printMessage("<OP_GE>");   return(OP_GE);}
    "<="            {printMessage("<OP_LE>");   return(OP_LE);}
    "and"      	    {printMessage("<AND>");     return(AND);}
    "or"       	    {printMessage("<OR>");      return(OR);}
    "+"        	    {printMessage("<PLUS>");    return('+');}
    "-"        	    {printMessage("<MINUS>");   return('-');}
    "*"        	    {printMessage("<MUL>");     return('*');}
    "/"        	    {printMessage("<DIV>");     return('/');}
    "="        	    {printMessage("<EQUAL>");   return('=');}
    ">"        	    {printMessage("<OP_G>");    return('>');}
    "<"       	    {printMessage("<OP_L>");    return('<');}
    "{"     	    {printMessage("<L_BRACE>"); return('{');}
    "}" 	    {printMessage("<R_BRACE>"); return('}');}
    "[" 	    {printMessage("<L_BRACKET>");   return('[');}
    "]" 	    {printMessage("<R_BRACKET>");   return(']');}
    "(" 	    {printMessage("<L_PAREN>"); return('(');}
    ")" 	    {printMessage("<R_PAREN>"); return(')');}
    {IDENTIFIER}    {printMessage("<IDENTIFIER>"); return(IDENTIFIER);}
    ([+|-]?){DIGIT}+  {printMessage("<NUMBER>"); number = atoi(yytext); return(NUMBER);}
    {WHITESPACE}+   ;
    {NEWLINE}+      ;
    "/*" 	    {BEGIN(INCOMMENT);}
    "\""	    {initString();}
    . 		    printf("INVALID TOKEN");
}
<INCOMMENT>
{
    "*/" {BEGIN(INITIAL);}
    "[^*\n]+"           ;

}
<INSTRING>
{ 
   "\\\"" appendString("\""); 
   "\""   {printMessage("<STRING>"); return(STRING);}
   .	  appendString(yytext);
}

%%

int main(void) {
    yylex();
    return 0;
}

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

void printMessage(char *str){
	printf("%s\n", str);
}

