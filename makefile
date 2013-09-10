CC = clang
BISON = bison
FLEX = flex
EXEC = parser

all: $(EXEC) clean

parser.tab.c: parser.y
	$(BISON) -d parser.y

lex.yy.c: scanner.l
	$(FLEX) scanner.l

parser: parser.tab.c parser.tab.h lex.yy.c
	$(CC) parser.tab.c lex.yy.c -ll -o parser

install: all
	@mkdir build
	@mv $(EXEC) build

clean:
	rm -rf *.c *.h
