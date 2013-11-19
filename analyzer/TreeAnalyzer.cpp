#include <iostream>
#include "Node.h"

using namespace std;

TreeAnalyzer::TreeAnalyzer(){
    this->firstScope = new SymbolTable();
    this->secondScope = NULL;
}

void TreeAnalyzer::visit(AST_Program *program) {
//   cout << "Analyzing AST_Program" << endl; 
}

void TreeAnalyzer::visit(NBinaryOperation *exp) {
//    cout << "Analyzing NBinaryOperation" << endl;
}

void TreeAnalyzer::visit(NNegation *exp) {
//    cout << "Analyzing NNegation" << endl;
}

void TreeAnalyzer::visit(NReturn *exp) {
//    cout << "Analyzing NReturn" << endl;
    
    if (secondScope == NULL)
        printError("'return' command outside of a function", exp->lin, exp->col);
}

void TreeAnalyzer::visit(NIdentifier *exp) {
//    cout << "Analyzing NIdentifier " << exp->identifier << endl;
//    
//   	cout << "firstScope\n";
//   	for (SymbolTable::iterator it=firstScope->begin(); it!=firstScope->end(); ++it)
//   		cout << it->first << endl;
//
//   	if (secondScope){
//	   	cout << "secondScope\n";
//	   	for (SymbolTable::iterator it=secondScope->begin(); it!=secondScope->end(); ++it)
//	   		cout << it->first << endl;
//   	}

//    if (firstScope->find(exp->identifier) == firstScope->end()){    	
//        if (secondScope == NULL || secondScope->find(exp->identifier) == secondScope->end()){
//            printError("Undefined identifier \'" + exp->identifier + "\'", exp->lin, exp->col);
//        }
//    }

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
//    cout << "Analyzing NAssign" << endl;
}

void TreeAnalyzer::visit(NIf *exp) {
//    cout << "Analyzing NIf" << endl;
}

void TreeAnalyzer::visit(NWhile *exp) {
//    cout << "Analyzing NWhile" << endl;
}

void TreeAnalyzer::visit(NFor *exp) {
//    cout << "Analyzing NFor" << endl;
}

void TreeAnalyzer::visit(NBreak *exp) {
//    cout << "Analyzing NBreak" << endl;
}

void TreeAnalyzer::visit(NLValue *exp) {
//    cout << "Analyzing NLValue" << endl;
    
    (*firstScope)[exp->identifier->identifier] = exp->identifier;
}

void TreeAnalyzer::visit(NArrayCreation *exp) {
//    cout << "Analyzing NArrayCreation" << endl;
    
    (*firstScope)[exp->identifier->identifier] = exp;
}

void TreeAnalyzer::visit(NFunctionCall *exp) {
//    cout << "Analyzing NFunctionCall" << endl;

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
//    cout << "Analyzing NExpressionList" << endl;
}

void TreeAnalyzer::visit(NInteger *exp) {
//    cout << "Analyzing NInteger" << endl;
}

void TreeAnalyzer::visit(NFunctionDec *dec) {
//    cout << "Analyzing NFunctionDec" << endl;
    
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
//    cout << "Analyzing NImport" << endl;
}

void TreeAnalyzer::eraseScope() {
//	cout << "eraseScope" << endl;
    firstScope->clear();
    free(firstScope);
    firstScope = secondScope;
    secondScope = NULL;
}

void TreeAnalyzer::printError(string msg, int lin, int col){
    stringstream ss;
    ss << msg << ", on line " << lin << ", column " << col;
    
    cout << ss.str() << endl;
    
}

