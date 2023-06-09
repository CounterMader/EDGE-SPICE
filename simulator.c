#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "symbol_table.h"
#include "circuit.h"
#include "simulator.h"
#include "log.h"
#include "stamps.h"
#include "source.h"

void simulate_DC(CKTcircuit *circuit, HASH_TAB *htab, FILE *log){
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
                temp -> is_stamped = STAMPED;
                break;
            case 'L':
                log_trace("L detected");
                l_dc_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'C':
                log_trace("C detected but NADIDAM!");
                temp -> is_stamped = STAMPED;
                break;
            default:
                break;
            }
            temp = temp -> next;
        }
    }

    for(int j = 0;j < htab -> s_size;j++){
        if(htab -> s_table[j] == NULL)
            continue;
        SRC_TAB *stemp = htab -> s_table[j];
        while(stemp != NULL){
            switch(stemp -> sid[0]){
            case 'V':
                if(stemp -> is_stamped == NOT_STAMPED){
                    log_trace("V detected");
                    v_stamp(circuit, stemp);
                    stemp -> is_stamped = STAMPED;
                }
                break;
            case 'I':
                log_trace("I detected");
                if(stemp -> group == 2){
                    i_g2_stamp(circuit, stemp);
                }
                else{
                    i_g1_stamp(circuit, stemp);
                }
                stemp -> is_stamped = STAMPED;
                break;
            case 'G':
                log_trace("VCCS(G) detected");
                g_stamp(circuit, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            case 'E':
                log_trace("VCVS(E) detected");
                e_stamp(circuit, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            case 'F':
                log_trace("CCCS(F) detected");
                f_stamp(circuit, htab, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            case 'H':
                log_trace("CCVS(H) detected");
                h_stamp(circuit, htab, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            default:
                break;
            }
            stemp = stemp -> next;
        }
    }
   
    ES_mat_lup *lup = ES_mat_lup_solve(circuit -> MNAmat);
    ES_mat *x = ES_ls_solve(lup, circuit -> RHSmat);

    update_result(x, htab, 0);
    print_result(htab);
}


void simulate_TRAN(CKTcircuit *circuit, HASH_TAB *htab, FILE *log){
    MNA_update_tran(circuit, htab, log);

    char fname[20];
    FILE *fp;

    if(isdigit(circuit -> out.id[0])){
        circuit -> out.index_in_RHS = search_node(htab, circuit -> out.id) -> number - 1;    
        sprintf(fname, "%s.dat",circuit -> out.id);
        fp = fopen(fname, "w");
    }
    else{
        if(circuit -> out.id[0] == 'R' || circuit -> out.id[0] == 'L' || circuit -> out.id[0] == 'C'){
            circuit -> out.index_in_RHS = search_element(htab, circuit -> out.id) -> index_in_RHS - 1;
            sprintf(fname, "%s.dat",circuit -> out.id);
            fp = fopen(fname, "w");
        }
        else{
            circuit -> out.index_in_RHS = search_src(htab, circuit -> out.id) -> index_in_RHS - 1;    
            sprintf(fname, "%s.dat",circuit -> out.id);
            fp = fopen(fname, "w");
        }
    }
    ES_mat_lup *lup = ES_mat_lup_solve(circuit -> MNAmat);

    //First Step
    RHS_update_tran(circuit, htab, 0, log);
    circuit -> RESmat = ES_ls_solve(lup, circuit -> RHSmat);

    for(int step = 1;step < circuit -> step_num;step++){ 
        RHS_update_tran(circuit, htab, step, log);
        circuit -> RESmat = ES_ls_solve(lup, circuit -> RHSmat);
        fprintf(fp,"%.10lf  %.10lf\n",circuit -> Tstep * step, circuit -> RESmat -> data[circuit -> out.index_in_RHS][0]);
        //update_result(circuit -> RESmat, htab, step);
    }
    fclose(fp);
}

void RHS_update_tran(CKTcircuit *circuit, HASH_TAB *htab, int step, FILE *log){
    //ES_mat_free(circuit -> RHSmat_prev);
    //circuit -> RHSmat_prev = circuit -> RHSmat;
    //circuit -> RHSmat = ES_mat_new(circuit -> MNA_size, 1);

    ES_mat_free(circuit -> RHSmat);
    circuit -> RHSmat = ES_mat_new(circuit -> MNA_size, 1);

    ES_mat_free(circuit -> RESmat_prev);
    circuit -> RESmat_prev = circuit -> RESmat;

    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL){
            continue;
        }
        ELM_TAB *etemp = htab -> e_table[i];
        while(etemp){
            switch(etemp -> key[0]){
                case 'L':
                    l_tran_RHS_stamp(circuit, etemp, step);
                    break;
                case 'C':
                    if(etemp -> group == 2){
                        c_g2_tran_RHS_stamp(circuit, htab, etemp, step);
                    }
                    break;
                default:
                    break;
            }
            etemp = etemp -> next;
        }
    }


    for(int j = 0;j < htab -> s_size;j++){
        if(htab -> s_table[j] == NULL){
            continue;
        }
        SRC_TAB *stemp = htab -> s_table[j];
        while(stemp){
            switch(stemp -> sid[0]){
                case 'V':
                    v_tran_RHS_stamp(circuit, stemp, step);
                    break;
                case 'I':
                    if(stemp -> group == 2){
                        i_g2_tran_RHS_stamp(circuit, stemp, step);
                    }
                    else{
                        i_g1_tran_RHS_stamp(circuit, stemp, step);
                    }
                    break;
                default:
                    break;
            }
            stemp = stemp -> next;
        }
    }
}

void MNA_update_tran(CKTcircuit *circuit, HASH_TAB *htab, FILE *log){
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL){
            continue;
        }
        ELM_TAB *etemp = htab -> e_table[i];
        while(etemp){
            switch(etemp -> key[0]){
                case 'R':
                    if(etemp -> group == 2){
                        r_g2_stamp(circuit, etemp);
                    }
                    else{
                        r_g1_stamp(circuit, etemp);
                    }
                    etemp -> is_stamped = STAMPED;
                    break;
                case 'L':
                    l_tran_MNA_stamp(circuit, etemp);
                    etemp -> is_stamped = STAMPED;
                    break;
                case 'C':
                    if(etemp -> group == 2){
                        c_g2_tran_MNA_stamp(circuit, etemp);
                    }
                    else{
                        c_g1_tran_MNA_stamp(circuit, etemp);
                    }
                    etemp -> is_stamped = STAMPED;
                    break;
                default:
                    break;
            }
            etemp = etemp -> next;
        }
    }

    for(int j = 0;j < htab -> s_size;j++){
        if(htab -> s_table[j] == NULL){
            continue;
        }
        SRC_TAB *stemp = htab -> s_table[j];
        while(stemp){
            switch(stemp -> sid[0]){
                case 'V':
                    if(stemp -> is_stamped == NOT_STAMPED){
                        v_tran_MNA_stamp(circuit, stemp);
                        stemp -> is_stamped = STAMPED;
                    }
                    break;
                case 'I':
                    if(stemp -> group == 2){
                        i_g2_tran_MNA_stamp(circuit, stemp);
                    }
                    stemp -> is_stamped = STAMPED;
                    break;
                case 'E':
                    e_stamp(circuit, stemp);
                    stemp -> is_stamped = STAMPED;
                    break;
                case 'F':
                    f_stamp(circuit, htab, stemp);
                    stemp -> is_stamped = STAMPED;
                    break;
                case 'G':
                    g_stamp(circuit, stemp);
                    stemp -> is_stamped = STAMPED;
                    break;
                case 'H':
                    h_stamp(circuit, htab,  stemp);
                    stemp -> is_stamped = STAMPED;
                    break;
                default:
                    break;
            }
            stemp = stemp -> next;
        }
    }

    log_trace("Transient MNA done!");
}

void simulate_AC(CKTcircuit *circuit, HASH_TAB *htab, FILE *log){
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        ELM_TAB *temp = htab -> e_table[i];
        while(temp){
            switch(temp ->key[0]){
            case 'R':
                log_trace("R detected");
                if(temp -> group == 2){
                    r_ac_g2_stamp(circuit, temp);
                }
                else{
                    r_ac_g1_stamp(circuit, temp);
                }
                temp -> is_stamped = STAMPED;
                break;
            case 'L':
                log_trace("L detected");
                if(temp -> group == 2){
                    l_ac_g2_stamp(circuit, temp);
                }
                temp -> is_stamped = STAMPED;
                break;
            case 'C':
                if(temp -> group == 1){
                    c_ac_g1_stamp(circuit, temp);
                }
                temp -> is_stamped = STAMPED;
                break;
            default:
                break;
            }
            temp = temp -> next;
        }
    }

    for(int j = 0;j < htab -> s_size;j++){
        if(htab -> s_table[j] == NULL)
            continue;
        SRC_TAB *stemp = htab -> s_table[j];
        while(stemp != NULL){
            switch(stemp -> sid[0]){
            case 'V':
                if(stemp -> is_stamped == NOT_STAMPED){
                    log_trace("V detected");
                    if(stemp -> src_type == AC){
                        v_ac_stamp(circuit, stemp);
                    }
                    else if(stemp -> src_type == DC && stemp -> src_coefficient[dc_V1] == 0){
                        v_stamp(circuit, stemp);
                    }
                    stemp -> is_stamped = STAMPED;
                }
                break;
            case 'I':
                log_trace("I detected");
                if(stemp -> group == 2){
                    i_ac_g2_stamp(circuit, stemp);
                }
                else{
                    i_ac_g1_stamp(circuit, stemp);
                }
                stemp -> is_stamped = STAMPED;
                break;
            case 'G':
                log_trace("VCCS(G) detected");
                g_stamp(circuit, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            case 'E':
                log_trace("VCVS(E) detected");
                e_stamp(circuit, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            case 'F':
                log_trace("CCCS(F) detected");
                f_stamp(circuit, htab, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            case 'H':
                log_trace("CCVS(H) detected");
                h_stamp(circuit, htab, stemp);
                stemp -> is_stamped = STAMPED;
                break;
            default:
                break;
            }
            stemp = stemp -> next;
        }
    }



}