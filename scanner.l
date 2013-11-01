%{
    #include <string.h>
    #include "Node.h"
    #include "parser.h"

    using namespace std;    

    char * myStr;
    int number;
    int yycolumn = 0;

    void initString();
    void appendString(char *text);
    void count();

%}
LETTER [a-zA-Z]
DIGIT [0-9]
WHITESPACE [\t\ ]
NEWLINE [\n\r]
IDENTIFIER ({LETTER}|_)({LETTER}|{DIGIT}|_)* 
%option noyywrap
%option yylineno

%x INCOMMENT
%x INSTRING

%%
<INITIAL>
{
    "if"		{ count(); return(IF);         }
    "then"		{ count(); return(THEN);       }
    "else"		{ count(); return(ELSE);       }
    "for"		{ count(); return(FOR);        }
    "to"		{ count(); return(TO);         }
    "do"		{ count(); return(DO);         }
    "while"		{ count(); return(WHILE);      }
    "break"		{ count(); return(BREAK);      }
    "print"		{ count(); return(PRINT);      }
    "<>"		{ count(); return(OPDIF);      }
    ">="		{ count(); return(OPGE);       }
    "<="		{ count(); return(OPLE);       }
    "and"		{ count(); return(AND);        }
    "or"		{ count(); return(OR);         }
    "+"			{ count(); return(PLUS);       }
    "-"			{ count(); return(MINUS);      }
    "*"			{ count(); return(MUL);        }
    "/"			{ count(); return(DIV);        }
    "="			{ count(); return(EQUAL);      }
    ">"			{ count(); return(OPG);        }
    "<" 		{ count(); return(OPL);        }
    "{"			{ count(); return(LBRACE);     }
    "}"			{ count(); return(RBRACE);     }
    "["			{ count(); return(LBRACKET);   }
    "]"			{ count(); return(RBRACKET);   }
    "("			{ count(); return(LPAREN);     }
    ")"			{ count(); return(RPAREN);     }
    ":="		{ count(); return(ASSIGN);     }
    ";"			{ count(); return(SEMICOLON);  }
    ":"			{ count(); return(COMMA);      }
    "."			{ count(); return(DOT);        }
    ","			{ count(); return(COLON);      }
    "function"		{ count(); return(FUNCTION);   }
    "import"		{ count(); return(IMPORT);     }
    {IDENTIFIER}	{ 
				count();
				yylval.str_identifier = yytext;
				return(IDENTIFIER); 
			}
    ([+|-]?){DIGIT}+	{ 
				yylval.integer = atoi(yytext); 
				return(NUMBER); 
			}
    {WHITESPACE}+	{ count();                     }
    {NEWLINE}+		{ count();                     }
    "/*"		{ count(); BEGIN(INCOMMENT);   }
    "\""		{ count(); initString();       }
    .			{ count(); yyterminate();      }
}
<INCOMMENT>
{
    "*/"		{ count(); BEGIN(INITIAL);      }
    "[^*\n]+"		{ count();                      }

}
<INSTRING>
{ 
   
   "\\\""		{ 
				count(); 
				char *aux = (char *)malloc(sizeof(char));
				aux[0] = '\"';
				appendString(aux); 
	                }
   "\""			{ 
				yylval.str_value = myStr; 
				return(STRING);
			}
   .			{ count(); appendString(yytext); }
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

void count() {
    for (int i = 0; i < yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            yycolumn = 0;
            yylineno++;
        } else {
            yycolumn++;
        }
    }
}
