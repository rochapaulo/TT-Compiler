#include <iostream>
#include "Node.h"
using namespace std;

extern Node * root;
extern int yyparse();

int main(int argc, char **argv) {
    yyparse();
    cout << "Hello World!" << endl;
    return 0;
}
