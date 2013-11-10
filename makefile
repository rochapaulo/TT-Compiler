CC = c++
BISON = bison
FLEX = flex
EXEC = parser
PATHS = -I./analyzer -I./
FILES = parser.cpp lex.yy.c Node.cpp ./analyzer/TreeAnalyzer.cpp main.cpp

all: $(EXEC) clean

parser.cpp: parser.y
	@$(BISON) -d -o parser.cpp parser.y
	@if [ -a parser.hpp ]; then mv parser.hpp parser.h; fi;

lex.yy.c: scanner.l
	@$(FLEX) scanner.l

parser: $(FILES)
	@$(CC) $(FILES) -o parser -ll $(PATHS)

install: all
	@mkdir -p build
	@mv $(EXEC) build

clean:
	@rm *.c parser.cpp parser.h
