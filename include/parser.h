int parse(const char *file_name);
void add_RLC(char *eid, int node1, int node2, double value,int group);
void add_V(char *eid, int node1, int node2, double value);
void add_sine_v(char *sid, int node1, int node2, double offset, double amp, double freq, double delay, double d_factor, double phase);
void add_pulse_v(char *sid, int node1, int node2, double v_off, double v_on, double delay, double Tr, double Tf, double t_on, double t_period);
void add_ramp_v(char *sid, int node1, int node2, double delay);
void add_step_v(char *sid, int node1, int node2, double v_on, double delay);
void add_ac_v(char *sid, int node1, int node2, double amp, double phase);
void add_I(char *eid, int node1, int node2, double value, int group);
void add_VCCS(char *eid, int node1, int node2, int node3, int node4, double value, int group);
void add_VCVS(char *eid, int node1, int node2, int node3, int node4, double value, int group);
void add_CCCS(char *eid, char *cvs, int node1, int node2, double value, int group);
void add_CCVS(char *eid, char *cvs, int node1, int node2, double value, int group);
void add_node(int num);
void set_simultaor_dc();
void set_simultaor_tran(double Tstop, double Tstep);
void yyerror();