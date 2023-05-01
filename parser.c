#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "log.h"
#include "hash.h"
#include "source.h"

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
    
    yyparse();
}

void add_RLC(char *eid, int node1, int node2, double value,int group){
    if(elm_insert(htab, eid, NULL, node1, node2, NO_NODE, NO_NODE, value, group)){
        log_error("Duplicated Element %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_V(char *eid, int node1, int node2, double value){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    if(elm_insert(htab, eid, NULL, node1, node2, NO_NODE, NO_NODE, value, 2)){
        log_error("Duplicated Voltage Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }

    //new routine
    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, DC, 2);
    stab -> dc_src = create_dc_s(value);
     if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_I(char *eid, int node1, int node2, double value, int group){
    //Consistency Requirement check FUTURE!
    if(elm_insert(htab, eid, NULL, node1, node2, NO_NODE, NO_NODE, value, group)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }

    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, DC, group);
    stab -> dc_src = create_dc_s(value);
     if(src_insert(htab, stab)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_VCCS(char *eid, int node1, int node2, int node3, int node4, double value, int group){
    if(elm_insert(htab, eid, NULL, node1, node2, node3, node4, value, group)){
        log_error("Duplicated VCCS : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_VCVS(char *eid, int node1, int node2, int node3, int node4, double value, int group){
    if(elm_insert(htab, eid, NULL, node1, node2, node3, node4, value, group)){
        log_error("Duplicated VCVS : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_CCCS(char *eid, char *cvs, int node1, int node2, double value, int group){
    if(elm_insert(htab, eid, cvs, node1, node2, NO_NODE, NO_NODE, value, group)){
        log_error("Duplicated CCCS : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }

}

void add_node(int num){
    char buf[11];
    sprintf(buf,"%d",num);
     if(node_exist(htab, buf)){
        node_insert(htab,buf,num);
    }
}
void set_simultaor_dc(){
    if(!(circuit -> simulate_type == NULL_SYM)){
        log_error("SIMULATOR Already SET!");
        return;
    }

    circuit -> simulate_type = DC_SYM;

    node_voltage_initial(htab, 1);
    element_current_initial(htab, 1);
    log_trace("current and voltage allocation success!");
}

void set_simultaor_tran(double Tstop, double Tstep){
    if(circuit -> simulate_type != NULL_SYM){
        log_error("SIMULATOR Already SET!");
        return;
    }

    circuit -> simulate_type = TRAN_SYM;
    circuit -> Tstart = 0;
    circuit -> Tstep = Tstep;
    circuit -> Tstop = Tstop;

    circuit -> step_num = (int)(Tstop/Tstep);

    node_voltage_initial(htab, circuit -> step_num + 1);
    element_current_initial(htab, circuit -> step_num + 1);
    log_trace("current and voltage allocation success! %d, Tstep = %f, Tstop = %f",circuit -> step_num,circuit -> Tstep, circuit -> Tstop);

}

void yyerror(char *msg){
    log_fatal("%s in line %d", msg, yylineno);
}