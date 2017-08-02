#include "IRCodeGen.h"
#include <iostream>
#include <stdlib.h>
#include "Node.h"

using namespace std;

/**
 * IRCodeGen
 * 
 * Generates the 3AC (three-address-code) representation
 * for each Node type.
 * https://en.wikipedia.org/wiki/Three-address_code
 * 
 * author rochapaulo 
 */
IRCodeGen::IRCodeGen() {
}

IRNode IRCodeGen::genCode(AST_Program *program) {
    cout << "IR code gen: AST_Program" << endl;
}

IRNode IRCodeGen::genCode(NBinaryOperation *exp) {
    cout << "IR code gen: NBinaryOperation" << endl;
}

IRNode IRCodeGen::genCode(NNegation *exp) {
    cout << "IR code gen: NNegation" << endl;
}

IRNode IRCodeGen::genCode(NReturn *exp) {
    cout << "IR code gen: NReturn" << endl;
}

IRNode IRCodeGen::genCode(NIdentifier *exp) {
    cout << "IR code gen: NIdentifier" << endl;
}

IRNode IRCodeGen::genCode(NAssign *exp) {
    cout << "IR code gen: NAssign" << endl;
}

IRNode IRCodeGen::genCode(NIf *exp) {
    cout << "IR code gen: NIf" << endl;
}

IRNode IRCodeGen::genCode(NWhile *exp) {
    cout << "IR code gen: NWhile" << endl;
}

IRNode IRCodeGen::genCode(NFor *exp) {
    cout << "IR code gen: NFor" << endl;
}

IRNode IRCodeGen::genCode(NBreak *exp) {
    cout << "IR code gen: NBreak" << endl;
}

IRNode IRCodeGen::genCode(NArrayCreation *exp) {
    cout << "IR code gen: NArrayCreation" << endl;
}

IRNode IRCodeGen::genCode(NArray *exp){
    cout << "IR code gen: NArray" << endl;
}

IRNode IRCodeGen::genCode(NArrayAssign *exp){
    cout << "IR code gen: NArrayAssign" << endl;
}

IRNode IRCodeGen::genCode(NFunctionCall *exp) {
    cout << "IR code gen: NFunctionCall" << endl;
}

IRNode IRCodeGen::genCode(NExpressionList *exp){
    cout << "IR code gen: NExpressionList" << endl;
}

IRNode IRCodeGen::genCode(NInteger *exp) {
    cout << "IR code gen: NInteger" << endl;
}

IRNode IRCodeGen::genCode(NFunctionDec *dec) {
    cout << "IR code gen: NFunctionDec" << endl;
}

IRNode IRCodeGen::genCode(NImport *dec) {
    cout << "IR code gen: NImport" << endl;
}

vector<IRNode*> IRCodeGen::getIntermediateCode(AST_Program *program) {
    return irCodeList;
}
