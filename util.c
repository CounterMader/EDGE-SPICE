#include <stdio.h>
#include <stdlib.h>


void safe_exit(){
    free_hash_table(htab);
    free_ckt(circuit);
    fclose(log);
    exit(EXIT_FAILURE);
}