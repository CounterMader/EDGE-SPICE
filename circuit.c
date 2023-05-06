/*
*   this file contain function to deal with circuit main structure;
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "log.h"
#include "circuit.h"


CKTcircuit *makeckt(){
    CKTcircuit *circuit = NULL;

    if(!(circuit = (CKTcircuit*)calloc(1, sizeof(CKTcircuit)))){
        log_fatal("Circuit structure allocation FAILED!");
        exit(EXIT_FAILURE);
    }

    circuit -> MNA_size = 0;
    circuit -> simulate_type = NULL_SYM;
    
    return circuit;
}

void free_ckt(CKTcircuit *circuit){
    ES_mat_free(circuit -> MNAmat);
    ES_mat_free(circuit -> RHSmat);
    ES_mat_free(circuit -> RHSmat_prev);

    free(circuit);
    log_trace("Circuit structure free SUCCESS!");
}

void get_MNA_size(CKTcircuit *circuit, HASH_TAB *htab){
    unsigned int size = htab -> n_numsyms - 1;          //Number of nodes(minus GND node)

    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        ELM_TAB *temp = htab -> e_table[i];
        while(temp){
            if(temp -> group == 2){
                size++;
            }
            temp = temp -> next;
        }
    }

    for(int i = 0;i < htab -> s_size;i++){
        if(htab -> s_table[i] == NULL)
            continue;
        SRC_TAB *stemp = htab -> s_table[i];
        while(stemp){
            if(stemp -> group == 2){
                size++;
            }
            stemp = stemp -> next;
        }
    }

    circuit -> MNA_size = size; 
}

int get_RHS_index(CKTcircuit *circuit){
    circuit -> RHS_free_pointer++;
    return circuit -> RHS_free_pointer;
}

double get_element_voltage(HASH_TAB *htab, ELM_TAB *element, int step){

    double voltage = 0;

    if(element -> node1 -> number != 0){
        voltage += (element -> node1 -> voltage[step]); 
    }
    if(element -> node2 -> number != 0){
        voltage += -(element -> node2 -> voltage[step]);
    }

    return voltage;
}

void update_result(ES_mat *x, HASH_TAB *htab, int step){
    for(int i = 0;i < htab -> n_size;i++){
        if(htab -> n_table[i] == NULL)
            continue;
        NODE_TAB *node_temp = htab -> n_table[i];
        while(node_temp){
            if(node_temp -> number != 0){
                node_temp -> voltage[step] = x -> data[node_temp -> number - 1][0];
            }
            node_temp = node_temp -> next;
        }
    }

    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        ELM_TAB *elm_temp = htab -> e_table[i];
        while(elm_temp){
            if(elm_temp -> group == 2){
                elm_temp -> current[step] = x -> data[elm_temp -> index_in_RHS - 1][0];
            }
            elm_temp = elm_temp -> next;
        }
    }
}

void print_result(HASH_TAB *htab){
    printf("Simulation Completed!\n====================\n\n");
    
    for(int i = 1;i < htab -> n_numsyms;i++){
        char buf[11];
        sprintf(buf,"%d",i);
        NODE_TAB *node_temp = search_node(htab, buf);
        printf("V(%s)\t=\t%lf\n", node_temp -> key, node_temp -> voltage[0]);
    }

    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        ELM_TAB *elm_temp = htab -> e_table[i];
        while(elm_temp){
            if(elm_temp -> group == 2){
                printf("I(%s)\t=\t%lf\n", elm_temp -> key, elm_temp -> current[0]);
            }
            elm_temp = elm_temp -> next;
        }
    }

    printf("\n====================\n");
}