#include <vector>
#include <string>
#include <sstream>

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
    public:
        int lin;
        int col;

    public:
        virtual ~Node()
        {
        }

        void set_line(int lin)
        {
            this->lin = lin;
        }
        
        void set_column(int col)
        {
            this->col = col;
        }

        virtual string to_string() = 0;

};

class NExpression : public Node
{
};

class NStatement : public Node
{
};

class AST_Program : public Node
{
    public:
        vector <NStatement*> *stmList;
        NExpression *exp;

    public:
        AST_Program(vector<NStatement*> *stmList, NExpression *exp)
        {
            this->stmList = stmList;
            this->exp = exp;
        }

        string to_string()
        {
            stringstream stream;
            stream << "<STATEMENTS_SECTION>\n" << "</STATEMENTS_SECTION>\n"
                   << "<EXPRESSION_SECTION>\n" << exp->to_string() << "</EXPRESSION_SECTION>\n";
            return (stream.str());
        }
};

class NBinaryOperation : public NExpression
{
    public:
        NExpression *rExp;
        NExpression *lExp;
        int op;

    public:
        NBinaryOperation(NExpression *lExp, int op, NExpression *rExp)
        {
            this->rExp = rExp;
            this->lExp = lExp;
            this->op = op;
        }

        string to_string()
        {
            stringstream stream;
            stream << "<BINARY_OPERATION>\n" 
                   << "<RIGHT_EXPRESSION>\n" << rExp->to_string() << "</RIGHT_EXPRESSION>\n"
                   << "<OPERATION\n>" << op << "\n</OPERATION>\n"
                   << "<LEFT_EXPRESSION>\n"  << lExp->to_string() << "</LEFT_EXPRESSION>\n"
                   << "</BINARY_OPERATION>\n";
            return stream.str();
        }
};

class NInteger : public NExpression
{
    public:
        int value;
    
    public:
        NInteger(int value)
        {
            this->value = value;
        }

        string to_string()
        {
            stringstream stream;
            stream << "<INTEGER>\n" << value << "\n</INTEGER>\n";
            return stream.str();
        }
};

class NNegation : public NExpression
{
    public:
        NExpression *exp;

    public:
        NNegation(NExpression *exp)
        {
            this->exp = exp;
        }

        string to_string()
        {
            stringstream stream;
            stream << "<NEGATION>\n" + exp->to_string() + "</NEGATION>\n";
            return stream.str();
        }
};

class NReturn : public NExpression
{
    public:
        NExpression *exp;

    public:
        NReturn(NExpression *exp)
        {
            this->exp = exp;
        }
        
        string to_string()
        {
            stringstream stream;
            stream << "<RETURN\n>" << exp->to_string() << "</RETURN>\n";
            return stream.str();
        }
};

class NIdentifier : public NExpression
{
    public:
        string *identifier;

    public:
        NIdentifier(string *identifier)
        {
            this->identifier = identifier;
        }

        string to_string()
        {
            stringstream stream;
            stream << "<IDENTIFIER>\n" << identifier << "</IDENTIFIER>\n";
            return stream.str();
        }
};

class NLValue : public NExpression
{
    public:
        NIdentifier *identifier;
        vector <NExpression*> *indexList;
        
    public:
        NLValue(NIdentifier *identifier, vector <NExpression*> *indexList)
        {
            this->identifier = identifier; 
            this->indexList = indexList;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NAssign : public NExpression
{
    public:
        NLValue *lvalue;
        NExpression *exp;

    public:
        NAssign(NLValue *lvalue, NExpression *exp)
        {
            this->lvalue = lvalue;
            this->exp = exp;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NIf : public NExpression
{
    public:
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

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NWhile : public NExpression
{
    public:
        NExpression *cond;
        NExpression *body;

    public:
        NWhile(NExpression *cond, NExpression *body)
        {
            this->cond = cond;
            this->body = body;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NFor : public NExpression
{
    public:
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

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NBreak : public NExpression
{
    public:
        NBreak()
        {
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NArrayCreation : public NExpression
{
    public:
        NIdentifier *identifier;
        int dimension;

    public:
        NArrayCreation(NIdentifier *identifier, int dimension)
        {
            this->identifier = identifier;
            this->dimension = dimension;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};


class NFunctionCall : public NExpression
{
    public:
        NIdentifier *identifier;
        vector <NExpression*> *args;

    public:
        NFunctionCall(NIdentifier *identifier, vector<NExpression*> *args)
        {
            this->identifier = identifier;
            this->args = args;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NExpressionList : public NExpression
{
    public:
        vector<NExpression*> *expList;

    public:
        NExpressionList(vector<NExpression*> *expList)
        {
            this->expList = expList;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
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
        NFunctionDec(NIdentifier *identifier, vector<NIdentifier*> *args, NExpression *exp)
        {
            this->identifier = identifier;
            this->args = args;
            this->exp = exp;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};

class NImport : public NStatement
{
    public:
        NIdentifier *identifier;

    public:
        NImport(NIdentifier *identifier)
        {
            this->identifier = identifier;
        }

        string to_string()
        {
            // TODO
            return "<TODO>";
        }
};
