#include "IRTreeGen.h"
#include <iostream>
#include <stdlib.h>
#include "Node.h"

using namespace std;

IRTreeGen::IRTreeGen() {
}

void IRTreeGen::genCode(AST_Program *program) {
}

void IRTreeGen::genCode(NBinaryOperation *exp) {
}

void IRTreeGen::genCode(NNegation *exp) {
}

void IRTreeGen::genCode(NReturn *exp) {
}

void IRTreeGen::genCode(NIdentifier *exp) {
}

void IRTreeGen::genCode(NAssign *exp) {
}

void IRTreeGen::genCode(NIf *exp) {
}

void IRTreeGen::genCode(NWhile *exp) {
}

void IRTreeGen::genCode(NFor *exp) {
}

void IRTreeGen::genCode(NBreak *exp) {
}

void IRTreeGen::genCode(NArrayCreation *exp) {
}

void IRTreeGen::genCode(NArray *exp){
}

void IRTreeGen::genCode(NArrayAssign *exp){
}

void IRTreeGen::genCode(NFunctionCall *exp) {
}

void IRTreeGen::genCode(NExpressionList *exp){
}

void IRTreeGen::genCode(NInteger *exp) {
}

void IRTreeGen::genCode(NFunctionDec *dec) {
}

void IRTreeGen::genCode(NImport *dec) {
}

vector<IRNode*> IRTreeGen::getIntermediateCode(AST_Program *program) {
    program->genCode();
    return irCodeList;
}
