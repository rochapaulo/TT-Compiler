#ifndef IRNode_H
#define IRNode_H

#include <vector>
#include <string>

using namespace std;

class IRLabel;

class IRNode
{
    public:
        IRNode() {};
        string toString() {};
};

class IRExp : public IRNode {};
class IRStm : public IRNode {};

class IRConst : public IRExp 
{
    public:
        int value;

    public:
        IRConst(int value);
        string toString();
};

class IRName : public IRExp
{
    public:
        string label;

    public:
        IRName(string label);
        string toString();
};

class IRTemp : public IRExp
{
    public:
        string temp;

    public:
        IRTemp(string temp);
        string toString();
};

class IRBinop : public IRExp
{
   public:
        int binop;
        IRExp *lExp;
        IRExp *rExp;

    public:
        IRBinop(int binop, IRExp *lExp, IRExp *rExp);
        string toString();
};

class IRMem : public IRExp
{
    public:
        IRExp *exp;

    public:
        IRMem(IRExp *exp);
        string toString();
};

class IRCall : public IRExp
{
    public:
        IRLabel *label;
        vector <IRExp*> *args;

    public:
        IRCall(IRLabel *label, vector <IRExp*> *args);
        string toString();
};

class IREseq : public IRExp
{
    public:
        IRStm *stm;
        IRExp *exp;

    public:
        IREseq(IRStm *stm, IRExp *exp);
        string toString();
};

class IRExpList : public IRExp
{
    public:
        vector <IRExp*> *exps;
    
    public:
        IRExpList(vector <IRExp*> *exps);
	string toString();
};

class IRMove : public IRStm
{
    public:
        IRExp *dst;
        IRExp *src;

    public:
        IRMove(IRExp *dst, IRExp *src);	
        string toString();
};


class IRJump : public IRStm
{
    public:
        IRLabel *label;
	IRExp *exp;

    public:
        IRJump(IRLabel *label, IRExp *exp);
        string toString();
};

class IRCJump : public IRStm
{
    public:
        int relop;
        IRExp *lExp;
        IRExp *rExp;
        IRLabel *iftrue;
        IRLabel *iffalse;

    public:
        IRCJump(int relop, IRExp *lExp, IRExp *rExp, IRLabel *iftrue, IRLabel *iffalse);
        string toString();
};

class IRSeq : public IRStm
{
    public:
        IRStm *left;
        IRStm *right;

    public:
        IRSeq(IRStm *left, IRStm *right);
        string toString();
};

class IRLabel : public IRStm
{
    public: 
        string label;

    public:
        IRLabel(string label);
        string toString();
};

#endif
