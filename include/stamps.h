void r_g1_stamp(CKTcircuit *circuit, ELM_TAB *element);
void r_g2_stamp(CKTcircuit *circuit, ELM_TAB *element);
void v_stamp(CKTcircuit *circuit, SRC_TAB *source);
void i_g1_stamp(CKTcircuit *circuit, SRC_TAB *source);
void i_g2_stamp(CKTcircuit *circuit, SRC_TAB *source);
void l_dc_stamp(CKTcircuit *circuit, ELM_TAB *element);
void g_stamp(CKTcircuit *circuit, SRC_TAB *source);
void e_stamp(CKTcircuit *circuit, SRC_TAB *source);
void f_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source);
void h_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source);

void v_tran_MNA_stamp(CKTcircuit *circuit, SRC_TAB *source);
void v_tran_RHS_stamp(CKTcircuit *circuit, SRC_TAB *source, int step);
void i_g1_tran_RHS_stamp(CKTcircuit *circuit, SRC_TAB *source, int step);
void i_g2_tran_MNA_stamp(CKTcircuit *circuit, SRC_TAB *source);
void i_g2_tran_RHS_stamp(CKTcircuit *circuit, SRC_TAB *source, int step);

void c_g2_tran_MNA_stamp(CKTcircuit *circuit, ELM_TAB *element);
void c_g2_tran_RHS_stamp(CKTcircuit *circuit, HASH_TAB *htab, ELM_TAB *element, int step);
void c_g1_tran_MNA_stamp(CKTcircuit *circuit, ELM_TAB *element);
void c_g1_tran_RHS_stamp(CKTcircuit *circuit, HASH_TAB *htab, ELM_TAB *element, int step);
void l_tran_MNA_stamp(CKTcircuit *circuit, ELM_TAB *element);
void l_tran_RHS_stamp(CKTcircuit *circuit, ELM_TAB *element, int step);

void r_ac_g1_stamp(CKTcircuit *circuit, ELM_TAB *element);
void r_ac_g2_stamp(CKTcircuit *circuit, ELM_TAB *element);
void c_ac_g1_stamp(CKTcircuit *circuit, ELM_TAB *element);
void l_ac_g2_stamp(CKTcircuit *circuit, ELM_TAB *element);
void v_ac_stamp(CKTcircuit *circuit, SRC_TAB *source);
void v_0_ac_stamp(CKTcircuit *circuit, SRC_TAB *source);
void i_ac_g1_stamp(CKTcircuit *circuit, SRC_TAB *source);
void i_ac_g2_stamp(CKTcircuit *circuit, SRC_TAB *source);
void g_ac_stamp(CKTcircuit *circuit, SRC_TAB *source);
void e_ac_stamp(CKTcircuit *circuit, SRC_TAB *source);
void f_ac_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source);
void h_ac_stamp(CKTcircuit *circuit, HASH_TAB *htab, SRC_TAB *source);
