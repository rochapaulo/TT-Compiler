CC = c++
BISON = bison
FLEX = flex
EXEC = parser
PATHS = -I./analyzer -I./

all: $(EXEC) clean

parser.cpp: parser.y
	@$(BISON) -d -o parser.cpp parser.y
	if [ -a parser.hpp ]; then mv parser.hpp parser.h; fi;

lex.yy.c: scanner.l
	@$(FLEX) scanner.l

parser: parser.cpp lex.yy.c
	@$(CC) -o parser parser.cpp lex.yy.c ./analyzer/TreeAnalyzer.cpp main.cpp -ll $(PATHS)

install: all
	@mkdir -p build
	@mv $(EXEC) build

clean:
	@rm *.c parser.cpp parser.h
