#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "simulator.h"
#include "log.h"
#include "stamps.h"

void r_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    /*
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
    }*/
    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> node1 - 1][element -> node1 - 1] += 1/element -> value;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> node2 - 1][element -> node2 - 1] += 1/element -> value;
    }
    if(element -> node1 != 0 && element -> node2 != 0){
        circuit -> MNAmat -> data[element -> node1 - 1][element -> node2 - 1] += -1/element -> value;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> node1 - 1] += -1/element -> value;
    }
}

void r_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    /*
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
    
    }*/
    element -> index_in_RHS = get_RHS_index(circuit);

    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] += -element -> value;

    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += +1;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += +1;    
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
    
}

/*
                   I
        node1(+)------->node2(-)
*/
void v_stamp(CKTcircuit *circuit, ELM_TAB *element){
    /*
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
    }*/
    element -> index_in_RHS = get_RHS_index(circuit);

    circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += element -> value;

     if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += +1;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += +1;    
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
}

/*
                 I
    node1(+)----->-----node2(-)
*/
void i_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    /*
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
    }*/

    if(element -> node1 != 0){
        circuit -> RHSmat -> data[element -> node1 - 1][0] += -element -> value;    
    }
    if(element -> node2 != 0){
        circuit -> RHSmat -> data[element -> node2 - 1][0] += element -> value;
    }
}

void i_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    /*
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
    }*/

    element -> index_in_RHS = get_RHS_index(circuit);
       
    circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += element -> value;

    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += 1;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] += 1;
}

void l_dc_stamp(CKTcircuit *circuit, ELM_TAB *element){
    /*
    ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    element -> index_in_RHS = get_RHS_index(circuit);
    
    if(element -> node1 == element -> node2){
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node1 == 0 && element -> node2 != 0){

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node2 - 1] = -1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = 0;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else if(element -> node2 == 0 && element -> node1 != 0){

        MNAstamp -> data[element -> index_in_RHS - 1][element -> node1 - 1] = +1;
        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = 0;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    }
    else{
        
        MNAstamp -> data[element -> index_in_RHS - 1][element -> node1 - 1] = +1;
        MNAstamp -> data[element -> node1 - 1][element -> index_in_RHS - 1] = +1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> node2 - 1] = -1;
        MNAstamp -> data[element -> node2 - 1][element -> index_in_RHS - 1] = -1;
        MNAstamp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = 0;

        circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
        ES_mat_free(MNAstamp);
        return;
    
    }*/

    element -> index_in_RHS = get_RHS_index(circuit);
    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += +1;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += +1;    
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
    

}


/*
    ------- node3   |------- node1
                    |
    ------- node4   |------- node2
*/
void g_stamp(CKTcircuit *circuit, ELM_TAB *element){
    //ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    if(element -> node1 - 1 >= 0 && element -> node3 - 1 >= 0){
        circuit -> MNAmat -> data[element -> node1 - 1][element -> node3 - 1] += element -> value;
    }
    if(element -> node2 - 1 >= 0 && element -> node4 - 1 >= 0){
        circuit -> MNAmat -> data[element -> node2 - 1][element -> node4 - 1] += element -> value;
    }
    if(element -> node1 - 1 >= 0 && element -> node4 - 1 >= 0){
        circuit -> MNAmat -> data[element -> node1 - 1][element -> node4 - 1] += -element -> value;
    }
    if(element -> node2 - 1 >= 0 && element -> node1 - 1 >= 0){
        circuit -> MNAmat -> data[element -> node2 - 1][element -> node1 - 1] += -element -> value;
    }
    
    //circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
    //ES_mat_free(MNAstamp);
}

/*
    ------- node3   |------- node1
                    |
    ------- node4   |------- node2
*/
void e_stamp(CKTcircuit *circuit, ELM_TAB *element){
    //ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    element -> index_in_RHS = get_RHS_index(circuit);

    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += 1;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += 1;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
    if(element -> node3 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node3 - 1] += -element -> value;
    }
    if(element -> node4 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node4 - 1] += element -> value;
    }
    
    //circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
    //ES_mat_free(MNAstamp);
}

void f_stamp(CKTcircuit *circuit, HASH_TAB *htab, ELM_TAB *element){
    ELM_TAB *cvs = search_element(htab, element -> cvs);
    if(cvs -> is_stamped == NOT_STAMPED){
        v_stamp(circuit, cvs);
        cvs -> is_stamped = STAMPED;
    }

    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> node1 - 1][cvs -> index_in_RHS - 1] += element -> value;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> node2 - 1][cvs -> index_in_RHS - 1] += -element -> value;
    }
}

void h_stamp(CKTcircuit *circuit, HASH_TAB *htab, ELM_TAB *element){
    ELM_TAB *cvs = search_element(htab, element -> cvs);
    if(cvs -> is_stamped == NOT_STAMPED){
        v_stamp(circuit, cvs);
        cvs -> is_stamped = STAMPED;
    }

    element -> index_in_RHS = get_RHS_index(circuit);

    circuit -> MNAmat -> data[element -> index_in_RHS - 1][cvs -> index_in_RHS - 1] += -element -> value;
    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += 1;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += 1;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }

}

void c_g2_tran_stamp(CKTcircuit *circuit, ELM_TAB *element){

    element -> index_in_RHS = get_RHS_index(circuit);
    //RHS stamp
    
    circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += 0;              //(C/h)*v(t-h) or initial condition for next update

    //MNA stamp
    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] += -1;

    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += element -> value / circuit -> Tstep;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += 1;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -element -> value / circuit -> Tstep;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
    
}


void c_g1_tran_stamp(CKTcircuit *_circuit_struct, ELM_TAB *element){
    
}

void l_tran_stamp(CKTcircuit *circuit, ELM_TAB *element){

    element -> index_in_RHS = get_RHS_index(circuit);
    //RHS stamp
    
    circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += 0;              //(L/h)*i(t-h) or initial condition for next update

    //MNA stamp
    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] += -element -> value / circuit -> Tstep;

    if(element -> node1 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 - 1] += 1;
        circuit -> MNAmat -> data[element -> node1 - 1][element -> index_in_RHS - 1] += 1;
    }
    if(element -> node2 != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 - 1][element -> index_in_RHS - 1] += -1;
    }
}