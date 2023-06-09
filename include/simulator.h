void simulate_DC(CKTcircuit *circuit, HASH_TAB *htab, FILE *log);
void simulate_TRAN(CKTcircuit *circuit, HASH_TAB *htab, FILE *log);
void simulate_AC(CKTcircuit *circuit, HASH_TAB *htab, FILE *log);
void RHS_update_tran(CKTcircuit *circuit, HASH_TAB *htab, int step, FILE *log);
void MNA_update_tran(CKTcircuit *circuit, HASH_TAB *htab, FILE *log);