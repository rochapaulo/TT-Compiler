#ifndef IRTreeGen_H
#define IRTreeGen_H

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

class IRTreeGen {

   private:
        vector<IRNode*> irCodeList;

   public:
       IRTreeGen();
       void genCode(AST_Program *program);
       void genCode(NBinaryOperation *exp);
       void genCode(NNegation *exp);
       void genCode(NReturn *exp);
       void genCode(NIdentifier *exp);
       void genCode(NAssign *exp);
       void genCode(NIf *exp);
       void genCode(NWhile * exp);
       void genCode(NFor *exp);
       void genCode(NBreak *exp);
       void genCode(NArrayCreation *exp);
       void genCode(NArray *exp);
       void genCode(NArrayAssign *exp);
       void genCode(NFunctionCall *exp);
       void genCode(NExpressionList *exp);
       void genCode(NInteger *exp);
       void genCode(NFunctionDec *dec);
       void genCode(NImport *dec);

       vector<IRNode*> getIntermediateCode(AST_Program *program);
};

#endif
