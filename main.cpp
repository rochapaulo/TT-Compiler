#include <iostream>
#include "Node.h"
using namespace std;

extern Node * root;
extern int yyparse();

int main(int argc, char **argv) {
    yyparse();
    cout << "Hello World!" << endl;
    cout << root << endl;
    return 0;
}
