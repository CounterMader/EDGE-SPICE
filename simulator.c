#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "simulator.h"
#include "log.h"

void simulate(CKTcircuit *circuit, HASH_TAB *htab){
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        ELM_TAB *temp = htab -> e_table[i];
        while(temp){
            switch(temp ->key[0]){
            case 'R':
                log_trace("R detected");
                if(temp -> group == 2){
                    r_g2_stamp(circuit, temp);
                }
                else{
                    r_g1_stamp(circuit, temp);
                }
                break;
            case 'V':
                log_trace("V detected");
                v_stamp(circuit, temp);
                break;
            case 'I':
                log_trace("I detected");
                if(temp -> group == 2){
                    i_g2_stamp(circuit, temp);
                }
                else{
                    i_g1_stamp(circuit, temp);
                }
            default:
                break;
            }
            temp = temp -> next;
        }
    }
}
void r_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    if(element -> node1 == element -> node2){
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node1 == 0 && element -> node2 != 0){

        MNAstamp -> data[element -> node2 - 1][element -> node2 - 1] = 1/element -> value;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node2 == 0 && element -> node1 != 0){

        MNAstamp -> data[element -> node1 - 1][element -> node1 - 1] = 1/element -> value;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else{

        MNAstamp -> data[element -> node1 - 1][element -> node1 - 1] = 1/element -> value;
        MNAstamp -> data[element -> node2 - 1][element -> node2 - 1] = 1/element -> value;
        MNAstamp -> data[element -> node1 - 1][element -> node2 - 1] = -1/element -> value;
        MNAstamp -> data[element -> node2 - 1][element -> node1 - 1] = -1/element -> value;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
}

void r_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    element -> index_in_RHS = get_RHS_index(circuit);
    
    if(element -> node1 == element -> node2){
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node1 == 0 && element -> node2 != 0){

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node2 - 1] = -1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = -element -> value;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node2 == 0 && element -> node1 != 0){

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node1 - 1] = +1;
        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = -element -> value;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else{
        
        MNAstamp -> data[element -> index_in_RHS - 1][element -> node1 - 1] = +1;
        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> node2 - 1] = -1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = -element -> value;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    
    }
    
    
}

/*
                   I
        node1(+)------->node2(-)
*/
void v_stamp(CKTcircuit *circuit, ELM_TAB *element){
    ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);
    ES_mat *RHSstamp = ES_mat_new(circuit -> MNA_size, 1);

    element -> index_in_RHS = get_RHS_index(circuit);
    
    RHSstamp -> data[element -> index_in_RHS - 1][0] = element -> value;
    circuit -> RHSmat = ES_mat_add(circuit -> RHSmat, RHSstamp);
    ES_mat_free(RHSstamp);

    if(element -> node1 == 0 && element -> node2 != 0){

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node2 - 1] = -1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node2 == 0 && element -> node1 != 0){

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node1 - 1] = +1;
        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;
        

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else{

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node2 - 1] = -1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> node1 - 1] = +1;
        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
}

/*
                 I
    node1(+)----->-----node2(-)
*/
void i_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    ES_mat *RHSstamp = ES_mat_new(circuit -> MNA_size, 1);

    if(element -> node1 == element -> node2){
        ES_mat_free(RHSstamp);
        return;
    }
    else if(element -> node1 == 0 && element -> node2 != 0){

        RHSstamp -> data[element -> node2 - 1][0] = element -> value;

        circuit -> RHSmat = ES_mat_add(circuit -> RHSmat, RHSstamp);
        ES_mat_free(RHSstamp);
        return;
    }
    else if(element -> node2 == 0 && element -> node1 != 0){

        RHSstamp -> data[element -> node1 - 1][0] = -element -> value;
    
        circuit -> RHSmat = ES_mat_add(circuit -> RHSmat, RHSstamp);
        ES_mat_free(RHSstamp);
        return;
    }
    else{

        RHSstamp -> data[element -> node1 - 1][0] = -element -> value;
        RHSstamp -> data[element -> node2 - 1][0] = element -> value;

        circuit -> RHSmat = ES_mat_add(circuit -> RHSmat, RHSstamp);
        ES_mat_free(RHSstamp);
        return;
    }
    
}

void i_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);
    ES_mat *RHSstamp = ES_mat_new(circuit -> MNA_size, 1);

    element -> index_in_RHS = get_RHS_index(circuit);

    RHSstamp -> data[element -> index_in_RHS - 1][0] = element -> value;
    circuit -> RHSmat = ES_mat_add(circuit -> RHSmat, RHSstamp);
    ES_mat_free(RHSstamp);

    if(element -> node1 == element -> node2){
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node1 == 0 && element -> node2 != 0){

        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = 1;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node2 == 0 && element -> node1 != 0){

        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = 1;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else{

        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = 1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = 1;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }   
}