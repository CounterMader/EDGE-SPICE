int parse(const char *file_name);
void add_RLC(char *eid, int node1, int node2, double value,int group);
void add_V(char *eid, int node1, int node2, double value);
void add_I(char *eid, int node1, int node2, double value, int group);
void add_VCCS(char *eid, int node1, int node2, int node3, int node4, double value, int group);
void add_VCVS(char *eid, int node1, int node2, int node3, int node4, double value, int group);
void add_CCCS(char *eid, char *cvs, int node1, int node2, double value, int group);
void add_node(int num);
void set_simultaor_dc();
void set_simultaor_tran(double Tstop, double Tstep);
void yyerror();