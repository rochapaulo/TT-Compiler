#include <vector>
#include <string>
#include <sstream>
#include "TreeAnalyzer.h"

class Node;
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
class NArrayCreation;
class NArray;
class NArrayAssign;
class NFunctionCall;
class NExpressionList;
class NInteger;
class NFunctionDec;
class NImport;

using namespace std;

class Node
{
    public:
        int lin;
        int col;

    public:
        virtual ~Node() { }

        virtual string toString() = 0;
        virtual void analyze(TreeAnalyzer *analyzer) = 0;

        void setLine(int lin);
        void setColumn(int col);
};

class NExpression : public Node { };

class NStatement : public Node { };

class AST_Program : public Node
{
    public:
        vector <NStatement*> *stmList;
	vector <NExpression*> *expList;

    public:
        AST_Program(vector<NStatement*> *stmList, vector<NExpression*> *expList, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NBinaryOperation : public NExpression
{
    public:
        NExpression *rExp;
        NExpression *lExp;
        int op;

    public:
        NBinaryOperation(NExpression *lExp, int op, NExpression *rExp, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NInteger : public NExpression
{
    public:
        int value;

    public:
        NInteger(int value, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NNegation : public NExpression
{
    public:
        NExpression *exp;

    public:
        NNegation(NExpression *exp, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NReturn : public NExpression
{
    public:
        NExpression *exp;

    public:
        NReturn(NExpression *exp, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NIdentifier : public NExpression
{
    public:
        string identifier;

    public:
        NIdentifier(char *identifier, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
    
};


class NAssign : public NExpression
{
    public:
        NIdentifier *identifier;
        NExpression *exp;

    public:
        NAssign(NIdentifier *identifier, NExpression *exp, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NIf : public NExpression
{
    public:
        NExpression *cond;
        NExpression *trueExp;
        NExpression *falseExp;

    public:
        NIf(NExpression *cond, NExpression *trueExp, NExpression *falseExp, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NWhile : public NExpression
{
    public:
        NExpression *cond;
        NExpression *body;

    public:
        NWhile(NExpression *cond, NExpression *body, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NFor : public NExpression
{
    public:
        NIdentifier *identifier;
        NExpression *initExp;
        NExpression *endExp;
        NExpression *body;        

    public:
        NFor(NIdentifier *identifier, NExpression *initExp, NExpression *endExp, NExpression *body, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NBreak : public NExpression
{
    public:
        NBreak(int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
    
};

class NArrayCreation : public NExpression
{
    public:
        NIdentifier *identifier;
        int dimension;

    public:
        NArrayCreation(NIdentifier *identifier, int dimension, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);

};


class NArray : public NExpression
{
    public:
        NIdentifier *identifier;
	vector <NExpression*> *indexList;

    public:
        NArray(NIdentifier *identifier, vector <NExpression*> *indexList, int lin, int col);
	virtual string toString();
	virtual void analyze(TreeAnalyzer *analyzer);
};

class NArrayAssign : public NExpression
{
    public:
        NArray *array;
	NExpression *exp;

    public:
        NArrayAssign(NArray *array, NExpression *exp, int lin, int col);
	virtual string toString();
	virtual void analyze(TreeAnalyzer *analyzer);
};

class NFunctionCall : public NExpression
{
    public:
        NIdentifier *identifier;
        vector <NExpression*> *args;

    public:
    NFunctionCall(NIdentifier *identifier, vector<NExpression*> *args, int lin, int col);
    virtual string toString();
    virtual void analyze(TreeAnalyzer *analyzer);

};

class NExpressionList : public NExpression
{
    public:
        vector<NExpression*> *expList;

    public:
    NExpressionList(vector<NExpression*> *expList, int lin, int col);
    virtual string toString();
    virtual void analyze(TreeAnalyzer *analyzer);
    
};


/*
   DECLARATIONS
 */

class NFunctionDec : public NStatement
{
    public:
        NIdentifier *identifier;
        vector<NIdentifier*> *args;
        NExpression *exp;

    public:
        NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp, int lin, int col);
        virtual string toString();
        virtual void analyze(TreeAnalyzer *analyzer);
    
};

class NImport : public NStatement
{
    public:
        NIdentifier *identifier;

    public:
    NImport(NIdentifier *identifier, int lin, int col);
    virtual string toString();
    virtual void analyze(TreeAnalyzer *analyzer);
    
};

