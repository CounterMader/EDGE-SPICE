/*
    circuit structure
*/
#include "ESmat.h"

#define NULL_SYM 0
#define DC_SYM 1
#define AC_SYM 2
#define TRAN_SYM 3

typedef struct _simulate_output_s{
    char *id;
    int index_in_RHS;
}SIM_OUT;

typedef struct _circuit_struct{
    ES_mat *MNAmat;             //Circuit MNA matrix
    ES_mat *RHSmat;             //Circuit RHS matrix
    ES_mat *RHSmat_prev;        //Circuit Previus RHS
    ES_mat *RESmat;
    ES_mat *RESmat_prev;
    
    ES_mat_comp *MNAmat_comp;             //Circuit MNA matrix
    ES_mat_comp *RHSmat_comp;             //Circuit RHS matrix
    ES_mat_comp *RHSmat_prev_comp;        //Circuit Previus RHS
    ES_mat_comp *RESmat_comp;
    ES_mat_comp *RESmat_prev_comp;
    
    SIM_OUT out;
    unsigned int MNA_size;
    int simulate_type;

    //Transient Analysis Parameters
    double Tstart;
    double Tstop;
    double Tstep;

    int step_num;

    //AC Analysis Parameters
    double frequency;           //Frequency of intrest
    double omega;               //Angular velocity : 2 * PI * f

    int is_linear;              //flag for networks linearity

    int RHS_free_pointer;

}CKTcircuit;

CKTcircuit *makeckt();
void free_ckt(CKTcircuit *circuit);
void get_MNA_size(CKTcircuit *circuit, HASH_TAB *htab);
int get_RHS_index(CKTcircuit *circuit);
double get_element_voltage(HASH_TAB *htab, ELM_TAB *element, int step);
void update_result(ES_mat *x, HASH_TAB *htab, int step);
void print_result(HASH_TAB *htab);
