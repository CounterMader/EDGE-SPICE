unsigned int symtab_hash_pjw(char *name);
unsigned int symtab_hash_add(char *name);
#define NBITS_IN_UNSIGNED       (8 * sizeof(unsigned int))
#define SEVENTY_FIVE_PERCENT    ((int)(NBITS_IN_UNSIGNED * 0.75))
#define TWELVE_PERCENT          ((int)(NBITS_IN_UNSIGNED * 0.125))
#define HIGH_BITS               (~((unsigned)(~0) >> TWELVE_PERCENT))