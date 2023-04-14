/*
    circuit structure
*/

#include "ESmat.h"


#define DC_SYM 0
#define AC_SYM 1
#define TRAN_SYM 2

typedef struct _circuit_struct{
    ES_mat *MNAmat;             //Circuit MNA matrix
    ES_mat *RHSmat;             //Circuit RHS matrix
    ES_mat *RHSmat_prev;        //Circuit Previus RHS

    unsigned int MNA_size;
    int simulate_type;

    //Transient Analysis Parameters
    double Tstart;
    double Tstop;
    double Tstep;

    int is_linear;              //flag for networks linearity

}CKTcircuit;

CKTcircuit *makeckt();
void free_ckt(CKTcircuit *circuit);
void get_MNA_size(CKTcircuit *circuit, HASH_TAB *htab);