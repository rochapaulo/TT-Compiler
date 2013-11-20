
#ifndef TreeAnalyzer_H
#define TreeAnalyzer_H

#include <map>
#include <string>

using namespace std;

class Node;
class AST_Program;
class NBinaryOperation;
class NNegation;
class NReturn;
class NIdentifier;
class NAssign;
class NIf;
class NWhile;
class NFor;
class NBreak;
class NArrayCreation;
class NArray;
class NArrayAssign;
class NFunctionCall;
class NExpressionList;
class NInteger;
class NFunctionDec;
class NImport;

typedef map<string, Node*> SymbolTable;

class TreeAnalyzer {
   
   private:
       SymbolTable *firstScope;
       SymbolTable *secondScope;
       unsigned int loop;
       void printError(string msg, int lin, int col);
              
   public:
       TreeAnalyzer();
       void visit(AST_Program *program);
       void visit(NBinaryOperation *exp);
       void visit(NNegation *exp);
       void visit(NReturn *exp);
       void visit(NIdentifier *exp);
       void visit(NAssign *exp);
       void visit(NIf *exp);
       void visit(NWhile * exp);
       void visit(NFor *exp);
       void visit(NBreak *exp);
       void visit(NArrayCreation *exp);
       void visit(NArray *exp);
       void visit(NArrayAssign *exp);
       void visit(NFunctionCall *exp);
       void visit(NExpressionList *exp);
       void visit(NInteger *exp);
       void visit(NFunctionDec *dec);
       void visit(NImport *dec);
       
       void eraseScope();
       void exitLoop();
};


#endif

