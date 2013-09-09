CC = clang++
FLEX = flex++
BISON = bison++
PROGRAM = parser

all: $(PROGRAM) clean

y.tab.c: parser.y
	$(BISON) -d parser.y

lex.yy.cc: scanner.l
	$(FLEX) scanner.l

parser: y.tab.c y.tab.h lex.yy.cc
	$(CC) y.tab.c lex.yy.cc -ll -o parser

clean:
	rm -rf *.c *.h
