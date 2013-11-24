#include <vector>
#include <string>

using namespace std;

class IRLabel;

class IRNode
{
    public:
        virtual ~IRNode() {}
        virtual string toString() = 0;
};

class IRExp : public IRNode {};
class IRStm : public IRNode {};

class IRConst : public IRExp 
{
    public:
        int value;

    public:
        IRConst(int value);
        virtual string toString();
};

class IRName : public IRExp
{
    public:
        string label;

    public:
        IRName(string label);
        virtual string toString();
};

class IRTemp : public IRExp
{
    public:
        string temp;

    public:
        IRTemp(string temp);
        virtual string toString();
};

class IRBinop : public IRExp
{
    public:
        int binop;
        IRExp *lExp;
        IRExp *rExp;

    public:
        IRBinop(int binop, IRExp *lExp, IRExp *rExp);
        virtual string toString();
};

class IRMem : public IRExp
{
    public:
        IRExp *exp;

    public:
        IRMem(IRExp *exp);
        virtual string toString();
};

class IRCall : public IRExp
{
    public:
        IRExp *func;
        vector <IRExp*> *args;

    public:
        IRCall(IRExp *func, vector <IRExp*> *args);
        virtual string toString();
};

class IREsec : public IRExp
{
    public:
        IRStm *stm;
        IRExp *exp;

    public:
        IREsec(IRStm *stm, IRExp *exp);
        virtual string toString();
};


class IRMove : public IRStm
{
    public:
        IRExp *dst;
        IRExp *src;

    public:
        IRMove(IRExp *dst, IRExp *src);	
        virtual string toString();
};


class IRJump : public IRStm
{
    public:
        IRLabel *label;

    public:
        IRJump(IRLabel *label);
        virtual string toString();
};

class IRCJump : public IRStm
{
    public:
        int relop;
        IRExp *exp;
        IRLabel *iftrue;
        IRLabel *iffalse;

    public:
        IRCJump(int relop, IRExp *exp, IRLabel *iftrue, IRLabel *iffalse);
        virtual string toString();
};

class IRSeq : public IRStm
{
    public:
        IRStm *left;
        IRStm *right;

    public:
        IRSeq(IRStm *left, IRStm *right);
        virtual string toString();
};

class IRLabel : public IRStm
{
    public: 
        string label;

    public:
        IRLabel(string label);
        virtual string toString();
};



