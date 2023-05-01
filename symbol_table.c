#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "hash.h"

#include "symbol_table.h"
#include "circuit.h"
#include "source.h"

/*
    symbol table
        |__ size
        |__ numsyms
        |__ hash function
        |__ compare function
        |__ hash table
            |    |__ node symbol(BUCKET) 0
            |         |__ Entrie
            |    :
            |    :
            |    |__ node symbol(BUCKET) n
            |         |__ Entrie
            |
            |__ element symbol 0
                    |__ Entrie
            :
            :
            |__ element symbol n
                    |__ Entrie
*/


HASH_TAB *maketab(int NTsize,
                  int ETsize,
                  int STsize,
                  unsigned (*hash_function)(char*), 
                  int(*n_cmp_function)(NODE_TAB *, NODE_TAB*), 
                  int(*e_cmp_function)(ELM_TAB *, ELM_TAB*),
                  int(*s_cmp_function)(SRC_TAB *, SRC_TAB *)){
    HASH_TAB *tab = NULL;

    if(!(tab = (HASH_TAB*)malloc(sizeof(HASH_TAB)))){
        log_fatal("symbol table allocaion fault!");
        //safe exit
        exit(EXIT_FAILURE);
        return NULL;
    }

    if(!(tab -> n_table = (struct node_table**)calloc(NTsize ,sizeof(struct node_table*)))){
        log_fatal("node table allocaion fault!");
        return NULL;
    }
    for(int i = 0;i < NTsize;i++){
        tab -> n_table[i] = NULL;
    }

    if(!(tab -> e_table = (struct elm_table**)calloc(ETsize , sizeof(struct elm_table*)))){
        log_fatal("element table allocaion fault!");
        return NULL;
    }
    for(int i = 0;i < ETsize;i++){
        tab -> e_table[i] = NULL;
    }

    if(!(tab -> s_table = (struct src_table**)calloc(STsize , sizeof(struct src_table*)))){
        log_fatal("source table allocaion fault!");
        //safe exit
        return NULL;
    }
    for(int i = 0;i < STsize;i++){
        tab -> s_table[i] = NULL;
    }
    tab -> e_numsyms = 0;
    tab -> n_numsyms = 0;
    tab -> s_numsyms = 0;

    tab -> n_size = NTsize;
    tab -> e_size = ETsize;
    tab -> s_size = STsize;

    tab -> n_cmp = n_cmp_function;
    tab -> e_cmp = e_cmp_function;
    tab -> s_cmp = s_cmp_function;

    tab -> hash = hash_function;

    return tab;
}

NODE_TAB *create_node(char *key,int number){
    NODE_TAB *ntab = NULL;
    ntab = (NODE_TAB*)malloc(sizeof(NODE_TAB));

    ntab -> voltage =NULL;

    ntab -> number = number;

    ntab -> key = (char*)malloc(strlen(key) + 1);
    strcpy(ntab -> key,key);

    ntab -> next = NULL;
    ntab -> prev = NULL;

    return ntab;
}

ELM_TAB *create_element(char *eid, int node1, int node2, int node3, int node4, double value, int group){
    ELM_TAB *etab = NULL;
    etab = (ELM_TAB*)malloc(sizeof(ELM_TAB));

    etab -> key = (char*)malloc(strlen(eid) + 1);
    strcpy(etab -> key, eid);

    etab ->current = NULL;

    etab -> next = NULL;
    etab -> prev = NULL;

    etab -> node1 = node1;
    etab -> node2 = node2;
    etab -> node3 = node3;
    etab -> node4 = node4;
    etab -> value = value; 
    etab -> group = group;

    etab -> is_stamped = NOT_STAMPED;

    etab -> cvs = NULL;
    return etab;
}

void free_node(NODE_TAB *ntab){
    free(ntab -> key);
    free(ntab);
}

void free_element(ELM_TAB *etab){
    free(etab -> key);
    if(etab -> cvs != NULL){
        free(etab -> cvs);
    }
    free(etab);
}

void free_hash_table(HASH_TAB *tab){

    for (int i = 0; i < tab->n_size; i++){
        NODE_TAB *p = tab -> n_table[i];
        if(p != NULL){
            if(p -> voltage != NULL){
               free(p -> voltage);
            }
            free_node(p);
        }
    }
    
    for (int i = 0; i < tab->e_size; i++){
        ELM_TAB *p = tab -> e_table[i];
        if(p != NULL){
            if(p -> current != NULL){
                free(p -> current);
            }
            free_element(p);
        }
    }

    for (int i = 0; i < tab->s_size; i++){
        SRC_TAB *p = tab -> s_table[i];
        if(p != NULL){
            if(p -> current != NULL){
                free(p -> current);
            }
            free_src(p);
        }
    }

    free(tab -> n_table);
    free(tab -> e_table);
    free(tab -> s_table);   
    free(tab);
    log_trace("Symbol table free SUCCESS!");
}

int node_cmp(NODE_TAB *p, NODE_TAB*q){
    return strcmp(p -> key,q ->key);
}

int elm_cmp(ELM_TAB *p, ELM_TAB*q){
    return strcmp(p -> key, q -> key);
}

/*return 1 when symbol already exist in data base
  return 0 when inserting successfull*/
int elm_insert(HASH_TAB *tab, char *eid, char *cvs, int node1, int node2, int node3, int node4, double value, int group){
    ELM_TAB *elm = create_element(eid, node1, node2, node3, node4, value, group);
    
    if(cvs != NULL){
        elm -> cvs = malloc((strlen(cvs) + 1) * sizeof(char));
        strcpy(elm -> cvs, cvs);
    }
    unsigned int index = tab -> hash(eid) % tab -> e_size;
    
    if(tab -> e_table[index] == NULL){
        tab -> e_table[index] = elm;
        tab -> e_numsyms++;
        return 0;
    }
    ELM_TAB *temp = tab -> e_table[index];
    while(temp){
        if(!(tab -> e_cmp(temp,elm))){
            log_error("symbol already exist! : %s",elm -> key);
            free_element(elm);
            return 1;
        }
        if(temp -> next == NULL){
            temp -> next = elm;
            tab -> e_numsyms++;
            return 0;
        }
        
        temp = temp -> next; 
    }
}


/*return 1 when symbol already exist in data base
  return 0 when inserting successfull*/
int node_insert(HASH_TAB *tab, char *key, int data){
    NODE_TAB *node = create_node(key,data);
    
    unsigned int index = tab -> hash(key) % tab -> n_size;
    
    if(tab -> n_table[index] == NULL){
        tab -> n_table[index] = node;
        tab -> n_numsyms++;
        return 0;
    }
    NODE_TAB *temp = tab -> n_table[index];
    while(temp){
        if(!(tab -> n_cmp(temp,node))){
            log_error("symbol already exist! : %s",node -> key);
            free_node(node);
            return 1;
        }
        if(temp -> next == NULL){
            temp -> next = node;
            tab -> n_numsyms++;
            return 0;
        }
        
        temp = temp -> next; 
    }
}

/* If element found ,return its entrie
   Otherwise return NULL */
ELM_TAB *search_element(HASH_TAB *tab, char *key){
    unsigned int index = tab -> hash(key) % tab -> e_size;
    
    ELM_TAB *temp = tab -> e_table[index];

    while(temp){
        if(!(strcmp(temp -> key,key)))
            return temp;
        temp = temp -> next;
    }
    printf("there is no element with %s ID!\n",key);
    return NULL;
}

/* If node found ,return its entrie
   Otherwise return NULL */
NODE_TAB *search_node(HASH_TAB *tab, char *key){
    unsigned int index = tab -> hash(key) % tab -> n_size;
    
    NODE_TAB *temp = tab -> n_table[index];

    while(temp){
        if(!(strcmp(temp -> key,key)))
            return temp;
        temp = temp -> next;
    }
    printf("there is no node with %s ID!\n",key);
    return NULL;
}

/* If node found ,return its entrie
   Otherwise return NULL */
NODE_TAB *search_node_by_num(HASH_TAB *tab, int num){
    char key[11];
    sprintf(key, "%d", num);

    unsigned int index = tab -> hash(key) % tab -> n_size;
    
    NODE_TAB *temp = tab -> n_table[index];

    while(temp){
        if(!(strcmp(temp -> key,key)))
            return temp;
        temp = temp -> next;
    }
    printf("there is no node with %s ID!\n",key);
    return NULL;
}

/*
Check if node is already exist in symbol table
return 0 when exist
return 1 when not exist
*/
int node_exist(HASH_TAB *htab, char *nid){
    unsigned int index = htab -> hash(nid) % htab -> n_size;

    NODE_TAB *temp = htab -> n_table[index];

    while(temp != NULL){
        if(!(strcmp(temp -> key, nid))){
            return 0;
        }
        temp = temp -> next;
    }

    return 1;
}

void print_element_table(HASH_TAB *tab, FILE *fp){
    for(int i = 0;i < tab -> e_size;i++){
        if(tab -> e_table[i] == NULL)
            continue;
        ELM_TAB *temp = tab -> e_table[i];
        while(temp){
            fprintf(fp,"%d\teid = %s\tnode : %d -> %d\tvalue = %f\tg:%d",tab -> hash(temp -> key) % tab -> e_size,
                                                                       temp -> key, temp -> node1, temp ->node2,
                                                                       temp -> value, temp -> group);
            if(temp -> cvs == NULL){
                fprintf(fp,"\n");
            }
            else{
                fprintf(fp,", current sensor : %s\n", temp -> cvs);
            }
            temp = temp -> next;
        }
    }
    fprintf(fp, "Element number = %d\n", tab -> e_numsyms);
    fprintf(fp, "-------------------------\n");
}

void print_node_table(HASH_TAB *tab, FILE *fp){
    for(int i = 0;i < tab -> n_size;i++){
        if(tab -> n_table[i] == NULL)
            continue;
        NODE_TAB *temp = tab -> n_table[i];
        while(temp){
            fprintf(fp,"%d\tnid = %s\tnumber = %d\n",tab -> hash(temp -> key) % tab -> n_size, temp -> key, temp -> number);
            temp = temp -> next;
        }
    }
    fprintf(fp, "Node number = %d\n", tab -> n_numsyms);
    fprintf(fp, "-------------------------\n");
}

void node_voltage_initial(HASH_TAB *htab, int step_num){
    for(int i = 0;i < htab -> n_size;i++){
        if(htab -> n_table[i] == NULL)
            continue;
        NODE_TAB *temp = htab -> n_table[i];
        while(temp){
            temp -> voltage = (double*)calloc(step_num, sizeof(double)); 
            if(temp -> voltage == NULL){
                    //safe exit routibe
                    log_fatal("element current allocation faild!");
                    exit(EXIT_FAILURE);
                }
            temp = temp -> next;
        }
    }
}

void element_current_initial(HASH_TAB *htab, int step_num){
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> e_table[i] == NULL)
            continue;
        ELM_TAB *temp = htab -> e_table[i];
        while(temp){
            if(temp -> group == 2){
                temp -> current = (double*)calloc(step_num, sizeof(double));
                if(temp -> current == NULL){
                    //safe exit routibe
                    log_fatal("element current allocation faild!");
                    exit(EXIT_FAILURE);
                }
            }
            temp = temp -> next;
        }
    }
}
/*
        Source Table
*/

SRC_TAB *create_src(char *sid, NODE_TAB *node1, NODE_TAB *node2, NODE_TAB *node3, NODE_TAB *node4, int source_domain, int source_type, int group){
    SRC_TAB *stab = NULL;
    stab = (SRC_TAB*)malloc(sizeof(SRC_TAB));
    if(stab == NULL){
        log_fatal("Source Allocation Failed!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    stab -> sid = (char*)malloc((strlen(sid) + 1) * sizeof(char));
    strcpy(stab -> sid, sid);
    if(stab -> sid == NULL){
        log_fatal("Source ID Allocation Failed!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    stab -> node1 = node1;
    stab -> node2 = node2;
    stab -> node3 = node3;
    stab -> node4 = node4;

    stab -> src_type = source_type;
    stab -> src_domain = source_domain;
    stab -> group = group;

    stab -> current = NULL;
    stab -> value = NULL;
    stab -> cvs = NULL;

    stab -> ac_src = NULL;
    stab -> dc_src = NULL;
    stab -> ramp_src = NULL;
    stab -> step_src = NULL;
    stab -> sine_src = NULL;
    stab -> pulse_src = NULL;
    stab -> dep_src = NULL;

    stab -> is_stamped = NOT_STAMPED;

    return stab;
}

void free_src(SRC_TAB *stab){
    free(stab -> sid);
    free(stab -> current);
    free(stab -> value);
    if(stab -> cvs != NULL){
        free(stab -> cvs);
    }

    if(stab -> pulse_src != NULL){
        free(stab -> pulse_src);
    }
    else if(stab -> sine_src != NULL){
        free(stab -> sine_src);
    }
    else if(stab -> ramp_src != NULL){
        free(stab -> ramp_src);
    }
    else if(stab -> step_src != NULL){
        free(stab -> step_src);
    }
    else if(stab -> dc_src != NULL){
        free(stab -> dc_src);
    }
    else if(stab -> ac_src != NULL){
        free(stab -> ac_src);
    }
    else if(stab -> dep_src != NULL){
        free(stab -> dep_src);
    }
    free(stab);
}

int src_cmp(SRC_TAB *p, SRC_TAB*q){
    return strcmp(p -> sid, q -> sid);
}

/*return 1 when symbol already exist in data base
  return 0 when inserting successfull*/
int src_insert(HASH_TAB *htab, SRC_TAB *stab){
    
    unsigned int index = htab -> hash(stab -> sid) % htab -> s_size;
    
    if(htab -> s_table[index] == NULL){
        htab -> s_table[index] = stab;
        htab -> s_numsyms++;
        return 0;
    }
    SRC_TAB *temp = htab -> s_table[index];
    while(temp){
        if(!(htab -> s_cmp(temp,stab))){
            log_error("symbol already exist! : %s",stab -> sid);
            free_src(stab);
            return 1;
        }
        if(temp -> next == NULL){
            temp -> next = stab;
            htab -> s_numsyms++;
            return 0;
        }
        
        temp = temp -> next; 
    }
}

/* If source found ,return its entrie
   Otherwise return NULL */
SRC_TAB *search_src(HASH_TAB *htab, char *sid){
    unsigned int index = htab -> hash(sid) % htab -> s_size;
    
    SRC_TAB *temp = htab -> s_table[index];

    while(temp){
        if(!(strcmp(temp -> sid, sid))){
            return temp;
        }
        temp = temp -> next;
    }
    log_error("there is no source with %s ID!", sid);
    return NULL;
}

void print_src_table(HASH_TAB *htab, FILE *fp){
    for(int i = 0;i < htab -> s_size;i++){
        if(htab -> s_table[i] == NULL)
            continue;
        SRC_TAB *temp = htab -> s_table[i];
        while(temp){     
            switch(temp -> src_type){
            case SINE:
                if(temp -> sid[0] == 'V'){
                    fprintf(fp, "%d\tSine Voltage source:sid = %s, node:%d --> %d, offset:%f, phase:%f, freq:%f, Amp :%f, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> sine_src -> offset, temp -> sine_src -> phase,
                                                                                          temp -> sine_src -> freq, temp -> sine_src -> amplitude,
                                                                                          temp -> sine_src -> delay);
                }
                else{
                    fprintf(fp, "%d\tSine Current source:sid = %s, node:%d --> %d, offset:%f, phase:%f, freq:%f, Amp :%f, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> sine_src -> offset, temp -> sine_src -> phase,
                                                                                          temp -> sine_src -> freq, temp -> sine_src -> amplitude,
                                                                                          temp -> sine_src -> delay);
                }
                break;
            case PULSE:
                if(temp -> sid[0] == 'V'){
                    fprintf(fp, "%d\tPulse Voltage source:sid = %s, node:%d --> %d, Von:%f, Voff:%f, Ton:%f, Tperiod:%f, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> pulse_src -> v_on, temp -> pulse_src -> v_off,
                                                                                          temp -> pulse_src -> t_on, temp -> pulse_src -> t_period,
                                                                                          temp -> pulse_src -> delay);
                }
                else{
                    fprintf(fp, "%d\tPulse Current source:sid = %s, node:%d --> %d, Von:%f, Voff:%f, Ton:%f, Tperiod:%f, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> pulse_src -> v_on, temp -> pulse_src -> v_off,
                                                                                          temp -> pulse_src -> t_on, temp -> pulse_src -> t_period,
                                                                                          temp -> pulse_src -> delay);
                }
                break;
            case RAMP:
                if(temp -> sid[0] == 'V'){
                    fprintf(fp, "%d\tRamp Voltage source:sid = %s, node:%d --> %d, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> ramp_src -> delay);
                }
                else{
                    fprintf(fp, "%d\tRamp Currnet source:sid = %s, node:%d --> %d, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> ramp_src -> delay);
                }
                break;
            case STEP:
                if(temp -> sid[0] == 'V'){
                    fprintf(fp, "%d\tStep Voltage source:sid = %s, node:%d --> %d, Von:%f, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> step_src -> v_on, temp -> step_src -> delay);
                }
                else{
                    fprintf(fp, "%d\tStep Current source:sid = %s, node:%d --> %d, Von:%f, delay:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> step_src -> v_on, temp -> step_src -> delay);
                }
                break;
            case DC:
                if(temp -> sid[0] == 'V'){
                    fprintf(fp, "%d\tDC Voltage source:sid = %s, node:%d --> %d, Value:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> dc_src -> value);
                }
                else{
                    fprintf(fp, "%d\tDC Current source:sid = %s, node:%d --> %d, Value:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> dc_src -> value);
                }
                break;
            case AC:
                fprintf(fp, "%d\tAC source:sid = %s, node:%d --> %d, Amp:%f, phase:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                          temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                          temp -> ac_src -> amplitude, temp -> ac_src -> phase);
                break;
            case DEPENDENT:
                if(temp -> sid[0] == 'F'){
                    fprintf(fp, "%d\tCCCS:sid = %s, node:%d --> %d, Current sesnsor:%s, Value:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                        temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                        temp -> cvs, temp -> dep_src -> value);
                }
                else if(temp -> sid[0] == 'H'){
                    fprintf(fp, "%d\tCCVS:sid = %s, node:%d --> %d, Current sesnsor:%s, Value:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                        temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                        temp -> cvs, temp -> dep_src -> value);
                }
                else if(temp -> sid[0] == 'G'){
                    fprintf(fp, "%d\tVCCS:sid = %s, out node:%d --> %d, sense nodes:%d --> %d, Value:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                                            temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                                            temp -> node3 -> number, temp -> node4 -> number,
                                                                                                            temp -> dep_src -> value);
                }
                else if(temp -> sid[0] == 'E'){
                    fprintf(fp, "%d\tVCVS:sid = %s, out node:%d --> %d, sense nodes:%d --> %d, Value:%f\n", htab -> hash(temp -> sid) % htab -> s_size,
                                                                                                            temp -> sid, temp -> node1 -> number, temp -> node2 -> number,
                                                                                                            temp -> node3 -> number, temp -> node4 -> number,
                                                                                                            temp -> dep_src -> value);
                }
                break;
            default:
                break;
            }
            temp = temp -> next;
        }
    }
    fprintf(fp, "Source number = %d\n", htab -> s_numsyms);
    fprintf(fp, "-------------------------\n");
}

void src_current_initial(HASH_TAB *htab, int step_num){
    for(int i = 0;i < htab -> e_size;i++){
        if(htab -> s_table[i] == NULL)
            continue;
        SRC_TAB *temp = htab -> s_table[i];
        while(temp){
            if(temp -> group == 2){
                temp -> current = (double*)calloc(step_num, sizeof(double));
                if(temp -> current == NULL){
                    //safe exit routibe
                    log_fatal("element current allocation faild!");
                    exit(EXIT_FAILURE);
                }
            }
            temp = temp -> next;
        }
    }
}


