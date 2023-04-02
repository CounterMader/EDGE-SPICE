compile:
	flex parser.l
	bison -d parser.y
	gcc -o spice.out main.c parser.c lex.yy.c parser.tab.c
