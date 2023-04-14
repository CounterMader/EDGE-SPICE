#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "parser.h"
#include "log.h"
#include "hash.h"
#include "defs.h"

extern FILE* yyin;
extern int yyparse();

int main(int argc, char **argv){
    if(argc > 1){
        parse(argv[1]);
    }
    print_element_table(htab);
    printf("-------------------------\n");
    print_node_table(htab);
    //printf("%s value is : %d\n",argv[2],search_node(htab, argv[2]) -> number);
    printf("-------------------------\n");
    printf("Node number = %d\n",htab -> n_numsyms);
    printf("Element number = %d\n",htab -> e_numsyms);
    get_MNA_size(circuit, htab);
    printf("MNA matrix size is %d\n", circuit -> MNA_size);
    free_hash_table(htab);
    //free_ckt(circuit);
    return 0;
}
