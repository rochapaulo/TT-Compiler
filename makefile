CC = clang++
BISON = bison++
FLEX = flex++
EXEC = parser

all: $(EXEC) clean

parser.cc: parser.y
	$(BISON) -d -o parser.cc parser.y

lex.yy.cc: scanner.l
	$(FLEX) scanner.l

parser: parser.cc lex.yy.cc
	$(CC) -o parser parser.cc lex.yy.cc main.cpp

install: all
	@mkdir build
	@mv $(EXEC) build

clean:
	rm -rf *.cc *.h
