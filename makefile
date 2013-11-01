CC = g++
BISON = bison
FLEX = flex
EXEC = parser

all: $(EXEC) install

parser.cc: parser.y
	@$(BISON) -d -o parser.cpp parser.y
	if [ -a parser.hpp ]; then mv parser.hpp parser.h; fi;

lex.yy.cc: scanner.l
	@$(FLEX) scanner.l

parser: parser.cc lex.yy.cc
	@$(CC) -o parser parser.cpp lex.yy.c main.cpp -ll

install: clean
	@mkdir -p build
	@mv $(EXEC) build

clean:
	@rm *.c parser.cpp parser.h
