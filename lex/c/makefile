CC = gcc
LD = gcc
PROGRAM = parser

all: $(PROGRAM) clean

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: scanner.l
	flex scanner.l

parser: parser.tab.c parser.tab.h lex.yy.c
	gcc parser.tab.c lex.yy.c -lfl -o parser

clean:
	rm -rf *.c *.h
