#include "IRTreeGen.h"
#include <iostream>
#include <stdlib.h>
#include "Node.h"

using namespace std;

IRTreeGen::IRTreeGen() {
}

IRNode IRTreeGen::genCode(AST_Program *program) {
}

IRNode IRTreeGen::genCode(NBinaryOperation *exp) {
}

IRNode IRTreeGen::genCode(NNegation *exp) {
}

IRNode IRTreeGen::genCode(NReturn *exp) {
}

IRNode IRTreeGen::genCode(NIdentifier *exp) {
}

IRNode IRTreeGen::genCode(NAssign *exp) {
}

IRNode IRTreeGen::genCode(NIf *exp) {
}

IRNode IRTreeGen::genCode(NWhile *exp) {
}

IRNode IRTreeGen::genCode(NFor *exp) {
}

IRNode IRTreeGen::genCode(NBreak *exp) {
}

IRNode IRTreeGen::genCode(NArrayCreation *exp) {
}

IRNode IRTreeGen::genCode(NArray *exp){
}

IRNode IRTreeGen::genCode(NArrayAssign *exp){
}

IRNode IRTreeGen::genCode(NFunctionCall *exp) {
}

IRNode IRTreeGen::genCode(NExpressionList *exp){
}

IRNode IRTreeGen::genCode(NInteger *exp) {
}

IRNode IRTreeGen::genCode(NFunctionDec *dec) {
}

IRNode IRTreeGen::genCode(NImport *dec) {
}

vector<IRNode*> IRTreeGen::getIntermediateCode(AST_Program *program) {
    program->genCode();
    return irCodeList;
}
