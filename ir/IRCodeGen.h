#ifndef IRCodeGen_H
#define IRCodeGen_H

#include <vector>

using namespace std;

class IRNode;

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

class IRCodeGen {

   private:
        vector<IRNode*> irCodeList;

   public:
       IRCodeGen();
       IRNode genCode(AST_Program *program);
       IRNode genCode(NBinaryOperation *exp);
       IRNode genCode(NNegation *exp);
       IRNode genCode(NReturn *exp);
       IRNode genCode(NIdentifier *exp);
       IRNode genCode(NAssign *exp);
       IRNode genCode(NIf *exp);
       IRNode genCode(NWhile * exp);
       IRNode genCode(NFor *exp);
       IRNode genCode(NBreak *exp);
       IRNode genCode(NArrayCreation *exp);
       IRNode genCode(NArray *exp);
       IRNode genCode(NArrayAssign *exp);
       IRNode genCode(NFunctionCall *exp);
       IRNode genCode(NExpressionList *exp);
       IRNode genCode(NInteger *exp);
       IRNode genCode(NFunctionDec *dec);
       IRNode genCode(NImport *dec);

       vector<IRNode*> getIntermediateCode(AST_Program *program);
};

#endif
