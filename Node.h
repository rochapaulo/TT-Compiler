#include <vector>
#include <string>

using namespace std;

class NExpression;
class NStatement;
class AST_Program;
class NBinaryOperation;
class NNegation;
class NReturn;
class NIdentifier;
class NAssign;
class NIf;
class NWhile;
class NFor;
class NBreak;
class NLValue;
class NArrayCreation;
class NFunCall;
class NInteger;
class NFunctionDec;
class NImport;

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

class NExpression : public Node
{
};

class NStatement : public Node
{
};

class AST_Program : public Node
{
    private:
        vector <NStatement*> *stmList;
        NExpression *exp;

    public:
        AST_Program(vector<NStatement*> *stmList, NExpression *exp)
        {
            this->stmList = stmList;
            this->exp = exp;
        }
};

class NBinaryOperation : public NExpression
{
    private:
        NExpression *rExp;
        NExpression *lExp;
        int op;

    public:
        NBinaryOperation(NExpression *rExp, int op, NExpression *lExp)
        {
            this->rExp = rExp;
            this->lExp = lExp;
            this->op = op;
        }
};

class NInteger : public NExpression
{
    private:
        int value;
    
    public:
        NInteger(int value)
        {
            this->value = value;
        }
};

class NNegation : public NExpression
{
    private:
        NExpression *exp;

    public:
        NNegation(NExpression *exp)
        {
            this->exp = exp;
        }
};

class NReturn : public NExpression
{
    private:
        NExpression *exp;

    public:
        NReturn(NExpression *exp)
        {
            this->exp = exp;
        }
};

class NIdentifier : public NExpression
{
    private:
        string *identifier;

    public:
        NIdentifier(string *identifier)
        {
            this->identifier = identifier;
        }
};

class NLValue : public NExpression
{
    private:
        NIdentifier *identifier;
        vector <NExpression*> *indexList;
        
    public:
        NLValue(NIdentifier *identifier, vector <NExpression*> *indexList)
        {
            this->identifier = identifier; 
            this->indexList = indexList;
        }
};

class NAssign : public NExpression
{
    private:
        NLValue *lvalue;
        NExpression *exp;

    public:
        NAssign(NLValue *lvalue, NExpression *exp)
        {
            this->lvalue = lvalue;
            this->exp = exp;
        }
};

class NIf : public NExpression
{
    private:
        NExpression *cond;
        NExpression *trueExp;
        NExpression *falseExp;

    public:
        NIf(NExpression *cond, NExpression *trueExp, NExpression *falseExp)
        {
            this->cond = cond;
            this->trueExp = trueExp;
            this->falseExp = falseExp;
        }
};

class NWhile : public NExpression
{
    private:
        NExpression *cond;
        NExpression *body;

    public:
        NWhile(NExpression *cond, NExpression *body)
        {
            this->cond = cond;
            this->body = body;
        }
};

class NFor : public NExpression
{
    private:
        NIdentifier *identifier;
        NExpression *initExp;
        NExpression *endExp;
        NExpression *body;        

    public:
        NFor(NIdentifier *identifier, NExpression *initExp, NExpression *endExp, NExpression *body)
        {
            this->identifier = identifier;
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
        NIdentifier *identifier;
        int dimension;

    public:
        NArrayCreation(NIdentifier *identifier, int dimension)
        {
            this->identifier = identifier;
            this->dimension = dimension;
        }
};


class NFunctionCall : public NExpression
{
    private:
        NIdentifier *identifier;
        vector <NExpression*> *args;

    public:
        NFunctionCall(NIdentifier *identifier, vector<NExpression*> *args)
        {
            this->identifier = identifier;
            this->args = args;
        }
};

class NExpressionList : public NExpression
{
    private:
        vector<NExpression*> *expList;

    public:
        NExpressionList(vector<NExpression*> *expList)
        {
            this->expList = expList;
        }
};


/*
    DECLARATIONS
*/

class NFunctionDec : public NStatement
{
    private:
        NIdentifier *identifier;
        vector<NIdentifier*> *args;
        NExpression *exp;

    public:
        NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp)
        {
            this->identifier = identifier;
            this->args = args;
            this->exp = exp;
        }
};

class NImport : public NStatement
{
    private:
        NIdentifier *identifier;

    public:
        NImport(NIdentifier *identifier)
        {
            this->identifier = identifier;
        }
};
