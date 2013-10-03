#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Classes do Arquivo */
class NExpression;
class NStatement;
class NInteger;
class NBinaryOperator;
class NNegExp;
class NWhile;
class NIf;
class NFor;
class NBreak;
class NReturn;

typedef vector<NExpression*> NExpressionList;
typedef vector<NStatement*> NStatementList;

/* Todas as subclasses devem derivar de Node */
class Node {
private: 
    int line, column;

public: 
    virtual ~Node() { }
};

class NExpression : public Node { };

class NStatement : public Node { };

class NInteger : public NExpression {
private:
    int value;

public:
    NInteger(int value) : value(value) { }
};

class NBinaryOperator : public NExpression {
private:
    int op;
    NExpression& rExp;
    NExpression& lExp;

public: 
    NBinaryOperator(NExpression& lExp, int op, NExpression& rExp) : op(op), rExp(rExp), lExp(lExp) { }
    
    int getOp(){
        return op;
    }
};

class NNegExp : public NExpression {
private:
    NExpression& exp;

public:
    NNegExp(NExpression& exp) : exp(exp) { }
};

class NWhile : public NExpression {
private:
    NExpression& condition;
    NExpression& body;

public: 
    NWhile(NExpression& condition, NExpression& body) : condition(condition), body(body) { }
};

class NIf : public NExpression {
private:
    NExpression& condition;
    NExpression& bodyIf;
    NExpression& bodyElse;

public:
    NIf(NExpression& condition, NExpression& bodyIf, NExpression& bodyElse) : condition(condition), bodyIf(bodyIf), bodyElse(bodyElse) { }
};

class NFor : public NExpression {
private:
    NExpression& initExp;
    NExpression& endExp;
    NExpression& body;

public:
    NFor(NExpression& initExp, NExpression& endExp, NExpression& body) : initExp(initExp), endExp(endExp), body(body) { }
};

class NBreak : public NExpression {
public:
    NBreak() { }
};

class NReturn : public NExpression {
private:
    NExpression& exp;

public:
    NReturn(NExpression& exp) : exp(exp) { }
};

class NIdentifier : public NExpression {
private:
    string value;

public:
    NIdentifier(string value) : value(value) { }
};
