#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "log.h"

unsigned int symtab_hash_add(char *name){
    unsigned int hash_value = 0;

    while(*name != '\0'){
        hash_value += (unsigned)*name;
        name++;
    }
    return hash_value;
}


unsigned int symtab_hash_pjw(char *name){
    unsigned int hash_value = 0;
    unsigned int g;

    while(*name != '\0'){
        hash_value = (hash_value << TWELVE_PERCENT) + *name;

        if(g = hash_value & HIGH_BITS)
            hash_value = (hash_value ^ (g >> SEVENTY_FIVE_PERCENT)) & ~HIGH_BITS;
        name++;
    }
    return hash_value;
}