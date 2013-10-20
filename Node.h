#include <vector>
#include <stdio>
using namespace std;


class Node
{
    private:
        int lin;
        int col;

    public:
        void set_line(int lin)
        {
            this->lin = lin;
        }
        
        void set_column(int col)
        {
            this->col = col;
        }
};

class AST_Program : public Node
{
    private:
        vector <NStatement*> stmList;
        NExpression exp;

    public:
        AST_Program(vector<NStatement*> stmList, NExpression exp)
        {
            this->stmList = stmList;
            this->exp = exp;
        }
};

class NExpression : public Node
{
};

class NStatement : public Node
{
};

class NBinaryOperation : public NExpression
{
    private:
        NExpression rExp;
        NExpression lExp;
        int op;

    public:
        NBinaryOperation(NExpression rExp, NExpression lExp, int op)
        {
            this->rExp = rExp;
            this->lExp = lExp;
            this->op = op;
        }
};

class NNegation : public NExpression
{
    private:
        NExpression exp;

    public:
        NNegation(NExpression exp)
        {
            this->exp = exp;
        }
};

class NReturn : public NExpression
{
    private:
        NExpression exp;

    public:
        NReturn(NExpression exp)
        {
            this->exp = exp;
        }
};

class NIdentifier : public NExpression
{
    private:
        string identifier;

    public:
        NIdentifier(string identifier)
        {
            this->identifier = identifier;
        }
};

class NAssign : public NExpression
{
    private:
        NIdentifier identifier;
        NExpression exp;

    public:
        NAssign(NIdentifier identifier, NExpression exp)
        {
            this->identifier = identifier;
            this->exp = exp;
        }
};

class NIf : public NExpression
{
    private:
        NExpression cond;
        NExpression trueExp;
        NExpression falseExp;

    public:
        NIf(NExpression cond, NExpression trueExp, NExpression falseExp)
        {
            this->cond = cond;
            this->trueExp = trueExp;
            this->falseExp = falseExp;
        }
};

class NWhile : public NExpression
{
    private:
        NExpression cond;
        NExpression body;

    public:
        NWhile(NExpression cond, NExpression body)
        {
            this->cond = cond;
            this->body = body;
        }
};

class NFor : public NExpression
{
    private:
        string idVar;
        NExpression initExp;
        NExpression endExp;
        NExpression body;        

    public:
        NFor(string idVar, NExpression initExp, NExpression endExp, NExpression body)
        {
            this->idVar = idVar;
            this->initExp = initExp;
            this->endExp = endExp;
            this->body = body;
        }
};

class NBreak : public NExpression
{
    public:
        NBreak()
        {
        }
};

class NArrayCreation : public NExpression
{
    private:
        NIdentifier identifier;
        int dimension;

    public:
        NArrayCreation(NIdentifier identifier, int dimension)
        {
            this->identifier = identifier;
            this->dimension = dimension;
        }
};

class NArrayAccess : public NExpression
{
    private:
        NIdentifier identifier;
        vector <NExpression*> indexList;
        
    public:
        NArrayAccess(NIdentifier identifier, vector <NExpression*> indexList)
        {
            this->identifier = identifier;
            this->indexList = indexList;
        }
};

class NFunCall : public NExpression
{
    private:
        NIdentifier identifier;
        vector <NExpression*> args;

    public:
        NFunCall(NIdentifier identifier, vector<NExpression*> args)
        {
            this->identifier = identifier;
            this->args = args;
        }
};


