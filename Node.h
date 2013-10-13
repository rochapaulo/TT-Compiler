#include <string>
#include <vector>

using namespace std;

/* --------------- classes -------------- */
class Node;
class AST_Program;

class NExpression;
class NBinaryOperation;
class NIf;
class NWhile;
class NFor;
class NBreak;
class NArray;
class NRecord;
class NFunctionCall;
class NSimpleVar;

class NStatement;
class NFunctionDec;
class NImport;
class NField;
/* -------------------------------------- */

typedef vector<NStatement*> NStatementList;
typedef vector<NExpression*> NExpressionList;
typedef vector<NField*> NFieldList;


class Node 
{
    int line;
    int column;
};

class AST_Program : public Node 
{
    Node node;

    public: 
        AST_Program(int line, int column, Node node) :
        line(line),
        column(column),
        node(node) { }
};

class NExpression : public Node {};
class NStatement  : public Node {};

class NBinaryOperation : public NExpression
{
    NExpression l_exp;
    NExpression r_exp;
    int op;

    public:
        NBinaryOperation(NExpression l_exp, int op, NExpression r_exp) : 
        l_exp(l_exp),
        op(op),
        r_exp(r_exp) { }
};

class NIf : public NExpression 
{
    NExpression condition;
    NExpression exp_1;
    NExpression exp_2;
    
    public:
        NIf(NExpression condition, NExpression exp_1, NExpression exp_2) :
        condition(condition),
        exp_1(exp_1),
        exp_2(exp_2) { }
};

class NWhile : public NExpression
{
    NExpression condition;
    NExpression body;

    public:
        NWhile(NExpression condition, NExpression body) :
        condition(condition),
        body(body) { }
};

class NFor : public NExpression
{
    string identifier;
    NExpression init_exp;
    NExpression to_exp;
    NExpression do_exp;

    public:
        NFor(string identifier, NExpression init_exp, NExpression to_exp, NExpression do_exp) :
        identifier(identifier),
        init_exp(init_exp),
        to_exp(to_exp),
        do_exp(do_exp) { }
};

class NBreak : public NExpression 
{
    public:
        NBreak() { }
};

class NArray : public NArray 
{
    string identifier;
    NExpressionList elements;

    public:
        NArray(string identifier, NExpressionList elements) :
        identifier(identifier),
        elements(elements) { }
};

class NRecord : public NExpression 
{
    string identifier;
    NExpressionList elements;
   
    public:
        NRecord(string identifier, NExpressionList elements) :
        identifier(identifier),
        elements(elements) { }
};

class NField() : public NExpression 
{
    string identifier;
    NExpression exp;

    public:
        NField(string identifier, NExpression exp) :
        identifier(identifier),
        exp(exp) { }
};

class NFunctionCall : public NExpression 
{
    string identifier;
    NExpressionList args;
    
    public:
        NFunctionCall(string identifier, NExpressionList args) :
        identifier(identifier),
        args(args) { }
};

class NSimpleVar : public NStatement 
{
    string identifier;
    NExpression exp;

    public:
        NSimpleVar(string identifier, NExpression exp) :
        identifier(identifier),
        exp(exp) { }
};

class NFunctionDec : public NStatement
{
    string identifier;
    NFIeldList tyfields;
    NExpression body;

    public:
        NFunctionDec(string identifier, NFieldList tyfields, NExpression body) :
        identifier(identifier),
        tyfields(tyfields),
        body(body) { }
};

class NImport : public NStatement
{
    string identifier;

    public:
        NImport(string identifier) :
        identifier(identifier) { }
};

class NField {
    string identifier_1;
    string identifier_2;

    public:
        NField(string identifier_1, string identifier_2) :
        identifier_1(identifier_1),
        identifier_2(identifier_2) { }
};
