/*
    this file contains function to deal with circuit main structure;
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

    ELM_TAB *temp = NULL;
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        temp = htab -> e_table[i];
        while(temp){
            if(temp -> group == 2){
                size++;
            }
            temp = temp -> next;
        }
    }

    circuit -> MNA_size = size; 
}

int get_RHS_index(CKTcircuit *circuit){
    circuit -> RHS_free_pointer++;
    return circuit -> RHS_free_pointer;
}