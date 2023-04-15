compile:
	flex parser.l
	bison -d parser.y
	gcc -o espice main.c parser.c lex.yy.c parser.tab.c log.c symbol_table.c hash.c circuit.c ESmat.c -DLOG_USE_COLOR 