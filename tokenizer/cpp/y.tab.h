#ifndef YY_parse_h_included
#define YY_parse_h_included
#define YY_USE_CLASS

#line 1 "/usr/share/bison++/bison.h"
/* before anything */
#ifdef c_plusplus
 #ifndef __cplusplus
  #define __cplusplus
 #endif
#endif


 #line 8 "/usr/share/bison++/bison.h"

#line 10 "parser.y"
typedef union {
   string t_string;
   int t_number;
} yy_parse_stype;
#define YY_parse_STYPE yy_parse_stype

#line 21 "/usr/share/bison++/bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_parse_COMPATIBILITY
 #ifndef YY_USE_CLASS
  #define  YY_parse_COMPATIBILITY 1
 #else
  #define  YY_parse_COMPATIBILITY 0
 #endif
#endif

#if YY_parse_COMPATIBILITY != 0
/* backward compatibility */
 #ifdef YYLTYPE
  #ifndef YY_parse_LTYPE
   #define YY_parse_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
  #endif
 #endif
/*#ifdef YYSTYPE*/
  #ifndef YY_parse_STYPE
   #define YY_parse_STYPE YYSTYPE
  /* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
   /* use %define STYPE */
  #endif
/*#endif*/
 #ifdef YYDEBUG
  #ifndef YY_parse_DEBUG
   #define  YY_parse_DEBUG YYDEBUG
   /* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
   /* use %define DEBUG */
  #endif
 #endif 
 /* use goto to be compatible */
 #ifndef YY_parse_USE_GOTO
  #define YY_parse_USE_GOTO 1
 #endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_parse_USE_GOTO
 #define YY_parse_USE_GOTO 0
#endif

#ifndef YY_parse_PURE

 #line 65 "/usr/share/bison++/bison.h"

#line 65 "/usr/share/bison++/bison.h"
/* YY_parse_PURE */
#endif


 #line 68 "/usr/share/bison++/bison.h"

#line 68 "/usr/share/bison++/bison.h"
/* prefix */

#ifndef YY_parse_DEBUG

 #line 71 "/usr/share/bison++/bison.h"

#line 71 "/usr/share/bison++/bison.h"
/* YY_parse_DEBUG */
#endif

#ifndef YY_parse_LSP_NEEDED

 #line 75 "/usr/share/bison++/bison.h"

#line 75 "/usr/share/bison++/bison.h"
 /* YY_parse_LSP_NEEDED*/
#endif

/* DEFAULT LTYPE*/
#ifdef YY_parse_LSP_NEEDED
 #ifndef YY_parse_LTYPE
  #ifndef BISON_YYLTYPE_ISDECLARED
   #define BISON_YYLTYPE_ISDECLARED
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;
  #endif

  #define YY_parse_LTYPE yyltype
 #endif
#endif

/* DEFAULT STYPE*/
#ifndef YY_parse_STYPE
 #define YY_parse_STYPE int
#endif

/* DEFAULT MISCELANEOUS */
#ifndef YY_parse_PARSE
 #define YY_parse_PARSE yyparse
#endif

#ifndef YY_parse_LEX
 #define YY_parse_LEX yylex
#endif

#ifndef YY_parse_LVAL
 #define YY_parse_LVAL yylval
#endif

#ifndef YY_parse_LLOC
 #define YY_parse_LLOC yylloc
#endif

#ifndef YY_parse_CHAR
 #define YY_parse_CHAR yychar
#endif

#ifndef YY_parse_NERRS
 #define YY_parse_NERRS yynerrs
#endif

#ifndef YY_parse_DEBUG_FLAG
 #define YY_parse_DEBUG_FLAG yydebug
#endif

#ifndef YY_parse_ERROR
 #define YY_parse_ERROR yyerror
#endif

#ifndef YY_parse_PARSE_PARAM
 #ifndef __STDC__
  #ifndef __cplusplus
   #ifndef YY_USE_CLASS
    #define YY_parse_PARSE_PARAM
    #ifndef YY_parse_PARSE_PARAM_DEF
     #define YY_parse_PARSE_PARAM_DEF
    #endif
   #endif
  #endif
 #endif
 #ifndef YY_parse_PARSE_PARAM
  #define YY_parse_PARSE_PARAM void
 #endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

 #ifndef YY_parse_PURE
  #ifndef yylval
   extern YY_parse_STYPE YY_parse_LVAL;
  #else
   #if yylval != YY_parse_LVAL
    extern YY_parse_STYPE YY_parse_LVAL;
   #else
    #warning "Namespace conflict, disabling some functionality (bison++ only)"
   #endif
  #endif
 #endif


 #line 169 "/usr/share/bison++/bison.h"
#define	IDENTIFIER	258
#define	STRING	259
#define	NUMBER	260
#define	IF	261
#define	THEN	262
#define	ELSE	263
#define	WHILE	264
#define	DO	265
#define	FOR	266
#define	TO	267
#define	BREAK	268
#define	PLUS	269
#define	MINUS	270
#define	MULT	271
#define	DIV	272
#define	EQUAL	273
#define	DIFF	274
#define	G_OP	275
#define	L_OP	276
#define	GE_OP	277
#define	LE_OP	278
#define	AND	279
#define	OR	280
#define	L_PAREN	281
#define	R_PAREN	282
#define	L_BRACKET	283
#define	R_BRACKET	284
#define	L_BRACE	285
#define	R_BRACE	286


#line 169 "/usr/share/bison++/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
 #ifndef YY_parse_CLASS
  #define YY_parse_CLASS parse
 #endif

 #ifndef YY_parse_INHERIT
  #define YY_parse_INHERIT
 #endif

 #ifndef YY_parse_MEMBERS
  #define YY_parse_MEMBERS 
 #endif

 #ifndef YY_parse_LEX_BODY
  #define YY_parse_LEX_BODY  
 #endif

 #ifndef YY_parse_ERROR_BODY
  #define YY_parse_ERROR_BODY  
 #endif

 #ifndef YY_parse_CONSTRUCTOR_PARAM
  #define YY_parse_CONSTRUCTOR_PARAM
 #endif
 /* choose between enum and const */
 #ifndef YY_parse_USE_CONST_TOKEN
  #define YY_parse_USE_CONST_TOKEN 0
  /* yes enum is more compatible with flex,  */
  /* so by default we use it */ 
 #endif
 #if YY_parse_USE_CONST_TOKEN != 0
  #ifndef YY_parse_ENUM_TOKEN
   #define YY_parse_ENUM_TOKEN yy_parse_enum_token
  #endif
 #endif

class YY_parse_CLASS YY_parse_INHERIT
{
public: 
 #if YY_parse_USE_CONST_TOKEN != 0
  /* static const int token ... */
  
 #line 212 "/usr/share/bison++/bison.h"
static const int IDENTIFIER;
static const int STRING;
static const int NUMBER;
static const int IF;
static const int THEN;
static const int ELSE;
static const int WHILE;
static const int DO;
static const int FOR;
static const int TO;
static const int BREAK;
static const int PLUS;
static const int MINUS;
static const int MULT;
static const int DIV;
static const int EQUAL;
static const int DIFF;
static const int G_OP;
static const int L_OP;
static const int GE_OP;
static const int LE_OP;
static const int AND;
static const int OR;
static const int L_PAREN;
static const int R_PAREN;
static const int L_BRACKET;
static const int R_BRACKET;
static const int L_BRACE;
static const int R_BRACE;


#line 212 "/usr/share/bison++/bison.h"
 /* decl const */
 #else
  enum YY_parse_ENUM_TOKEN { YY_parse_NULL_TOKEN=0
  
 #line 215 "/usr/share/bison++/bison.h"
	,IDENTIFIER=258
	,STRING=259
	,NUMBER=260
	,IF=261
	,THEN=262
	,ELSE=263
	,WHILE=264
	,DO=265
	,FOR=266
	,TO=267
	,BREAK=268
	,PLUS=269
	,MINUS=270
	,MULT=271
	,DIV=272
	,EQUAL=273
	,DIFF=274
	,G_OP=275
	,L_OP=276
	,GE_OP=277
	,LE_OP=278
	,AND=279
	,OR=280
	,L_PAREN=281
	,R_PAREN=282
	,L_BRACKET=283
	,R_BRACKET=284
	,L_BRACE=285
	,R_BRACE=286


#line 215 "/usr/share/bison++/bison.h"
 /* enum token */
     }; /* end of enum declaration */
 #endif
public:
 int YY_parse_PARSE(YY_parse_PARSE_PARAM);
 virtual void YY_parse_ERROR(char *msg) YY_parse_ERROR_BODY;
 #ifdef YY_parse_PURE
  #ifdef YY_parse_LSP_NEEDED
   virtual int  YY_parse_LEX(YY_parse_STYPE *YY_parse_LVAL,YY_parse_LTYPE *YY_parse_LLOC) YY_parse_LEX_BODY;
  #else
   virtual int  YY_parse_LEX(YY_parse_STYPE *YY_parse_LVAL) YY_parse_LEX_BODY;
  #endif
 #else
  virtual int YY_parse_LEX() YY_parse_LEX_BODY;
  YY_parse_STYPE YY_parse_LVAL;
  #ifdef YY_parse_LSP_NEEDED
   YY_parse_LTYPE YY_parse_LLOC;
  #endif
  int YY_parse_NERRS;
  int YY_parse_CHAR;
 #endif
 #if YY_parse_DEBUG != 0
  public:
   int YY_parse_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
 #endif
public:
 YY_parse_CLASS(YY_parse_CONSTRUCTOR_PARAM);
public:
 YY_parse_MEMBERS 
};
/* other declare folow */
#endif


#if YY_parse_COMPATIBILITY != 0
 /* backward compatibility */
 /* Removed due to bison problems
 /#ifndef YYSTYPE
 / #define YYSTYPE YY_parse_STYPE
 /#endif*/

 #ifndef YYLTYPE
  #define YYLTYPE YY_parse_LTYPE
 #endif
 #ifndef YYDEBUG
  #ifdef YY_parse_DEBUG 
   #define YYDEBUG YY_parse_DEBUG
  #endif
 #endif

#endif
/* END */

 #line 267 "/usr/share/bison++/bison.h"
#endif
