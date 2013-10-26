%{
//    #include <string>
    #include "Node.h"
    #include "parser.h"

    using namespace std;    

    char * myStr;
   
    int number;

    void initString();
    void appendString(char *text);
    //void printMessage(char *str);

%}
LETTER [a-zA-Z]
DIGIT [0-9]
WHITESPACE [\t\ ]
NEWLINE [\n\r]
IDENTIFIER ({LETTER}|_)({LETTER}|{DIGIT}|_)* 
%option noyywrap

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
    ":="             return(ASSIGN);
    ";"              return(SEMICOLON);
    ":"              return(COMMA);
    "."              return(DOT);
    ","              return(COLON);
    "function"       return(FUNCTION);
    "import"         return(IMPORT);
    {IDENTIFIER}     { 
			yylval.str_identifier = yytext;
			return(IDENTIFIER); 
		     }
    ([+|-]?){DIGIT}+ { 
    			yylval.integer = atoi(yytext); 
			return(NUMBER); 
		     }
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
   
   "\\\"" { 
   	      char *aux = (char *)malloc(sizeof(char));
	      aux[0] = '\"';
	      appendString(aux); 
	  }
   "\""   { 
   	      yylval.str_value = myStr; 
	      return(STRING);
	  }
   .      appendString(yytext);

}

%%

void initString() {
    
    myStr = (char *)malloc(sizeof(char));
    myStr[0] = '\0';

    BEGIN(INSTRING);
}

void appendString(char *text) {
    char *aux = (char *)malloc(strlen(myStr)+strlen(text)+1);
    strcat(aux, myStr);
    strcat(aux, text);
    myStr = aux;
}

