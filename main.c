#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <complex.h>
#include "symbol_table.h"
#include "circuit.h"
#include "parser.h"
#include "log.h"
#include "hash.h"
#include "defs.h"
#include "simulator.h"
#include "source.h"



/*
    Work Flow:
        1)  Initializing Simulator:
              -Initializing Symbol table
              -Initializing Circuit structure

        2)  Parsing netlist and adding elements to symbol table

        3)  Get MNA Matrix size and add it to Circuit structure

        4)  Initializing MNA and RHS Matrices with given size

        5)  Based on Analysis mode(ac, dc, Transient):
              -Allocate enough memory for each node voltage
              -Allocate enough memory for each Group2 Elemts current

        6)  Stamping Elements to MNA Matrix

        7)  Solve the Matrix

        8)  Update the voltages and currents in symbol table

        9)  Printing the Result to user given file

        10) Free every matrices and structures we have allocated
*/

int main(int argc, char **argv){
    switch (argc){
    case 1:
        printf("EDGE-SPICE v1.0\nAuther : Ali Esmaeily - University of Tabriz - Spring 2023\n"
               "Use Following Format : espice <netlist> <output>\n");
        return 0;
        break;
    case 2:
        //Log redirection
        FILE *log = fopen("log","w");
        log_add_fp(log, LOG_TRACE);
        log_set_level(LOG_ERROR);

        //symbol table and circuit structure initial
        htab = maketab(53, 127, 53, symtab_hash_pjw, node_cmp, elm_cmp, src_cmp);
        circuit = makeckt();
        log_trace("SPICE initialization SUCCESS!");

        //Parsing netlist
        parse(argv[1]);
        print_element_table(htab, log);
        print_node_table(htab, log);
        print_src_table(htab, log);

        //Set RHS pointer
        circuit -> RHS_free_pointer = htab -> n_numsyms - 1;        //Because of GND node

        //MNA size
        get_MNA_size(circuit, htab);
        log_trace("MNA matrix size is %d", circuit -> MNA_size);

        //simulate
        switch (circuit -> simulate_type){
            case DC_SYM:
                //MNA and RHS matrices initialization
                circuit -> MNAmat = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);
                circuit -> RHSmat = ES_mat_new(circuit -> MNA_size, 1);
                //circuit -> RHSmat_prev = ES_mat_new(circuit -> MNA_size, 1);
                //circuit -> RESmat = ES_mat_new(circuit -> MNA_size, 1);
                //circuit -> RESmat_prev = ES_mat_new(circuit -> MNA_size, 1);
                simulate_DC(circuit, htab, log);
                ES_mat_print(circuit -> MNAmat, log);
                ES_mat_print(circuit -> RHSmat, log);
                ES_mat_print(circuit -> RHSmat_prev, log);
                break;
            case TRAN_SYM:
                //update sources
                if(circuit -> out.id == NULL){
                    log_fatal("Output variable not defined! Simulate STOPED!");
                    exit(EXIT_FAILURE);
                }
                //MNA and RHS matrices initialization
                circuit -> MNAmat = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);
                circuit -> RHSmat = ES_mat_new(circuit -> MNA_size, 1);
                circuit -> RHSmat_prev = ES_mat_new(circuit -> MNA_size, 1);
                circuit -> RESmat = ES_mat_new(circuit -> MNA_size, 1);
                circuit -> RESmat_prev = ES_mat_new(circuit -> MNA_size, 1);
                transient_source_update(circuit, htab);
                simulate_TRAN(circuit, htab, log);
                ES_mat_print(circuit -> MNAmat, log);
                ES_mat_print(circuit -> RHSmat, log);
                ES_mat_print(circuit -> RHSmat_prev, log);
                break;
            case AC_SYM:
                circuit -> MNAmat_comp = ES_mat_comp_new(circuit -> MNA_size, circuit -> MNA_size);
                circuit -> RHSmat_comp = ES_mat_comp_new(circuit -> MNA_size, 1);
                //circuit -> RHSmat_prev_comp = ES_mat_comp_new(circuit -> MNA_size, 1);
                //circuit -> RESmat_comp = ES_mat_comp_new(circuit -> MNA_size, 1);
                //circuit -> RESmat_prev_comp = ES_mat_comp_new(circuit -> MNA_size, 1);
                simulate_AC(circuit, htab, log);
                ES_mat_comp_print(circuit -> MNAmat_comp, log);
                ES_mat_comp_print(circuit -> RHSmat_comp, log);
                ES_mat_comp_print(circuit -> RHSmat_prev_comp, log);
                break;
            default:
                log_fatal("Undefined Type Simulator!");
                break;
        }

        
        
        free_hash_table(htab);
        free_ckt(circuit);
        fclose(log);
        return 0;
   
    default:
        break;
    }
}