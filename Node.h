#include <vector>
#include <string>
#include <sstream>
#include "TreeAnalyzer.h"

//class TreeAnalyzer;
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
class NLValue;
class NArrayCreation;
class NFunctionCall;
class NExpressionList;
class NInteger;
class NFunctionDec;
class NImport;

using namespace std;

class Node
{
    private:
        int lin;
        int col;

    public:
        virtual ~Node() { }

        virtual string to_string() = 0;
        virtual void analyze(TreeAnalyzer *analyzer) = 0;

        void set_line(int lin);
        void set_column(int col);
};

class NExpression : public Node { };

class NStatement : public Node { };

class AST_Program : public Node
{
    private:
        vector <NStatement*> *stmList;
	vector <NExpression*> *expList;

    public:
        AST_Program(vector<NStatement*> *stmList, vector<NExpression*> *expList, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NBinaryOperation : public NExpression
{
    private:
        NExpression *rExp;
        NExpression *lExp;
        int op;

    public:
        NBinaryOperation(NExpression *lExp, int op, NExpression *rExp, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NInteger : public NExpression
{
    private:
        int value;

    public:
        NInteger(int value, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NNegation : public NExpression
{
    private:
        NExpression *exp;

    public:
        NNegation(NExpression *exp, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NReturn : public NExpression
{
    private:
        NExpression *exp;

    public:
        NReturn(NExpression *exp, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
};

class NIdentifier : public NExpression
{
    private:
        string identifier;

    public:
        NIdentifier(char *identifier, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
    
};

class NLValue : public NExpression
{
    private:
        NIdentifier *identifier;
        vector <NExpression*> *indexList;

    public:
        NLValue(NIdentifier *identifier, vector <NExpression*> *indexList, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NAssign : public NExpression
{
    private:
        NLValue *lvalue;
        NExpression *exp;

    public:
        NAssign(NLValue *lvalue, NExpression *exp, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NIf : public NExpression
{
    private:
        NExpression *cond;
        NExpression *trueExp;
        NExpression *falseExp;

    public:
        NIf(NExpression *cond, NExpression *trueExp, NExpression *falseExp, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NWhile : public NExpression
{
    private:
        NExpression *cond;
        NExpression *body;

    public:
        NWhile(NExpression *cond, NExpression *body, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NFor : public NExpression
{
    private:
        NIdentifier *identifier;
        NExpression *initExp;
        NExpression *endExp;
        NExpression *body;        

    public:
        NFor(NIdentifier *identifier, NExpression *initExp, NExpression *endExp, NExpression *body, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);

};

class NBreak : public NExpression
{
    public:
        NBreak(int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
    
};

class NArrayCreation : public NExpression
{
    private:
        NIdentifier *identifier;
        int dimension;

    public:
        NArrayCreation(NIdentifier *identifier, int dimension, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);

};


class NFunctionCall : public NExpression
{
    private:
        NIdentifier *identifier;
        vector <NExpression*> *args;

    public:
    NFunctionCall(NIdentifier *identifier, vector<NExpression*> *args, int lin, int col);
    virtual string to_string();
    virtual void analyze(TreeAnalyzer *analyzer);

};

class NExpressionList : public NExpression
{
    private:
        vector<NExpression*> *expList;

    public:
    NExpressionList(vector<NExpression*> *expList, int lin, int col);
    virtual string to_string();
    virtual void analyze(TreeAnalyzer *analyzer);
    
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
        NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp, int lin, int col);
        virtual string to_string();
        virtual void analyze(TreeAnalyzer *analyzer);
    
};

class NImport : public NStatement
{
    private:
        NIdentifier *identifier;

    public:
    NImport(NIdentifier *identifier, int lin, int col);
    virtual string to_string();
    virtual void analyze(TreeAnalyzer *analyzer);
    
};

