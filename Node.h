#include <iostream>

using namespace std;

class Expression;
class Integer;

class Node {
public:
    virtual ~Node() {}
};

class Expression : public Node { };


class Integer : public Expression {
private:
    int value;

public:
    Integer(int value) {
        this->value = value;
    }
};
