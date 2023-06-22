#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "symbol_table.h"
#include "circuit.h"
#include "simulator.h"
#include "log.h"
#include "stamps.h"
#include "source.h"

void r_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    if(element -> node1 -> number != 0){
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> node1 -> number - 1] += 1/element -> value;
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> node2 -> number - 1] += 1/element -> value;
    }
    if(element -> node1 -> number != 0 && element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> node2 -> number - 1] += -1/element -> value;
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> node1 -> number - 1] += -1/element -> value;
    }
}

void r_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    element -> index_in_RHS = get_RHS_index(circuit);

    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] += -element -> value;

    if(element -> node1 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 -> number - 1] += +1;
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> index_in_RHS - 1] += +1;    
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 -> number - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> index_in_RHS - 1] += -1;
    }
    
}

/*
                   I
        node1(+)------->node2(-)
*/
void v_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);

    circuit -> RHSmat -> data[source -> index_in_RHS - 1][0] += source -> src_coefficient[dc_V1];

    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1] += +1;
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1] += +1;    
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1] += -1;
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1] += -1;
    }

}

void v_tran_MNA_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);
    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1] += +1;
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1] += +1;    
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1] += -1;
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1] += -1;
    }
}

void v_tran_RHS_stamp(CKTcircuit *circuit, SRC_TAB *source, int step){
    circuit -> RHSmat -> data[source -> index_in_RHS - 1][0] += source -> value[step];
}
/*
                 I
    node1(+)----->-----node2(-)
*/
void i_g1_stamp(CKTcircuit *circuit, SRC_TAB *source){
    if(source -> node1 -> number != 0){
        circuit -> RHSmat -> data[source -> node1 -> number - 1][0] += -source -> src_coefficient[dc_V1];    
    }
    if(source -> node2 -> number != 0){
        circuit -> RHSmat -> data[source -> node2 -> number - 1][0] += source -> src_coefficient[dc_V1];
    }

}

void i_g1_tran_RHS_stamp(CKTcircuit *circuit, SRC_TAB *source, int step){
    if(source -> node1 -> number != 0){
        circuit -> RHSmat -> data[source -> node1 -> number - 1][0] += -source -> value[step];    
    }
    if(source -> node2 -> number != 0){
        circuit -> RHSmat -> data[source -> node2 -> number - 1][0] += source -> value[step];
    }
}

void i_g2_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);
       
    circuit -> RHSmat -> data[source -> index_in_RHS - 1][0] += source -> src_coefficient[dc_V1];

    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1] += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1] += -1;
    }
    circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> index_in_RHS - 1] += 1;
    
}
void i_g2_tran_MNA_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);
    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1] += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1] += -1;
    }
    circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> index_in_RHS - 1] += 1;
}

void i_g2_tran_RHS_stamp(CKTcircuit *circuit, SRC_TAB *source, int step){
    circuit -> RHSmat -> data[source -> index_in_RHS - 1][0] += source -> value[step];
}

void l_dc_stamp(CKTcircuit *circuit, ELM_TAB *element){
    element -> index_in_RHS = get_RHS_index(circuit);
    if(element -> node1 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 -> number - 1] += +1;
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> index_in_RHS - 1] += +1;    
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 -> number - 1] += -1;
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> index_in_RHS - 1] += -1;
    }
    

}


/*
    ------- node3   |------- node1
                    |
    ------- node4   |------- node2
*/
void g_stamp(CKTcircuit *circuit, SRC_TAB *source){
    //ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    if(source -> node1 -> number - 1 >= 0 && source -> node3 -> number - 1 >= 0){
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> node3 -> number - 1] += source -> src_coefficient[dep_value];
    }
    if(source -> node2 -> number - 1 >= 0 && source -> node4 -> number - 1 >= 0){
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> node4 -> number - 1] += source -> src_coefficient[dep_value];
    }
    if(source -> node1 -> number - 1 >= 0 && source -> node4 -> number - 1 >= 0){
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> node4 -> number - 1] += -source -> src_coefficient[dep_value];
    }
    if(source -> node2 -> number - 1 >= 0 && source -> node1 -> number - 1 >= 0){
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> node1 -> number - 1] += -source -> src_coefficient[dep_value];
    }
    
    //circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
    //ES_mat_free(MNAstamp);
}

/*
    ------- node3   |------- node1
                    |
    ------- node4   |------- node2
*/
void e_stamp(CKTcircuit *circuit, SRC_TAB *source){
    //ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    source -> index_in_RHS = get_RHS_index(circuit);

    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1] += 1;
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1] += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1] += -1;
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1] += -1;
    }
    if(source -> node3 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node3 -> number - 1] += -source -> src_coefficient[dep_value];
    }
    if(source -> node4 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node4 -> number - 1] += source -> src_coefficient[dep_value];
    }
    
    //circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
    //ES_mat_free(MNAstamp);
}

void f_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source){
    SRC_TAB *cvs = search_src(htab, source -> cvs);
    if(cvs -> is_stamped == NOT_STAMPED){
        v_stamp(circuit, cvs);
        cvs -> is_stamped = STAMPED;
    }

    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> node1 -> number - 1][cvs -> index_in_RHS - 1] += source -> src_coefficient[dep_value];
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> node2 -> number - 1][cvs -> index_in_RHS - 1] += -source -> src_coefficient[dep_value];
    }
}

void h_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source){
    SRC_TAB *cvs = search_src(htab, source -> cvs);
    if(cvs -> is_stamped == NOT_STAMPED){
        v_stamp(circuit, cvs);
        cvs -> is_stamped = STAMPED;
    }

    source -> index_in_RHS = get_RHS_index(circuit);

    circuit -> MNAmat -> data[source -> index_in_RHS - 1][cvs -> index_in_RHS - 1] += -source -> src_coefficient[dep_value];
    if(source -> node1 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1] += 1;
        circuit -> MNAmat -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1] += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1] += -1;
        circuit -> MNAmat -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1] += -1;
    }

}
void c_g1_tran_MNA_stamp(CKTcircuit *circuit, ELM_TAB *element){
    
    if(element -> node1 -> number != 0){
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> node1 -> number - 1] += element -> value/circuit -> Tstep;
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> node2 -> number - 1] += element -> value/circuit -> Tstep;
    }
    if(element -> node1 -> number != 0 && element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> node2 -> number - 1] += -element -> value/circuit -> Tstep;
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> node1 -> number - 1] += -element -> value/circuit -> Tstep;
    }
}

void c_g1_tran_RHS_stamp(CKTcircuit *circuit, HASH_TAB *htab, ELM_TAB *element, int step){
    if(step == 0){      //Initial state
        circuit -> RHSmat -> data[element -> node1 -> number - 1][0] += 0;      //Initial Condition
        circuit -> RHSmat -> data[element -> node2 -> number - 1][0] += 0;
    }
    else{
        circuit -> RHSmat -> data[element -> node1 -> number - 1][0] +=  (element -> value/circuit -> Tstep) *  get_element_voltage(htab, element, step - 1);
        circuit -> RHSmat -> data[element -> node2 -> number - 1][0] += -(element -> value/circuit -> Tstep) *  get_element_voltage(htab, element, step - 1);
    }
    
}

void c_g2_tran_MNA_stamp(CKTcircuit *circuit, ELM_TAB *element){
    element -> index_in_RHS = get_RHS_index(circuit);
    //RHS Initial set
    //circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += 0;                 //(c/h)*vpv(previous voltage or Initial voltage)
    if(element -> ic != NULL){
        circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += -(element -> value / circuit -> Tstep) * element -> ic[0];             //-(L/h)*ipv(previous cuurent or initial current)
    }
    //MNA stamp
    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = -1;

    if(element -> node1 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 -> number - 1] = element -> value / circuit -> Tstep;
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> index_in_RHS - 1] = 1;
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 -> number - 1] = -element -> value / circuit -> Tstep;
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> index_in_RHS - 1] = -1;
    }
    
}

void c_g2_tran_RHS_stamp(CKTcircuit *circuit, HASH_TAB *htab, ELM_TAB *element, int step){
    double p_voltage = 0;
    if(element -> node1 -> number != 0){
        p_voltage += circuit -> RESmat_prev -> data[element -> node1 -> number - 1][0]; 
    }
    if(element -> node2 -> number != 0){
        p_voltage -= circuit -> RESmat_prev -> data[element -> node2 -> number - 1][0];
    }
    circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += (element -> value/circuit -> Tstep) *  p_voltage;
}


void l_tran_MNA_stamp(CKTcircuit *circuit, ELM_TAB *element){

    element -> index_in_RHS = get_RHS_index(circuit);
    //RHS Initial set
    if(element -> ic != NULL){
        circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] = -(element -> value / circuit -> Tstep) * element -> ic[0];             //-(L/h)*ipv(previous cuurent or initial current)
    }
    
    //MNA stamp
    circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1] = -element -> value / circuit -> Tstep;

    if(element -> node1 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node1 -> number - 1] = 1;
        circuit -> MNAmat -> data[element -> node1 -> number - 1][element -> index_in_RHS - 1] = 1;
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat -> data[element -> index_in_RHS - 1][element -> node2 -> number - 1] = -1;
        circuit -> MNAmat -> data[element -> node2 -> number - 1][element -> index_in_RHS - 1] = -1;
    }
}

void l_tran_RHS_stamp(CKTcircuit *circuit, ELM_TAB *element, int step){
    circuit -> RHSmat -> data[element -> index_in_RHS - 1][0] += -(element -> value / circuit -> Tstep) * circuit -> RESmat_prev -> data[element -> index_in_RHS - 1][0];
}


/*
    AC Stamps
*/


void r_ac_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    if(element -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> node1 -> number - 1][element -> node1 -> number - 1].re += (1/element -> value);
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> node2 -> number - 1][element -> node2 -> number - 1].re += (1/element -> value);
    }
    if(element -> node1 -> number != 0 && element -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> node1 -> number - 1][element -> node2 -> number - 1].re += (-1/element -> value);
        circuit -> MNAmat_comp -> data[element -> node2 -> number - 1][element -> node1 -> number - 1].re += (-1/element -> value);
    }
}

void r_ac_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    element -> index_in_RHS = get_RHS_index(circuit);

    circuit -> MNAmat_comp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1].re += -element -> value;

    if(element -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> index_in_RHS - 1][element -> node1 -> number - 1].re += +1;
        circuit -> MNAmat_comp -> data[element -> node1 -> number - 1][element -> index_in_RHS - 1].re += +1;    
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> index_in_RHS - 1][element -> node2 -> number - 1].re += -1;
        circuit -> MNAmat_comp -> data[element -> node2 -> number - 1][element -> index_in_RHS - 1].re += -1;
    }
    
}

void c_ac_g1_stamp(CKTcircuit *circuit, ELM_TAB *element){
    double value = log10(circuit -> omega) + log10(element -> value);
    double val = pow(10,value);
    if(element -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> node1 -> number - 1][element -> node1 -> number - 1].im += val;
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> node2 -> number - 1][element -> node2 -> number - 1].im += val;
    }
    if(element -> node1 -> number != 0 && element -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> node1 -> number - 1][element -> node2 -> number - 1].im += -val;
        circuit -> MNAmat_comp -> data[element -> node2 -> number - 1][element -> node1 -> number - 1].im += -val;
    }
}

void l_ac_g2_stamp(CKTcircuit *circuit, ELM_TAB *element){
    element -> index_in_RHS = get_RHS_index(circuit);
    //MNA stamp
    double value = log10(circuit -> omega) + log10(element -> value);
    double val = pow(10,value);
    circuit -> MNAmat_comp -> data[element -> index_in_RHS - 1][element -> index_in_RHS - 1].im += -val;
    if(element -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> index_in_RHS - 1][element -> node1 -> number - 1].re += 1;
        circuit -> MNAmat_comp -> data[element -> node1 -> number - 1][element -> index_in_RHS - 1].re += 1;
    }
    if(element -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[element -> index_in_RHS - 1][element -> node2 -> number - 1].re += -1;
        circuit -> MNAmat_comp -> data[element -> node2 -> number - 1][element -> index_in_RHS - 1].re += -1;
    }
}

void v_ac_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);

    double radians = source -> src_coefficient[ac_phi] * PI/ 180.0;

    circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].re += source -> src_coefficient[ac_amp] * cos(radians);
    circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].im += source -> src_coefficient[ac_amp] * sin(radians);
    printf("%f %f\n",circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].re,circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].im);
    if(source -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1].re += +1;
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1].re += +1;    
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1].re += -1;
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1].re += -1;
    }

}


void v_0_ac_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);

    circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].re += 0;

    if(source -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1].re += +1;
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1].re += +1;    
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1].re += -1;
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1].re += -1;
    }

}


void i_ac_g1_stamp(CKTcircuit *circuit, SRC_TAB *source){
    double radians = source -> src_coefficient[ac_phi] * PI/ 180.0;
    if(source -> node1 -> number != 0){
        circuit -> RHSmat_comp -> data[source -> node1 -> number - 1][0].re += -source -> src_coefficient[ac_amp] * cos(radians);    
        circuit -> RHSmat_comp -> data[source -> node1 -> number - 1][0].im += -source -> src_coefficient[ac_amp] * sin(radians);
    }
    if(source -> node2 -> number != 0){
        circuit -> RHSmat_comp -> data[source -> node2 -> number - 1][0].re += -source -> src_coefficient[ac_amp] * cos(radians);    
        circuit -> RHSmat_comp -> data[source -> node2 -> number - 1][0].im += -source -> src_coefficient[ac_amp] * sin(radians);
    }

}

void i_ac_g2_stamp(CKTcircuit *circuit, SRC_TAB *source){
    source -> index_in_RHS = get_RHS_index(circuit);
    double radians = source -> src_coefficient[ac_phi] * PI/ 180.0;   
    circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].re += source -> src_coefficient[ac_amp] * cos(radians);
    circuit -> RHSmat_comp -> data[source -> index_in_RHS - 1][0].im += source -> src_coefficient[ac_amp] * sin(radians);
    if(source -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1].re += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1].re += -1;
    }
    circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> index_in_RHS - 1].re += 1;
    
}

/*
    AC Dependent Sources
*/

/*
    ------- node3   |------- node1
                    |
    ------- node4   |------- node2
*/
void g_ac_stamp(CKTcircuit *circuit, SRC_TAB *source){
    //ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    if(source -> node1 -> number - 1 >= 0 && source -> node3 -> number - 1 >= 0){
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> node3 -> number - 1].re += source -> src_coefficient[dep_value];
    }
    if(source -> node2 -> number - 1 >= 0 && source -> node4 -> number - 1 >= 0){
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> node4 -> number - 1].re += source -> src_coefficient[dep_value];
    }
    if(source -> node1 -> number - 1 >= 0 && source -> node4 -> number - 1 >= 0){
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> node4 -> number - 1].re += -source -> src_coefficient[dep_value];
    }
    if(source -> node2 -> number - 1 >= 0 && source -> node1 -> number - 1 >= 0){
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> node1 -> number - 1].re += -source -> src_coefficient[dep_value];
    }
    
    //circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
    //ES_mat_free(MNAstamp);
}

/*
    ------- node3   |------- node1
                    |
    ------- node4   |------- node2
*/
void e_ac_stamp(CKTcircuit *circuit, SRC_TAB *source){
    //ES_mat *MNAstamp = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);

    source -> index_in_RHS = get_RHS_index(circuit);

    if(source -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1].re += 1;
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1].re += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1].re += -1;
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1].re += -1;
    }
    if(source -> node3 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node3 -> number - 1].re += -source -> src_coefficient[dep_value];
    }
    if(source -> node4 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node4 -> number - 1].re += source -> src_coefficient[dep_value];
    }
    
    //circuit -> MNAmat = ES_mat_add(circuit -> MNAmat, MNAstamp);
    //ES_mat_free(MNAstamp);
}

void f_ac_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source){
    SRC_TAB *cvs = search_src(htab, source -> cvs);
    if(cvs -> is_stamped == NOT_STAMPED){
        if(cvs -> src_type == AC){
            v_ac_stamp(circuit, cvs);
        }
        else if(cvs -> src_type == DC && cvs -> src_coefficient[dc_V1] == 0){
            v_0_ac_stamp(circuit, cvs);
        }
        cvs -> is_stamped = STAMPED;
    }

    if(source -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][cvs -> index_in_RHS - 1].re += source -> src_coefficient[dep_value];
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][cvs -> index_in_RHS - 1].re += -source -> src_coefficient[dep_value];
    }
}

void h_ac_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source){
    SRC_TAB *cvs = search_src(htab, source -> cvs);
    if(cvs -> is_stamped == NOT_STAMPED){
        if(cvs -> src_type == AC){
            v_ac_stamp(circuit, cvs);
        }
        else if(cvs -> src_type == DC && cvs -> src_coefficient[dc_V1] == 0){
            v_0_ac_stamp(circuit, cvs);
        }
        cvs -> is_stamped = STAMPED;
    }

    source -> index_in_RHS = get_RHS_index(circuit);

    circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][cvs -> index_in_RHS - 1].re += -source -> src_coefficient[dep_value];
    if(source -> node1 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node1 -> number - 1].re += 1;
        circuit -> MNAmat_comp -> data[source -> node1 -> number - 1][source -> index_in_RHS - 1].re += 1;
    }
    if(source -> node2 -> number != 0){
        circuit -> MNAmat_comp -> data[source -> index_in_RHS - 1][source -> node2 -> number - 1].re += -1;
        circuit -> MNAmat_comp -> data[source -> node2 -> number - 1][source -> index_in_RHS - 1].re += -1;
    }

}