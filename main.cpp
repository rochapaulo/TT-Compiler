#include <iostream>
#include "Node.h"
using namespace std;

extern Node * syntaxTree_root;
extern int yyparse();

int main(int argc, char **argv) {
    yyparse();

    NBinaryOperator binop = *((NBinaryOperator*)syntaxTree_root);
    int v = binop.getOp();

    cout << v << endl;

    cout << "Hello World!" << endl;
    return 0;
}
