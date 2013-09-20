#include <iostream>
#include "Node.h"
using namespace std;

extern Node * root;
extern int yyparse();

int main(int argc, char **argv) {
    yyparse();

    NBinaryOperator binop = *((NBinaryOperator*)root);
    int v = binop.getOp();

    cout << v << endl;

    cout << "Hello World!" << endl;
    return 0;
}
