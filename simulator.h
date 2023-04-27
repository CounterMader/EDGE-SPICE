void simulate_DC(CKTcircuit *circuit, HASH_TAB *htab, FILE *log);
void simulate_TRAN(CKTcircuit *circuit, HASH_TAB *htab, FILE *log);
double get_element_voltage(HASH_TAB *htab, ELM_TAB *element, int step);