#include "IRNode.h"
#include <iostream>
#include <sstream>

IRConst::IRConst(int value){
    this->value = value;
}

string IRConst::toString(){
    stringstream stream;
    stream << "<CONST>" << value << "</CONST>\n";

    return stream.str();
}

IRName::IRName(string label){
    this->label = label;
}

string IRName::toString(){
   stringstream stream;
   stream << "<NAME>" << label << "</NAME>\n";
   return stream.str();
}

IRTemp::IRTemp(string temp){
   this->temp = temp;
}

string IRTemp::toString(){
    stringstream stream;
    stream << "<TEMP>" << temp << "</TEMP>\n";
    return stream.str();
}

IRBinop::IRBinop(int binop, IRExp *lExp, IRExp *rExp){
    this->binop = binop;
    this->lExp = lExp;
    this->rExp = rExp;
}

string IRBinop::toString(){
    stringstream stream;
    stream << lExp->toString();
    stream << "<OP>" << binop << "</OP>\n";
    stream << rExp->toString();

    return stream.str();
}

IRMem::IRMem(IRExp *exp){
    this->exp = exp;
}

string IRMem::toString(){
    stringstream stream;
    stream << "<MEM>" << exp->toString() << "</MEM>\n";
    return stream.str();
}

IRCall::IRCall(IRLabel *label, vector <IRExp*> *args){
    this->label = label;
    this->args = args;
}

string IRCall::toString(){
    stringstream stream;
    stream << "<CALL>";
    stream << label->toString();
    stream << "<ARGS>";
    if (args)
        for (int i = 0; i < args->size(); i++)
	    stream << args->at(i)->toString();
    stream << "</ARGS>";
    return stream.str();
}


IREseq::IREseq(IRStm *stm, IRExp *exp){
    this->stm = stm;
    this->exp = exp;
}

string IREseq::toString(){
    stringstream stream;
    stream << "<ESEQ>\n";
    stream << stm->toString();
    stream << exp->toString();
    stream << "</ESEQ>\n";
    return stream.str();
}

IRExpList::IRExpList(vector <IRExp*> *exps){
    this->exps = exps;
}

string IRExpList::toString(){
    stringstream stream;
    stream << "<EXPLIST>\n";
    for (int i = 0; i < exps->size(); i++)
        stream << exps->at(i)->toString();

    stream << "<EXPLIST>\n";

    return stream.str();

}

IRMove::IRMove(IRExp *dst, IRExp *src){
    this->dst = dst;
    this->src = src;
}

string IRMove::toString(){
    stringstream stream;
    stream << "<MOVE>\n";
    stream << dst->toString();
    stream << src->toString();
    stream << "</MOVE>\n";

    return stream.str();
}

IRJump::IRJump(IRLabel *label, IRExp *exp){
    this->label = label;
    this->exp = exp;
}

string IRJump::toString(){
    stringstream stream;
    stream << "<JUMP>\n";
    stream << label->toString();
    stream << exp->toString();
    stream << "</JUMP>\n";

    return stream.str();
}

IRCJump::IRCJump(int relop, IRExp *lExp, IRExp *rExp, IRLabel *iftrue, IRLabel *iffalse){
    this->relop = relop;
    this->lExp = lExp;
    this->rExp = rExp;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

string IRCJump::toString(){
    stringstream stream;
    stream << "<CJUMP>\n";
    stream << "<LEFT>" << lExp->toString() << "</LEFT>\n";
    stream << "<OP>" << relop << "</OP>\n";
    stream << "<RIGHT>" << rExp->toString() << "</RIGHT>\n";

    return stream.str();
}

IRSeq::IRSeq(IRStm *left, IRStm *right){
    this->left = left;
    this->right = right;
}

string IRSeq::toString(){
    return "SEC";
}

IRLabel::IRLabel(string label){
    this->label = label;
}

string IRLabel::toString(){
    stringstream stream;
    stream << "<LABEL>" << label << "</LABEL>\n";
    return stream.str();
}
