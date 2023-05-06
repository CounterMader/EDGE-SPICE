#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if(elm_insert(htab, eid, NULL, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NO_NODE, NO_NODE, value, group)){
        log_error("Duplicated Element %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_V(char *eid, int node1, int node2, double value){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    //if(elm_insert(htab, eid, NULL, node1, node2, NO_NODE, NO_NODE, value, 2)){
    //    log_error("Duplicated Voltage Source : %s in line %d",eid, (yylineno - 1));
    //    exit(EXIT_FAILURE);
    //}

    //new routine
    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, DC, 2);

    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[dc_V1] = value;

    if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_sine_v(char *sid, int node1, int node2, double offset, double amp, double freq, double delay, double d_factor, double phase){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }

    SRC_TAB *stab = create_src(sid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, SINE, 2);

    stab -> src_coefficient = (double *)calloc(6, sizeof(double));
    stab -> src_coefficient[sine_a] = d_factor;
    stab -> src_coefficient[sine_Fo] = freq;
    stab -> src_coefficient[sine_phi] = phase;
    stab -> src_coefficient[sine_Td] = delay;
    stab -> src_coefficient[sine_Va] = amp;
    stab -> src_coefficient[sine_Vo] = offset;
    
    if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_pulse_v(char *sid, int node1, int node2, double v_off, double v_on, double delay, double Tr, double Tf, double t_on, double t_period){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    SRC_TAB *stab = create_src(sid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, PULSE, 2);
    
    stab -> src_coefficient = (double *)calloc(7, sizeof(double));
    stab -> src_coefficient[pulse_Td] = delay;
    stab -> src_coefficient[pulse_Tf] = Tf;
    stab -> src_coefficient[pulse_To] = t_period; 
    stab -> src_coefficient[pulse_Tr] = Tr;
    stab -> src_coefficient[pulse_Tw] = t_on; 
    stab -> src_coefficient[pulse_V1] = v_on;
    stab -> src_coefficient[pulse_Vo] = v_off;

    if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_ramp_v(char *sid, int node1, int node2, double delay){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    SRC_TAB *stab = create_src(sid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, RAMP, 2);

    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[ramp_Td] = delay;
    
    if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_step_v(char *sid, int node1, int node2, double v_on, double delay){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    SRC_TAB *stab = create_src(sid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, STEP, 2);

    stab -> src_coefficient = (double *)calloc(2, sizeof(double));
    stab -> src_coefficient[step_Td] = delay;
    stab -> src_coefficient[step_V1] = v_on;

    if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_ac_v(char *sid, int node1, int node2, double amp, double phase){
    if(node1 == node2){
        log_error("Consistency Requirement ERROR! SHORTED VOLTAGE SOURCE : %s in Line %d", sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
    SRC_TAB *stab = create_src(sid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, FREQ_DOMAIN, AC, 2);

    stab -> src_coefficient = (double *)calloc(2, sizeof(double));
    stab -> src_coefficient[ac_amp] = amp;
    stab -> src_coefficient[ac_phi] = phase;

    if(src_insert(htab, stab)){
        log_error("Duplicated Voltage Source : %s in line %d",sid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_I(char *eid, int node1, int node2, double value, int group){
    //Consistency Requirement check FUTURE!
    //if(elm_insert(htab, eid, NULL, node1, node2, NO_NODE, NO_NODE, value, group)){
    //    log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
    //    exit(EXIT_FAILURE);
    //}

    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, DC, group);
    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[dc_V1] = value;
    if(src_insert(htab, stab)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_VCCS(char *eid, int node1, int node2, int node3, int node4, double value, int group){
    //if(elm_insert(htab, eid, NULL, node1, node2, node3, node4, value, group)){
    //    log_error("Duplicated VCCS : %s in line %d",eid, (yylineno - 1));
    //    exit(EXIT_FAILURE);
    //}
    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), search_node_by_num(htab, node3), search_node_by_num(htab, node4), TIME_DOMAIN, DEPENDENT, group);
    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[dep_value] = value;
    if(src_insert(htab, stab)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_VCVS(char *eid, int node1, int node2, int node3, int node4, double value, int group){
    //if(elm_insert(htab, eid, NULL, node1, node2, node3, node4, value, group)){
    //    log_error("Duplicated VCVS : %s in line %d",eid, (yylineno - 1));
    //    exit(EXIT_FAILURE);
    //}
    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), search_node_by_num(htab, node3), search_node_by_num(htab, node4), TIME_DOMAIN, DEPENDENT, group);
    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[dep_value] = value;
    if(src_insert(htab, stab)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_CCCS(char *eid, char *cvs, int node1, int node2, double value, int group){
    //if(elm_insert(htab, eid, cvs, node1, node2, NO_NODE, NO_NODE, value, group)){
    //    log_error("Duplicated CCCS : %s in line %d",eid, (yylineno - 1));
    //    exit(EXIT_FAILURE);
    //}
    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, DEPENDENT, group);
    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[dep_value] = value;

    stab -> cvs = (char *)malloc((strlen(cvs) + 1) * sizeof(char));
    if(stab -> cvs == NULL){
        log_fatal("cvs Allocation FAILD!");
        //safe exit
        exit(EXIT_FAILURE);
    }
    strcpy(stab -> cvs, cvs);

    if(src_insert(htab, stab)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
        exit(EXIT_FAILURE);
    }
}

void add_CCVS(char *eid, char *cvs, int node1, int node2, double value, int group){
    SRC_TAB *stab = create_src(eid, search_node_by_num(htab, node1), search_node_by_num(htab, node2), NULL, NULL, TIME_DOMAIN, DEPENDENT, group);
    stab -> src_coefficient = (double *)calloc(1, sizeof(double));
    stab -> src_coefficient[dep_value] = value;

    stab -> cvs = (char *)malloc((strlen(cvs) + 1) * sizeof(char));
    if(stab -> cvs == NULL){
        log_fatal("cvs Allocation FAILD!");
        //safe exit
        exit(EXIT_FAILURE);
    }
    strcpy(stab -> cvs, cvs);

    if(src_insert(htab, stab)){
        log_error("Duplicated Current Source : %s in line %d",eid, (yylineno - 1));
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