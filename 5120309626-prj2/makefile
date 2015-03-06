LEX=flex
YACC=bison
CC=g++ -std=gnu++11

scc:lex.yy.o smallc.tab.o GenIntermediate.o Intermediate.o MIPS32.o
	$(CC) lex.yy.o smallc.tab.o GenIntermediate.o Intermediate.o MIPS32.o -o scc

GenIntermediate.o:GenIntermediate.cpp GenIntermediate.h Intermediate.h SymbolTable.h Info.h MIPS32.h
	$(CC) -c GenIntermediate.cpp

MIPS32.o:MIPS32.cpp MIPS32.h
	$(CC) -c MIPS32.cpp

Intermediate.o:Intermediate.cpp Intermediate.h
	$(CC) -c Intermediate.cpp

lex.yy.o:lex.yy.c smallc.tab.h main.hpp
	$(CC) -c lex.yy.c

smallc.tab.o:smallc.tab.c main.hpp Info.h GenIntermediate.h Intermediate.h SymbolTable.h MIPS32.h
	$(CC) -c smallc.tab.c

smallc.tab.c smallc.tab.h:smallc.y
	$(YACC) -d smallc.y

lex.yy.c:smallc.l
	$(LEX) smallc.l

clean:
	@rm -f *.o *.yy.c *.yy.o *.tab.* InterCode MIPSCode.s scc 

