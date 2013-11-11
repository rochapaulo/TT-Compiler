#include <iostream>
#include "Node.h"

using namespace std;

void TreeAnalyzer::visit(AST_Program *program) {
   cout << "Analyzing AST_Program" << endl; 
}

void TreeAnalyzer::visit(NBinaryOperation *exp) {
    cout << "Analyzing NBinaryOperation" << endl;
}

void TreeAnalyzer::visit(NNegation *exp) {
    cout << "Analyzing NNegation" << endl;
}

void TreeAnalyzer::visit(NReturn *exp) {
    cout << "Analyzing NReturn" << endl;
}

void TreeAnalyzer::visit(NIdentifier *exp) {
    cout << "Analyzing NIdentifier" << endl;
}

void TreeAnalyzer::visit(NAssign *exp) {
    cout << "Analyzing NAssign" << endl;
}

void TreeAnalyzer::visit(NIf *exp) {
    cout << "Analyzing NIf" << endl;
}

void TreeAnalyzer::visit(NWhile *exp) {
    cout << "Analyzing NWhile" << endl;
}

void TreeAnalyzer::visit(NFor *exp) {
    cout << "Analyzing NFor" << endl;
}

void TreeAnalyzer::visit(NBreak *exp) {
    cout << "Analyzing NBreak" << endl;
}

void TreeAnalyzer::visit(NLValue *exp) {
    cout << "Analyzing NLValue" << endl;
}

void TreeAnalyzer::visit(NArrayCreation *exp) {
    cout << "Analyzing NArrayCreation" << endl;
}

void TreeAnalyzer::visit(NFunctionCall *exp) {
    cout << "Analyzing NFunctionCall" << endl;
}

void TreeAnalyzer::visit(NExpressionList *exp){
    cout << "Analyzing NExpressionList" << endl;
}

void TreeAnalyzer::visit(NInteger *exp) {
    cout << "Analyzing NInteger" << endl;
}

void TreeAnalyzer::visit(NFunctionDec *dec) {
    cout << "Analyzing NFunctionDec" << endl;
}

void TreeAnalyzer::visit(NImport *dec) {
    cout << "Analyzing NImport" << endl;
}

