#define NO_NODE -1
#define STAMPED 1
#define NOT_STAMPED 0

//Entries of DB
typedef struct node_table {
    struct node_table *next;
    struct node_table **prev;
    char *key;
    int number;
    double *voltage;
}NODE_TAB;

typedef struct elm_table {
    struct elm_table *next;
    struct elm_table **prev;
    char *key;
    /*
    NODE_TAB *node1;
    NODE_TAB *node2;
    */
    int index_in_RHS;

    int node1;
    int node2;
    int node3;
    int node4;
    int group;

    double value;
    double *current;

    int is_stamped;
    char *cvs;             //Corresponding voltage source for current controled sources
}ELM_TAB;

typedef struct _hash_table{
    int n_size;           //Size of node hash table
    int e_size;           //Size of element hash table
    int n_numsyms;        //Number of node symbols(statistical)
    int e_numsyms;        //Number of element symbols(statistical)
    unsigned int (*hash)(char*);
    int (*n_cmp)(NODE_TAB *, NODE_TAB*);
    int (*e_cmp)(ELM_TAB *, ELM_TAB*);
    ELM_TAB **e_table;
    NODE_TAB **n_table;
}HASH_TAB;

HASH_TAB *maketab(int NTsize, int ETsize,
                  unsigned (*hash_function)(char*), 
                  int(*n_cmp_function)(NODE_TAB *, NODE_TAB*), 
                  int(*e_cmp_function)(ELM_TAB *, ELM_TAB*));

NODE_TAB *create_node(char *key,int data);
ELM_TAB *create_element(char *eid, int node1, int node2, int node3, int node4, double value, int group);
void free_node(NODE_TAB *ntab);
void free_element(ELM_TAB *etab);
void free_hash_table(HASH_TAB *tab);
int node_cmp(NODE_TAB *p, NODE_TAB *q);
int elm_cmp(ELM_TAB *p, ELM_TAB *q);
int elm_insert(HASH_TAB *tab, char *eid, char *cvs, int node1, int node2, int node3, int node4, double value, int group);
int node_insert(HASH_TAB *tab, char *key, int number);
ELM_TAB *search_element(HASH_TAB *tab, char *key);
NODE_TAB *search_node(HASH_TAB *tab, char *key);
int node_exist(HASH_TAB *htab, char *nid);
void print_element_table(HASH_TAB *tab, FILE *fp);
void print_node_table(HASH_TAB *tab, FILE *fp);
void element_current_initial(HASH_TAB *htab, int step_num);
void node_voltage_initial(HASH_TAB *htab, int step_num);