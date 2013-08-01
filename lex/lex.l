%{
    #include <stdio.h>
    #include <string>
    #define SAVED_TOKEN yylval.string = new std::string(yytext, yyleng)
    extern "C" int yywrap() { }
%}
LETTER [a-zA-Z]
DIGIT [0-9]
WHITESPACE [\t\ ]
NEWLINE [\n\r]
%s INCOMMENT
%s INSTRING
%%
"if"                                       {return(IF);}
"then"                                     {return(THEN);}
"else"                                     {return(ELSE);}
"for"                                      {return(FOR);}
"to"                                       {return(TO);}
"do"                                       {return(DO);}
"while"                                    {return(WHILE);}
"break"                                    {return(BREAK);}
"<>"                                       {return(DIF_OP);}
">="                                       {return(GE_OP);}
"<="                                       {return(LE_OP);}
"and"                                      {return(AND);}
"or"                                       {return(OR);}
"+"                                        {return('+');}
"-"                                        {return('-');}
"*"                                        {return('*');}
"/"                                        {return('/');}
"="                                        {return('=');}
">"                                        {return('>');}
"<"                                        {return('<');}
{LETTER}_({LETTER}|{DIGIT}|_)*             {SAVED_TOKEN; return(IDENTIFIER);}
{DIGIT}+                                   {SAVED_TOKEN; return(NUMBER);}
{WHITESPACE}+                              ;
{NEWLINE}+                                 ;

<INITIAL>
{
    "/*"        BEGIN(INCOMMENT);
    ""          BEGIN(INSTRING);
}
<INCOMMENT>
{ 
    "*/"        BEGIN(INITIAL);
    [^*\n]+                   ;
    {NEWLINE}+                ;
}
<INSTRING>
{
    ["\""]          BEGIN(INITIAL);
    [^\n]+                        ;
}
%%
