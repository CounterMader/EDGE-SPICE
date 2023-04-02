#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

extern FILE* yyin;
extern int yyparse();

int main(int argc, char **argv){
    if(argc > 1){
        if(!(yyin = fopen(argv[1],"r"))){
            printf("can't open file!");
            return 1;
        }
    }

    yyparse();
    return 0;
}
