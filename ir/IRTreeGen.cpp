#include "IRTreeGen.h"
#include <iostream>
#include <stdlib.h>
#include "Node.h"

using namespace std;

IRTreeGen::IRTreeGen() {
}

IRNode IRTreeGen::genCode(AST_Program *program) {
    // TODO
}

IRNode IRTreeGen::genCode(NBinaryOperation *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NNegation *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NReturn *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NIdentifier *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NAssign *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NIf *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NWhile *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NFor *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NBreak *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NArrayCreation *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NArray *exp){
    // TODO
}

IRNode IRTreeGen::genCode(NArrayAssign *exp){
    // TODO
}

IRNode IRTreeGen::genCode(NFunctionCall *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NExpressionList *exp){
    // TODO
}

IRNode IRTreeGen::genCode(NInteger *exp) {
    // TODO
}

IRNode IRTreeGen::genCode(NFunctionDec *dec) {
    // TODO
}

IRNode IRTreeGen::genCode(NImport *dec) {
    // TODO
}

vector<IRNode*> IRTreeGen::getIntermediateCode(AST_Program *program) {
    return irCodeList;
}
