CC = c++
BISON = bison
FLEX = flex
EXEC = parser
PATH = ./build/

path: 
	@mkdir -p $(PATH)

parser.cpp: parser.y
	@$(BISON) -d -o $(PATH)parser.cpp parser.y
	@if [ -a $(PAHT)parser.hpp ]; then mv $(PATH)parser.hpp $(PATH)parser.h; fi;

lex.yy.c: scanner.l
	@$(FLEX) scanner.l
	@mv lex.yy.c $(PATH)lex.yy.c

parser: main.cpp
	@$(CC) -o $(PATH)parser $(PATH)parser.cpp $(PATH)lex.yy.c main.cpp -ll

install: path parser.cpp lex.yy.c parser

clean:
	rm -r $(PATH)
