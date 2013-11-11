#include "Node.h"

void Node::setLine(int lin){
    this->lin = lin;
}

void Node::setColumn(int col){
    this->col = col;
}

AST_Program::AST_Program(vector<NStatement*> *stmList, vector<NExpression*> *expList, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->stmList = stmList;
    this->expList = expList;
}

string AST_Program::toString(){
    stringstream stream;
    stream << "<AST_PROGRAM>\n";

    if (stmList != NULL) {
        stream << "<STATEMENTS_SECTION>\n";

        for (int i = 0; i < stmList->size(); i++)
            stream << stmList->at(i)->toString();

        stream << "</STATEMENTS_SECTION>\n";
    };

    if (expList != NULL) {
        stream << "<EXPRESSION_SECTION>\n";

        for (int i = 0; i < expList->size(); i++)
            stream << expList->at(i)->toString();
        stream << "<EXPRESSION_SECTION>\n";
    };

    stream << "</AST_PROGRAM>\n";

    return (stream.str());
}


void AST_Program::analyze(TreeAnalyzer *analyzer) {
    analyzer->visit(this);
    if (stmList != NULL)
        for (int i = 0; i < stmList->size(); i++)
            stmList->at(i)->analyze(analyzer);	  

    if (expList != NULL)
        for (int i = 0; i < expList->size(); i++)
            expList->at(i)->analyze(analyzer);		
}

NBinaryOperation::NBinaryOperation(NExpression *lExp, int op, NExpression *rExp, int lin, int col) {
    this->setLine(lin);
    this->setColumn(col);
    this->rExp = rExp;
    this->lExp = lExp;
    this->op = op;
}

string NBinaryOperation::toString(){
    stringstream stream;
    stream << "<BINARY_OPERATION>\n"
        << "<LEFT_EXPRESSION>\n"  << lExp->toString() << "</LEFT_EXPRESSION>\n"
        << "<OPERATION>\n" << op << "\n</OPERATION>\n"
        << "<RIGHT_EXPRESSION>\n" << rExp->toString() << "</RIGHT_EXPRESSION>\n"
        << "</BINARY_OPERATION>\n";
    return stream.str();
}

void NBinaryOperation::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);

    rExp->analyze(analyzer);
    lExp->analyze(analyzer);
}

NInteger::NInteger(int value, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->value = value;
}

string NInteger::toString(){
    stringstream stream;
    stream << "<INTEGER>\n" << value << "\n</INTEGER>\n";
    return stream.str();
}

void NInteger::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
}

NNegation::NNegation(NExpression *exp, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->exp = exp;
}

string NNegation::toString(){
    stringstream stream;
    stream << "<NEGATION>\n" + exp->toString() + "</NEGATION>\n";
    return stream.str();
}

void NNegation::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    exp->analyze(analyzer);
}

NReturn::NReturn(NExpression *exp, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->exp = exp;
}

string NReturn::toString(){
    stringstream stream;
    stream << "<RETURN>\n" << exp->toString() << "</RETURN>\n";
    return stream.str();
}

void NReturn::analyze(TreeAnalyzer *analyzer)
{
    analyzer->visit(this);
    exp->analyze(analyzer);
}

NIdentifier::NIdentifier(char *identifier, int lin, int col)
{
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
}

string NIdentifier::toString()
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
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
    this->indexList = indexList;
}

string NLValue::toString(){
    stringstream stream;
    stream << "<LVALUE>\n" << identifier->toString() << "</LVALUE>\n";

    if (indexList != NULL){
        for (int i = 0; i < indexList->size(); i++)
            stream << "<INDEX>\n" << indexList->at(i)->toString() << "</INDEX>\n";
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
    this->setLine(lin);
    this->setColumn(col);
    this->lvalue = lvalue;
    this->exp = exp;
}

string NAssign::toString(){
    stringstream stream;
    stream << "<ASSIGN>\n"
        << "<LEFT_EXPRESSION>\n" << lvalue->toString() << "</LEFT_EXPRESSION>\n"
        << "<RIGHT_EXPRESSION>\n" << exp->toString() << "</RIGHT_EXPRESSION>\n"
        << "</ASSIGN>\n";
    return stream.str();
}

void NAssign::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    lvalue->analyze(analyzer);
    exp->analyze(analyzer);
}

NIf::NIf(NExpression *cond, NExpression *trueExp, NExpression *falseExp, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->cond = cond;
    this->trueExp = trueExp;
    this->falseExp = falseExp;
}

string NIf::toString(){
    stringstream stream;
    stream << "<IF>\n" << cond->toString() << "<THEN>\n" << trueExp->toString() << "</THEN>\n";

    if (falseExp != NULL) {
        stream << "<ELSE>\n" << falseExp->toString() << "</ELSE>\n";
    }

    stream << "</IF>\n";
    return stream.str();
}

void NIf::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);

    cond->analyze(analyzer);
    trueExp->analyze(analyzer);
    if (falseExp != NULL)
        falseExp->analyze(analyzer);
}

NWhile::NWhile(NExpression *cond, NExpression *body, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->cond = cond;
    this->body = body;
}

string NWhile::toString(){
    stringstream stream;
    stream << "<WHILE>\n";
    stream << cond->toString() << "<DO>\n" << body->toString() << "</DO>\n";
    stream << "</WHILE>\n";
    return stream.str();
}

void NWhile::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);

    cond->analyze(analyzer);
    body->analyze(analyzer);
}

NFor::NFor(NIdentifier *identifier, NExpression *initExp, NExpression *endExp, NExpression *body, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
    this->initExp = initExp;
    this->endExp = endExp;
    this->body = body;
}

string NFor::toString(){
    stringstream stream;
    stream << "<FOR>\n" << identifier->toString()
        << "<ASSIGN>\n" << initExp->toString() << "</ASSIGN>\n"
        << "<TO>\n" << endExp->toString() << "</TO>\n"
        << "<DO>\n" << body->toString() << "</DO>\n"
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
    this->setLine(lin);
    this->setColumn(col);
}

string NBreak::toString(){
    stringstream stream;
    stream << "<BREAK>\n" << "</BREAK>\n";
    return stream.str();
}

void NBreak::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
}

NArrayCreation::NArrayCreation(NIdentifier *identifier, int dimension, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
    this->dimension = dimension;
}

string NArrayCreation::toString(){
    stringstream stream;
    stream << "<ARRAY_CREATION>\n"
        << identifier->toString()
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
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
    this->args = args;
}

string NFunctionCall::toString(){
    stringstream stream;
    stream << "<FUNCTION_CALL>\n"<< identifier->toString();

    if (args != NULL)
        for (int i = 0; i < args->size(); i++)
            stream << (args->at(i))->toString();

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
    this->setLine(lin);
    this->setColumn(col);
    this->expList = expList;
}

string NExpressionList::toString(){
    stringstream stream;
    stream << "<EXPRESSION_LIST>\n";

    for (int i = 0; i < expList->size(); i++)
        stream << expList->at(i)->toString();

    stream << "</EXPRESSION_LIST>\n";
    return stream.str();
}

void NExpressionList::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);

    for (int i = 0; i < expList->size(); i++)
        expList->at(i)->analyze(analyzer);

}

NFunctionDec::NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp, int lin, int col){
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
    this->args = args;
    this->exp = exp;
}

string NFunctionDec::toString(){
    stringstream stream;
    stream << "<FUNCTION_DEC>\n" << identifier->toString()
        <<"<ARGS>\n";

    if (args != NULL)
        for(int i = 0; i < args->size(); i++)
            stream << args->at(i)->toString();

    stream << "</ARGS>\n"
        << "<BODY>\n" << exp->toString() << "</body>\n"
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
    this->setLine(lin);
    this->setColumn(col);
    this->identifier = identifier;
}

string NImport::toString(){
    stringstream stream;
    stream << "<IMPORT>\n" << identifier->toString() << "</IMPORT>\n";
    return stream.str();
}

void NImport::analyze(TreeAnalyzer *analyzer){
    analyzer->visit(this);
    identifier->analyze(analyzer);
}
