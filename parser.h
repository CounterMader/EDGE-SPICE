int parse(const char *file_name);
void add_RLC(char *eid, int node1, int node2, double value,int group);
void add_V(char *eid, int node1, int node2, double value);
void add_I(char *eid, int node1, int node2, double value, int group);
void add_node(int num);
void yyerror();