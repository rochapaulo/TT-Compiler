CC = g++
BISON = bison
FLEX = flex
EXEC = parser

all: $(EXEC) clean

parser.cc: parser.y
	$(BISON) -d -o parser.cpp parser.y

lex.yy.cc: scanner.l
	$(FLEX) scanner.l

parser: parser.cc lex.yy.cc
	$(CC) -o parser parser.cpp lex.yy.c main.cpp -ll

install: all
	@mkdir -p build
	@mv $(EXEC) build

clean:
	rm *.c parser.cpp parser.h
