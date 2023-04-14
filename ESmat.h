typedef struct _ES_mat_s{
    unsigned int num_rows;
    unsigned int num_cols;
    double **data;
    int is_square;
}ES_mat;

ES_mat *ES_mat_new(unsigned int num_rows, unsigned int num_cols);
ES_mat *ES_mat_sqr(unsigned int size);
ES_mat *ES_mat_identity(unsigned int size);
void ES_mat_print(ES_mat *matrix);
void ES_mat_printf(ES_mat *mat, const char *d_fmt);
void ES_mat_free(ES_mat *mat);