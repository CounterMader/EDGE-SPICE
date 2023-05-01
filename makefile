compile:
	flex parser.l
	bison --header=./include/parser.tab.h parser.y
	gcc -o espice main.c parser.c lex.yy.c parser.tab.c log.c symbol_table.c hash.c circuit.c ESmat.c simulator.c stamps.c source.c -I./include -DLOG_USE_COLOR 