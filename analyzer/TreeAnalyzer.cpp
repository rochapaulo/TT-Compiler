#include <iostream>
#include "Node.h"

using namespace std;

TreeAnalyzer::TreeAnalyzer(){
    this->firstScope = new SymbolTable();
    this->secondScope = NULL;
    this->loop = 0;
}

void TreeAnalyzer::visit(AST_Program *program) {
}

void TreeAnalyzer::visit(NBinaryOperation *exp) {
}

void TreeAnalyzer::visit(NNegation *exp) {
}

void TreeAnalyzer::visit(NReturn *exp) {
    
    if (secondScope == NULL)
        printError("Illegal 'return' command", exp->lin, exp->col);
}

void TreeAnalyzer::visit(NIdentifier *exp) {

    SymbolTable::iterator it = firstScope->find(exp->identifier);
    if (it == firstScope->end())
        if (secondScope)
             it = secondScope->find(exp->identifier);
   
    NIdentifier* identifier = dynamic_cast<NIdentifier*>(it->second);
    if (!identifier) {
        printError("Undeclared identifier \'" + exp->identifier + "\'", exp->lin, exp->col);
    }
}

void TreeAnalyzer::visit(NAssign *exp) {
    (*firstScope)[exp->identifier->identifier] = exp->identifier;
}

void TreeAnalyzer::visit(NIf *exp) {
}

void TreeAnalyzer::visit(NWhile *exp) {
    loop ++;
}

void TreeAnalyzer::visit(NFor *exp) {
    loop ++;
}

void TreeAnalyzer::visit(NBreak *exp) {
    if (loop == 0)
        printError("Illegal 'break' command", exp->lin, exp->col);
}

void TreeAnalyzer::visit(NArrayCreation *exp) {
    (*firstScope)[exp->identifier->identifier] = exp;
}

void TreeAnalyzer::visit(NArray *exp){

    SymbolTable::iterator it = firstScope->find(exp->identifier->identifier);
    if (it == firstScope->end())
        if (secondScope)
             it = secondScope->find(exp->identifier->identifier);
   
    NArrayCreation* array = dynamic_cast<NArrayCreation*>(it->second);
    if (!array || exp->indexList->size() > array->dimension) {
        printError("Undeclared array \'" + exp->identifier->identifier + "\'", exp->lin, exp->col);
    } 
}

void TreeAnalyzer::visit(NArrayAssign *exp){
    
}

void TreeAnalyzer::visit(NFunctionCall *exp) {
    SymbolTable::iterator it = firstScope->find(exp->identifier->identifier);
    if (it == firstScope->end())
        if (secondScope)
             it = secondScope->find(exp->identifier->identifier);
   
    NFunctionDec* funDec = dynamic_cast<NFunctionDec*>(it->second);
    if (!funDec || (funDec->args->size() != exp->args->size())) {
        stringstream ss;
        ss << "Undeclared function '" << exp->identifier->identifier << "\\" << exp->args->size() << "\'";
        string msg = ss.str();
        printError(msg, exp->lin, exp->col);
    }
}

void TreeAnalyzer::visit(NExpressionList *exp){
}

void TreeAnalyzer::visit(NInteger *exp) {
}

void TreeAnalyzer::visit(NFunctionDec *dec) {
    (*firstScope)[dec->identifier->identifier] = dec;
    SymbolTable *aux = new SymbolTable();
    
    if (dec->args != NULL){
        for (int i = 0; i < dec->args->size(); i++)
            (*aux)[dec->args->at(i)->identifier] = dec->args->at(i);
    }
        
    secondScope = firstScope;
    firstScope = aux;
}

void TreeAnalyzer::visit(NImport *dec) {
}

void TreeAnalyzer::eraseScope() {
    firstScope->clear();
    free(firstScope);
    firstScope = secondScope;
    secondScope = NULL;
}

void TreeAnalyzer::printError(string msg, int lin, int col){
    stringstream ss;
    ss << "Error: " << msg << ", on line " << lin << ", column " << col;
    
    cout << ss.str() << endl; 
}

void TreeAnalyzer::exitLoop() {
    loop --;
}


