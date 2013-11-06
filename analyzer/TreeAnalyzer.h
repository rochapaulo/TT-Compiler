#ifdef TREE_ANALYZER_H
#define TREE_ANALYZER_H

class Node;
class NExpression;
class NStatement;
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
class NLValue;
class NArrayCreation;
class NFunCall;
class NInteger;
class NFunctionDec;
class NImport;

class TreeAnalyzer {
   
   public:
       virtual ~TreeAnalyzer() {}
       virtual void visit(AST_Program *program) = 0;
       virtual void visit(NBinaryOperation *exp) = 0;
       virtual void visit(NNegation *exp) = 0;
       virtual void visit(NReturn *exp) = 0;
       virtual void visit(NIdentifier *exp) = 0;
       virtual void visit(NAssign *exp) = 0;
       virtual void visit(NIf *exp) = 0;
       virtual void visit(NWhile * exp) = 0;
       virtual void visit(NFor *exp) = 0;
       virtual void visit(NBreak *exp) = 0;
       virtual void visit(NLValue *exp) = 0;
       virtual void visit(NArrayCreation *exp) = 0;
       virtual void visit(NFunCall *exp) = 0;
       virtual void visit(NInteger *exp) = 0;
       virtual void visit(NFunctionDec *dec) = 0;
       virtual void visit(NImport *dec) = 0;
};
#endif
