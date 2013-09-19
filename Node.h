#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Classes do Arquivo */
class NExpression;
class NStatement;
class NInteger;
class NBinaryOperator;
class NWhile;

typedef vector<NExpression*> ExpressionList;
typedef vector<NStatement*> StatementList;

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
};


class NWhile : public NExpression {
private:
    NExpression& condition;
    NExpression& body;

public: 
    NWhile(NExpression& condition, NExpression& body) : condition(condition), body(body) { }
};

