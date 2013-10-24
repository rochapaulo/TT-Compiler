#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

#define PLUS    273
#define MINUS   274
#define MUL     275
#define DIV     276
#define EQUAL   277
#define OPDIF   278
#define OPGE    279
#define OPLE    280
#define OPG     281
#define OPL     282
#define AND     283
#define OR      284

using namespace std;

extern AST_Program * ast_program;
extern FILE *yyin;
extern FILE *yyout;
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
    yyparse();
    cout << "Parse complete." << endl;
    fclose(p_infile);
    fclose(p_outfile);

    cout << "Result: " << endl;
    NBinaryOperation binop = *((NBinaryOperation*) ast_program->exp);
    cout << " -leftExp: " << (*(NInteger*)binop.lExp).value << endl;
    cout << " -operation: " << getOperation(binop.op) << endl;
    cout << " -rightExp: " << (*(NInteger*)binop.rExp).value << endl;

    cout << binop.to_string() << endl;

    return 1;
};

string getOperation(int key) {
    switch (key) {
        case PLUS:
            return "PLUS";
        break;

        case MINUS:
            return "MINUS";
        break;
    }
};
