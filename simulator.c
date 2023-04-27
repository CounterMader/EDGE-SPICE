#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "simulator.h"
#include "log.h"
#include "stamps.h"

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
            case 'V':
                if(temp -> is_stamped == NOT_STAMPED){
                    log_trace("V detected");
                    v_stamp(circuit, temp);
                    temp -> is_stamped = STAMPED;
                }
                break;
            case 'I':
                log_trace("I detected");
                if(temp -> group == 2){
                    i_g2_stamp(circuit, temp);
                }
                else{
                    i_g1_stamp(circuit, temp);
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
            case 'G':
                log_trace("VCCS(G) detected");
                g_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'E':
                log_trace("VCVS(E) detected");
                e_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'F':
                log_trace("CCCS(F) detected");
                f_stamp(circuit, htab, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'H':
                log_trace("CCVS(H) detected");
                h_stamp(circuit, htab, temp);
                temp -> is_stamped = STAMPED;
                break;
            default:
                break;
            }
            temp = temp -> next;
        }
    }
    ES_mat_lup *lup = ES_mat_lup_solve(circuit -> MNAmat);
    ES_mat *x = ES_ls_solve(lup, circuit -> RHSmat);
    ES_mat_print(x, log);

    update_result(x, htab, 0);
    print_result(htab);
}


void simulate_TRAN(CKTcircuit *circuit, HASH_TAB *htab, FILE *log){
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
            case 'V':
                if(temp -> is_stamped == NOT_STAMPED){
                    log_trace("V detected");
                    v_stamp(circuit, temp);
                    temp -> is_stamped = STAMPED;
                }
                break;
            case 'I':
                log_trace("I detected");
                if(temp -> group == 2){
                    i_g2_stamp(circuit, temp);
                }
                else{
                    i_g1_stamp(circuit, temp);
                }
                temp -> is_stamped = STAMPED;
                break;
            case 'L':
                log_trace("L detected");
                l_tran_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'C':
                log_trace("C detected");
                c_g2_tran_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'G':
                log_trace("VCCS(G) detected");
                g_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'E':
                log_trace("VCVS(E) detected");
                e_stamp(circuit, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'F':
                log_trace("CCCS(F) detected");
                f_stamp(circuit, htab, temp);
                temp -> is_stamped = STAMPED;
                break;
            case 'H':
                log_trace("CCVS(H) detected");
                h_stamp(circuit, htab, temp);
                temp -> is_stamped = STAMPED;
                break;
            default:
                break;
            }
            temp = temp -> next;
        }
    }
    ES_mat_lup *lup = ES_mat_lup_solve(circuit -> MNAmat);
    ES_mat *x;

    for(int step = 1;step <= circuit -> step_num;step++){

        x = ES_ls_solve(lup, circuit -> RHSmat);
       
        update_result(x, htab, step - 1);
        
        for(int i = 0;i < htab -> e_size;i++){
            if(htab -> e_table[i] == NULL)
                continue;
            ELM_TAB *temp = htab -> e_table[i];
            while(temp){
                switch(temp ->key[0]){
                case 'V':
                    
                    break;
                case 'L':
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] = 0; 
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] += (-temp -> value / circuit -> Tstep) * temp -> current[step - 1];
                    break;
                case 'C':
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] = 0;
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] += (temp -> value / circuit -> Tstep) * get_element_voltage(htab, temp, step - 1);
                    break;
                default:
                    break;
                }
                temp = temp -> next;
            }
        }
        //fprintf(log,"after update:\n");
        //ES_mat_print(circuit -> RHSmat, log);
        ES_mat_free(x);
    }
}

void RHS_update_tran(CKTcircuit *circuit, HASH_TAB *htab, int step, FILE *log){
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
                continue;
            ELM_TAB *temp = htab -> e_table[i];
            while(temp){
                switch(temp ->key[0]){
                case 'V':
                    
                    break;
                case 'L':
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] = 0; 
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] += (-temp -> value / circuit -> Tstep) * temp -> current[step - 1];
                    break;
                case 'C':
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] = 0;
                    circuit -> RHSmat -> data[temp -> index_in_RHS - 1][0] += (temp -> value / circuit -> Tstep) * get_element_voltage(htab, temp, step - 1);
                    break;
                default:
                    break;
                }
                temp = temp -> next;
            }
        }
}

double get_element_voltage(HASH_TAB *htab, ELM_TAB *element, int step){

    double voltage = 0;

    char node1_buf[11];
    char node2_buf[11];
    sprintf(node1_buf, "%d", element -> node1);
    sprintf(node2_buf, "%d", element -> node2);

    if(element -> node1 != 0){
        NODE_TAB *node1 = search_node(htab, node1_buf);
        voltage += (node1 -> voltage[step]); 
    }
    if(element -> node2 != 0){
        NODE_TAB *node2 = search_node(htab, node2_buf);
        voltage += -(node2 -> voltage[step]);
    }

    return voltage;
}