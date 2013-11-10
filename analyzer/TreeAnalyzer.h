#ifndef TreeAnalyzer_H
#define TreeAnalyzer_H

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
class NFunctionCall;
class NExpressionList;
class NInteger;
class NFunctionDec;
class NImport;

class TreeAnalyzer {
   
   public:
       TreeAnalyzer() {}
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
       void visit(NLValue *exp);
       void visit(NArrayCreation *exp);
       void visit(NFunctionCall *exp);
       void visit(NExpressionList *exp);
       void visit(NInteger *exp);
       void visit(NFunctionDec *dec);
       void visit(NImport *dec);
};

#endif

