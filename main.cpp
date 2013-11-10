#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include "TreeAnalyzer.h"
#include "Node.h"

using namespace std;

extern AST_Program * ast_program;
extern FILE *yyin, *yyout;
extern int yyparse();

string getOperation(int);

int main(int argc, char *argv[]) {

    if (argc < 3) {
        cout << "Please specify the input and output file" << endl;
        exit(0);
    }

    FILE *p_infile = fopen(argv[1], "r");
    if(!p_infile) {
        cout << "couldn't open file" << endl;
        exit(0);
    }
    
    FILE *p_outfile = fopen(argv[2], "w");
    if(!p_outfile) {
        cout << "couldn't write file" << endl;
        exit(0);
    }

    yyin = p_infile;
    cout << "Parsing Program ..." << endl;
    if (yyparse() == 0)	{
        cout << "Parse complete." << endl;
        
	ofstream outfile(argv[2]);
        outfile << ast_program->to_string();
   }

    cout << "Analyzing Semantics ..." << endl; 

    TreeAnalyzer analyzer = TreeAnalyzer();

    cout << "teste" << endl;

    ast_program->analyze(&analyzer);

    fclose(p_infile);
    fclose(p_outfile);

    return 1;
}


