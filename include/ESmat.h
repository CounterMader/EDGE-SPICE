#define DEFAULT_VALUE 0.0

#define CANNOT_ADD "Cannot add two matrices with different dimensions."

#define CANNOT_SUBTRACT "Cannot subctract two matrices with different dimensions."

#define CANNOT_MULITPLY \
  "Cannot multiply two matrices where \
  the number of columns of the first one \
  is different than the number of rows of the second one." \

#define CANNOT_REMOVE_COLUMN "Cannot remove matrix column %d. The value should be less than %d." 

#define CANNOT_REMOVE_ROW "Cannot remove matrix row %d. The value should be less than %d." 

#define INVALID_ROWS \
  "Cannot create matrix with 0 number of rows. Aborting." \

#define INVALID_COLS \
    "Cannot create matrix with 0 number of cols. Aborting." \

#define CANNOT_TRACE \
    "Cannot calculate trace. Matrix needs to be square." \

#define CANNOT_CROUT \
    "Cannot apply crout algorithm. Matrix needs to be square." \

#define CANNOT_SWAP_ROWS \
     "Cannot swap rows (%d, %d) because the matrix number of rows is %d." \

#define CANNOT_SWAP_COLUMNS \
      "Cannot swap columns (%d, %d) because the matrix number or columns is %d." \

#define CANNOT_ROW_MULTIPLY \
      "Cannot multiply row (%d), maximum number of rows is %d." \

#define CANNOT_COL_MULTIPLY "Cannot multiply col (%d), maximum number of columns is %d." 
  
#define CANNOT_ADD_TO_ROW \
      "Cannot add %2.2f x (row=%d) to row=%d. Total number of rows is: %d." \

#define CANNOT_LU_MATRIX_SQUARE \
      "Canot LU. Matrix (%d, %d) needs to be square." \

#define CANNOT_LU_MATRIX_DEGENERATE \
      "Cannot LU. Matrix is degenerate or almost degenerate." \

#define CANNOT_SOLVE_LIN_SYS_INVALID_B \
      "Cannot solve system. b[%d][%d] should have size b[%d][%d]." \

#define CANNOT_SET_DIAG \
      "Cannot set diag with value(=%2.2f). Matrix is not square." \

#define CANNOT_CONCATENATE_H \
      "Cannot concatenate. Matrices have a different number of rows. Expected %d, found: %d." \

#define CANNOT_CONCATENATE_V \
      "Cannot concatenate. Matrices have a different number of cols. Expected %d, found: %d." \

#define CANNOT_GET_COLUMN \
      "Cannot get column (%d). The matrix has %d number of columns." \

#define CANNOT_GET_ROW \
      "Cannot get row (%d). The matrix has %d number of rows." \

#define INCONSITENT_ARRAY \
      "Cannot found element %d in the array (NULL). Expected a total of : %d elements."  \

#define INCONSITENT_VARGS \
      "Cannot find element %d in the varargs. Expecteda total of : %d varargs." \

#define CANNOT_REF_MATRIX_DEGENERATE \
      "Cannot compute REF. Matrix is degenerate or near degenerate." \

#define CANNOT_OPEN_FILE "Cannot open file '%s'. Please check the path is correct and you have reading rights."

#define INVALID_MATRIX_FILE \
      "Invalid matrix file: %s. Cannot read data." \

#define VECTOR_J_DEGENERATE \
      "Vector on colum %d is generate or near degenerate. Cannot proceed further." \

#define CANNOT_QR_NON_SQUARE \
      "We cannot QA non-square matrix[%d, %d]." \

#define CANNOT_COLUMN_L2NORM \
      "Cannot get column (%d). The matrix has %d numbers of columns." \

#define CANNOT_VECT_DOT_DIMENSIONS \
      "The two vectors have different dimensions: %d and %d." \

#define ES_MIN_COEF 0.000000000000001

#define NP_CHECK(ptr) \
        if (!(ptr)) { \
            log_error("%s:%d NULL POINTER: %s n", \
                __FILE__, __LINE__, (#ptr)); \
            exit(-1); \
        } \
/*
    Matrix structure
*/
#include <lapacke.h>

typedef struct _complex_s{
      double re;
      double im;
}EScomp;

typedef struct _ES_mat_complex_s{
      unsigned int num_rows;
      unsigned int num_cols;
      EScomp **data;
      int is_square;
}ES_mat_comp;

typedef struct _ES_mat_s{
      unsigned int num_rows;
      unsigned int num_cols;
      double **data;
      int is_square;
}ES_mat;

/*
      LUP Structure
*/
typedef struct ES_mat_lup_s {
      ES_mat *L;
      ES_mat *U;
      ES_mat *P;
      unsigned int num_permutations;
} ES_mat_lup;

/*
    Functions prototype
*/
ES_mat *ES_mat_new(unsigned int num_rows, unsigned int num_cols);
ES_mat_comp *ES_mat_comp_new(unsigned int num_rows, unsigned int num_cols);
ES_mat *ES_mat_sqr(unsigned int size);
ES_mat *ES_mat_identity(unsigned int size);
ES_mat *ES_mat_cp(ES_mat *m);
void ES_mat_free(ES_mat *mat);
int ES_mat_eqdim(ES_mat *m1, ES_mat *m2);
int ES_mat_eq(ES_mat *m1, ES_mat *m2, double tolerance);
void ES_mat_print(ES_mat *matrix, FILE *fp);
void ES_mat_comp_print(ES_mat_comp *matrix, FILE *fp);
void ES_mat_printf(ES_mat *mat, const char *d_fmt, FILE *fp);
void ES_mat_comp_printf(ES_mat_comp *mat, const char *d_fmt, FILE *fp);
double ES_mat_get(ES_mat *matrix, unsigned int i, unsigned int j);
ES_mat *ES_mat_col_get(ES_mat *m, unsigned int col);
ES_mat *ES_mat_row_get(ES_mat *m, unsigned int row);
void ES_mat_set(ES_mat *matrix, unsigned int i, unsigned int j, double value);
void ES_mat_all_set(ES_mat *matrix, double value);
int ES_mat_diag_set(ES_mat *m, double value);
ES_mat *ES_mat_row_mult(ES_mat *m, unsigned int row, double num);
int ES_mat_row_mult_r(ES_mat *m, unsigned int row, double num);
ES_mat *ES_mat_col_mult(ES_mat *m, unsigned int col, double num);
int ES_mat_col_mult_r(ES_mat *m, unsigned int col, double num);
ES_mat *ES_mat_row_addrow(ES_mat *m, unsigned int where, unsigned int row, double multiplier);
int ES_mat_row_addrow_r(ES_mat *m, unsigned int where, unsigned int row, double multiplier);
ES_mat *ES_mat_smult(ES_mat *m, double num);
int ES_mat_smult_r(ES_mat *m, double num);
ES_mat *ES_mat_col_rem(ES_mat *m, unsigned int column);
ES_mat *ES_mat_row_rem(ES_mat *m, unsigned int row);
ES_mat *ES_mat_row_swap(ES_mat *m, unsigned int row1, unsigned int row2);
int ES_mat_row_swap_r(ES_mat *m, unsigned int row1, unsigned int row2);
ES_mat *ES_mat_col_swap(ES_mat *m, unsigned int col1, unsigned int col2);
int ES_mat_col_swap_r(ES_mat *m, unsigned int col1, unsigned int col2);
ES_mat *ES_mat_cath(unsigned int mnum, ES_mat **marr);
ES_mat *ES_mat_catv(unsigned int mnum, ES_mat **marr);

/*
      Matrix operation
*/
ES_mat *ES_mat_add(ES_mat *m1, ES_mat *m2);
int ES_mat_add_r(ES_mat *m1, ES_mat *m2);
ES_mat *ES_mat_sub(ES_mat *m1, ES_mat *m2);
int ES_mat_sub_r(ES_mat *m1, ES_mat *m2);
ES_mat *ES_mat_dot(ES_mat *m1, ES_mat *m2);
ES_mat *ES_mat_transp(ES_mat *m);
double ES_mat_trace(ES_mat* m);

/*
      Row Echelon
*/
ES_mat *ES_mat_ref(ES_mat *m);
ES_mat *ES_mat_rref(ES_mat *m);

/*
      LUP Decomposition
*/
ES_mat_lup *ES_mat_lup_new(ES_mat *L, ES_mat *U, ES_mat *P, unsigned int num_permutations);
ES_mat_lup *ES_mat_lup_solve(ES_mat *m);
void ES_mat_lup_free(ES_mat_lup* lu);
void ES_mat_lup_print(ES_mat_lup *lu, FILE *fp);
void ES_mat_lup_printf(ES_mat_lup *lu, const char *fmt, FILE *fp);
double ES_mat_det(ES_mat_lup* lup);
ES_mat *ES_mat_lu_get(ES_mat_lup* lup);
ES_mat *ES_mat_inv(ES_mat_lup *m);


/*
      Solving linear systems of equations
*/
ES_mat *ES_ls_solvefwd(ES_mat *low_triang, ES_mat *b);
ES_mat *ES_ls_solvebck(ES_mat *upper_triang, ES_mat *b);
ES_mat *ES_ls_solve(ES_mat_lup *lup, ES_mat* b);


