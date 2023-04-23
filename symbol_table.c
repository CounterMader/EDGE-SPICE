#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "hash.h"
#include "symbol_table.h"

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
                  unsigned (*hash_function)(char*), 
                  int(*n_cmp_function)(NODE_TAB *, NODE_TAB*), 
                  int(*e_cmp_function)(ELM_TAB *, ELM_TAB*)){
    HASH_TAB *tab = NULL;

    if(!(tab = (HASH_TAB*)malloc(sizeof(HASH_TAB)))){
        printf("symbol table allocaion fault!\n");
        return NULL;
    }

    if(!(tab -> n_table = (struct node_table**)calloc(NTsize ,sizeof(struct node_table*)))){
        printf("node table allocaion fault!\n");
        return NULL;
    }
    for(int i = 0;i < NTsize;i++){
        tab -> n_table[i] = NULL;
    }

    if(!(tab -> e_table = (struct elm_table**)calloc(ETsize , sizeof(struct elm_table*)))){
        printf("element table allocaion fault!\n");
        return NULL;
    }
    for(int i = 0;i < ETsize;i++){
        tab -> e_table[i] = NULL;
    }

    tab -> e_numsyms = 0;
    tab -> n_numsyms = 0;

    tab -> n_size = NTsize;
    tab -> e_size = ETsize;

    tab -> n_cmp = n_cmp_function;
    tab -> e_cmp = e_cmp_function;

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
            free(p);
        }
    }
    
    for (int i = 0; i < tab->e_size; i++){
        ELM_TAB *p = tab -> e_table[i];
        if(p != NULL){
            if(p -> current != NULL){
                free(p -> current);
            }
            free(p);
        }
    }

    free(tab -> n_table);
    free(tab -> e_table);   
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
    /*if(current_elm -> next == NULL){
            if(!(tab -> e_cmp(current_elm,elm))){
            log_error("symbol already exist! : %s",elm -> key);
            free_element(elm);
            return -1;
        }
    }
    while (current_elm -> next != NULL){
         if(!(tab -> e_cmp(current_elm,elm))){
            log_error("symbol already exist! : %s",elm -> key);
            free_element(elm);
            return -1;
        }
        current_elm = current_elm -> next;
    }
    current_elm -> next = elm;
    tab -> e_numsyms++;*/
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

    /*else{
        NODE_TAB *current_node = tab -> n_table[index];
        if(current_node -> next == NULL){
            if(!(tab -> n_cmp(current_node,node))){
                printf("symbol already exist! : %s\n",node -> key);
                free_node(node);
                return -1;
            }
        }
        while (current_node -> next != NULL){
            if(!(tab -> n_cmp(current_node,node))){
                printf("symbol already exist! : %s\n",node -> key);
                free_node(node);
                return -1;
            }
            current_node = current_node -> next;
        }
        current_node -> next = node;
    }
    tab -> n_numsyms++;
    return 0;*/
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