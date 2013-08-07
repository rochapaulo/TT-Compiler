%option noyywrap
%{
    #include <string>

    using namespace std;

    string aux = "";

    extern "C" int yywrap(){ }
%}
DIGIT [0-9]
LETTER [a-zA-Z]
WHITESPACE [\t\ ]
NEWLINE [\n\r]

%x IN_COMMENT
%x IN_STRING

%%
<INITIAL>
"if"                                  { return(IF);         }
"then"                                { return(THEN);       }
"else"                                { return(ELSE);       }
"while"                               { return(WHILE);      }
"do"                                  { return(DO);         }
"for"                                 { return(FOR);        }
"to"                                  { return(TO);         }
"break"                               { return(BREAK);      }
"+"                                   { return(PLUS);       }
"-"                                   { return(MINUS);      }
"*"                                   { return(MULT);       }
"/"                                   { return(DIV);        }
"="                                   { return(EQUAL);      }
"<>"                                  { return(DIFF);       }
">"                                   { return(G_OP);       }
"<"                                   { return(L_OP);       }
">="                                  { return(GE_OP);      }
"<="                                  { return(LE_OP);      }
"and"                                 { return(AND);        }
"or"                                  { return(OR);         }
"("                                   { return(L_PAREN);    }
")"                                   { return(R_PAREN);    }
"["                                   { return(L_BRACKET);  }
"]"                                   { return(R_BRACKET);  }
"{"                                   { return(L_BRACE);    }
"}"                                   { return(R_BRACE);    }
({LETTER}|_)({LETTER}|{DIGIT}|_)*     { return(IDENTIFIER); }
[+|-]?{DIGIT}+                        { return(NUMBER);     }
"/*"                                  { BEGIN(IN_COMMENT);  }
"\""                                  { aux=""; 
                                        BEGIN(IN_STRING);          
                                        return(IDENTIFIER); 
                                      }
{WHITESPACE}+                         ;
{NEWLINE}+                            ;
.                                     { yyterminate(); }

<IN_COMMENT>
{
    "*/"   { BEGIN(INITIAL); }
   [~*\n]+ ;
}

<IN_STRING>
{
    "\\\"" { (aux = aux + yytext); }
    "\""   { return(STRING);       }
    .      { (aux = aux + yytext); }
}
%%

int main()
{
   yyFlexLexer yy;
   yy.yylex();

   return 0;
}
