#include <stdio.h>
#include <stdlib.h>
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
        htab = maketab(53, 127, 50, symtab_hash_pjw, node_cmp, elm_cmp, src_cmp);
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

        //MNA and RHS matrices initialization
        circuit -> MNAmat = ES_mat_new(circuit -> MNA_size, circuit -> MNA_size);
        circuit -> RHSmat = ES_mat_new(circuit -> MNA_size, 1);
        circuit -> RHSmat_prev = ES_mat_new(circuit -> MNA_size, 1);
    
        //simulate
        switch (circuit -> simulate_type){
        case DC_SYM:
            simulate_DC(circuit, htab, log);
            break;
        case TRAN_SYM:
            //update sources
            transient_source_update(circuit, htab);
            simulate_TRAN(circuit, htab, log);
            break;
        case AC_SYM:

            break;
        default:
            log_fatal("Undefined Type Simulator!");
            break;
        }
        
        ES_mat_print(circuit -> MNAmat, log);
        ES_mat_print(circuit -> RHSmat, log);
        ES_mat_print(circuit -> RHSmat_prev, log);
        
        /*
        FILE *out = fopen("out.dat","w");
        ELM_TAB *c = search_element(htab, "C1");
        for(int i = 1;i <= circuit -> step_num;i++){
            fprintf(out,"%.16lf  %.16lf\n",circuit -> Tstep * (i - 1) ,c -> current[i]);
        }
        */
       /*
        FILE *out = fopen("out.dat","w");
        SRC_TAB *c = search_src(htab, "V2");
        double time = 0;
        for(int i = 0;i < circuit -> step_num;i++,time += circuit -> Tstep){
            fprintf(out,"%.16lf  %.16lf\n",time ,c -> value[i]);
        }
        */
        //result print
        free_hash_table(htab);
        free_ckt(circuit);
        fclose(log);
        return 0;
   
    default:
        break;
    }
}