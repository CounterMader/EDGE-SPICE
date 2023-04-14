#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "log.h"
#include "hash.h"

extern FILE* yyin;
extern int yyparse();
extern int yylineno;
extern HASH_TAB *htab;
extern CKTcircuit *circuit;

int parse(const char *file_name){
    if(!(yyin = fopen(file_name, "r"))){
        log_fatal("can't open %s",file_name);
        exit(EXIT_FAILURE);
    }
    htab = maketab(53, 5, symtab_hash_pjw, node_cmp, elm_cmp);
    circuit = makeckt();
    log_trace("SPICE initialization SUCCESS!");
    yyparse();
}

void add_RLC(char *eid, int node1, int node2, double value,int group){
    if(elm_insert(htab, eid, node1, node2, value, group)){
        log_error("Duplicated Element %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_V(char *eid, int node1, int node2, double value){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    if(elm_insert(htab, eid, node1, node2, value, 2)){
        log_error("Duplicated Voltage Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_I(char *eid, int node1, int node2, double value, int group){
    //Consistency Requirement chek FUTURE!
    if(elm_insert(htab, eid, node1, node2, value, group)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_node(int num){
    char buf[5];
    sprintf(buf,"%d",num);
    if(node_exist(htab, buf)){
        node_insert(htab,buf,num);
    }
}
void yyerror(char *msg){
    log_fatal("%s",msg);
}