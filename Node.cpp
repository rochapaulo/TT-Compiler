#include "Node.h"
//#include "TreeAnalyzer.h"

void Node::set_line(int lin){
    this->lin = lin;
}

void Node::set_column(int col){
    this->col = col;
}

AST_Program::AST_Program(vector<NStatement*> *stmList, vector<NExpression*> *expList, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->stmList = stmList;
    this->expList = expList;
}

string AST_Program::to_string(){
    stringstream stream;
    stream << "<AST_PROGRAM>\n";
    
    if (stmList != NULL) {
        stream << "<STATEMENTS_SECTION>\n";
        
	for (int i = 0; i < stmList->size(); i++)
            stream << stmList->at(i)->to_string();
        
	stream << "</STATEMENTS_SECTION>\n";
    };
       
    if (expList != NULL) {
         stream << "<EXPRESSION_SECTION>\n";
	 
	 for (int i = 0; i < expList->size(); i++)
	     stream << expList->at(i)->to_string();
	     
	 stream << "<EXPRESSION_SECTION>\n";
    };
    
    stream << "</AST_PROGRAM>\n";
    
    return (stream.str());
}


void AST_Program::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    if (stmList != NULL)
        for (int i = 0; i < stmList->size(); i++)
	    stmList->at(i)->analyze(analyzer);	  
	    
	if (expList != NULL)
	    for (int i = 0; i < expList->size(); i++)
	        expList->at(i)->analyze(analyzer);		
}

NBinaryOperation::NBinaryOperation(NExpression *lExp, int op, NExpression *rExp, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->rExp = rExp;
    this->lExp = lExp;
    this->op = op;
}

string NBinaryOperation::to_string(){
    stringstream stream;
    stream << "<BINARY_OPERATION>\n"
    << "<LEFT_EXPRESSION>\n"  << lExp->to_string() << "</LEFT_EXPRESSION>\n"
    << "<OPERATION>\n" << op << "\n</OPERATION>\n"
    << "<RIGHT_EXPRESSION>\n" << rExp->to_string() << "</RIGHT_EXPRESSION>\n"
    << "</BINARY_OPERATION>\n";
    return stream.str();
}

void NBinaryOperation::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    
    rExp->analyze(analyzer);
    lExp->analyze(analyzer);
}

NInteger::NInteger(int value, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->value = value;
}

string NInteger::to_string(){
    stringstream stream;
    stream << "<INTEGER>\n" << value << "\n</INTEGER>\n";
    return stream.str();
}

void NInteger::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
}

NNegation::NNegation(NExpression *exp, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->exp = exp;
}

string NNegation::to_string(){
    stringstream stream;
    stream << "<NEGATION>\n" + exp->to_string() + "</NEGATION>\n";
    return stream.str();
}

void NNegation::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    exp->analyze(analyzer);
}

NReturn::NReturn(NExpression *exp, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->exp = exp;
}

string NReturn::to_string(){
    stringstream stream;
    stream << "<RETURN>\n" << exp->to_string() << "</RETURN>\n";
    return stream.str();
}

void NReturn::analyze(TreeAnalyzer *analyzer)
{
    analyzer->visit(this);
    exp->analyze(analyzer);
}

NIdentifier::NIdentifier(char *identifier, int lin, int col)
{
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
}

string NIdentifier::to_string()
{
    stringstream stream;
    stream << "<IDENTIFIER>\n" << identifier << "\n</IDENTIFIER>\n";
    return stream.str();
}

void NIdentifier::analyze(TreeAnalyzer *analyzer)
{
    analyzer->visit(this);
}

NLValue::NLValue(NIdentifier *identifier, vector <NExpression*> *indexList, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
    this->indexList = indexList;
}

string NLValue::to_string(){
    stringstream stream;
    stream << "<LVALUE>\n" << identifier->to_string() << "</LVALUE>\n";
    
    if (indexList != NULL){
        for (int i = 0; i < indexList->size(); i++)
            stream << "<INDEX>\n" << indexList->at(i)->to_string() << "</INDEX>\n";
    }
    
    return stream.str();
}

void NLValue::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    identifier->analyze(analyzer);
    
    if (indexList != NULL)
        for (int i = 0; i < indexList->size(); i++)
            indexList->at(i)->analyze(analyzer);
    
}

NAssign::NAssign(NLValue *lvalue, NExpression *exp, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->lvalue = lvalue;
    this->exp = exp;
}

string NAssign::to_string(){
    stringstream stream;
    stream << "<ASSIGN>\n"
    << "<LEFT_EXPRESSION>\n" << lvalue->to_string() << "</LEFT_EXPRESSION>\n"
    << "<RIGHT_EXPRESSION>\n" << exp->to_string() << "</RIGHT_EXPRESSION>\n"
    << "</ASSIGN>\n";
    return stream.str();
}

void NAssign::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    lvalue->analyze(analyzer);
    exp->analyze(analyzer);
}

NIf::NIf(NExpression *cond, NExpression *trueExp, NExpression *falseExp, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->cond = cond;
    this->trueExp = trueExp;
    this->falseExp = falseExp;
}

string NIf::to_string(){
    stringstream stream;
    stream << "<IF>\n" << cond->to_string() << "<THEN>\n" << trueExp->to_string() << "</THEN>\n";
    
    if (falseExp != NULL) {
        stream << "<ELSE>\n" << falseExp->to_string() << "</ELSE>\n";
    }
    
    stream << "</IF>\n";
    return stream.str();
}

void NIf::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    
    cond->analyze(analyzer);
    trueExp->analyze(analyzer);
    falseExp->analyze(analyzer);
}

NWhile::NWhile(NExpression *cond, NExpression *body, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->cond = cond;
    this->body = body;
}

string NWhile::to_string(){
    stringstream stream;
    stream << "<WHILE>\n";
    stream << cond->to_string() << "<DO>\n" << body->to_string() << "</DO>\n";
    stream << "</WHILE>\n";
    return stream.str();
}

void NWhile::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    
    cond->analyze(analyzer);
    body->analyze(analyzer);
}

NFor::NFor(NIdentifier *identifier, NExpression *initExp, NExpression *endExp, NExpression *body, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
    this->initExp = initExp;
    this->endExp = endExp;
    this->body = body;
}

string NFor::to_string(){
    stringstream stream;
    stream << "<FOR>\n" << identifier->to_string()
    << "<ASSIGN>\n" << initExp->to_string() << "</ASSIGN>\n"
    << "<TO>\n" << endExp->to_string() << "</TO>\n"
    << "<DO>\n" << body->to_string() << "</DO>\n"
    << "</FOR>\n";
    return stream.str();
}

void NFor::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    
    identifier->analyze(analyzer);
    initExp->analyze(analyzer);
    endExp->analyze(analyzer);
    body->analyze(analyzer);
}

NBreak::NBreak(int lin, int col){
    this->set_line(lin);
    this->set_column(col);
}

string NBreak::to_string(){
    stringstream stream;
    stream << "<BREAK>\n" << "</BREAK>\n";
    return stream.str();
}

void NBreak::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
}

NArrayCreation::NArrayCreation(NIdentifier *identifier, int dimension, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
    this->dimension = dimension;
}

string NArrayCreation::to_string(){
    stringstream stream;
    stream << "<ARRAY_CREATION>\n"
    << identifier->to_string()
    << "<DIMENSIONS>\n"
    << dimension
    << "\n</DIMENSIONS>\n"
    << "</ARRAY_CREATION>\n";
    return stream.str();
}

void NArrayCreation::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    identifier->analyze(analyzer);
}

NFunctionCall::NFunctionCall(NIdentifier *identifier, vector<NExpression*> *args, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
    this->args = args;
}

string NFunctionCall::to_string(){
    stringstream stream;
    stream << "<FUNCTION_CALL>\n"<< identifier->to_string();
    
    if (args != NULL)
        for (int i = 0; i < args->size(); i++)
            stream << (args->at(i))->to_string();
    
    stream << "</FUNCTION_CALL>\n";
    return stream.str();
}

void NFunctionCall::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);

    identifier->analyze(analyzer);
    
    if (args != NULL)
        for (int i = 0; i < args->size(); i++)
            args->at(i)->analyze(analyzer);
}

NExpressionList::NExpressionList(vector<NExpression*> *expList, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->expList = expList;
}

string NExpressionList::to_string(){
    stringstream stream;
    stream << "<EXPRESSION_LIST>\n";
    
    for (int i = 0; i < expList->size(); i++)
        stream << expList->at(i)->to_string();
    
    stream << "</EXPRESSION_LIST>\n";
    return stream.str();
}

void NExpressionList::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    
    for (int i = 0; i < expList->size(); i++)
        expList->at(i)->analyze(analyzer);
    
}

NFunctionDec::NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
    this->args = args;
    this->exp = exp;
}

string NFunctionDec::to_string(){
    stringstream stream;
    stream << "<FUNCTION_DEC>\n" << identifier->to_string()
    <<"<ARGS>\n";
    
    if (args != NULL)
        for(int i = 0; i < args->size(); i++)
            stream << args->at(i)->to_string();
    
    stream << "</ARGS>\n"
    << "<BODY>\n" << exp->to_string() << "</body>\n"
    << "</FUNCTION_DEC>\n";
    return stream.str();
}

void NFunctionDec::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    
    identifier->analyze(analyzer);
    
    if (args != NULL)
        for(int i = 0; i < args->size(); i++)
            args->at(i)->analyze(analyzer);
    
}

NImport::NImport(NIdentifier *identifier, int lin, int col){
    this->set_line(lin);
    this->set_column(col);
    this->identifier = identifier;
}

string NImport::to_string(){
    stringstream stream;
    stream << "<IMPORT>\n" << identifier->to_string() << "</IMPORT>\n";
    return stream.str();
}

void NImport::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    identifier->analyze(analyzer);
}



