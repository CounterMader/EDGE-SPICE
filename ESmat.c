#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ESmat.h"
#include "log.h"

/*
    Matrix Construction
*/

ES_mat *ES_mat_new(unsigned int num_rows, unsigned int num_cols){
    if(num_cols == 0){
        log_trace("Zero Colunms Matrix!");
        return NULL;
    }
    if(num_rows == 0){
        log_trace("Zero Rows Matrix!\n");
        return NULL;
    }

    ES_mat *mat = (ES_mat*)calloc(1,sizeof(ES_mat));
    if(mat == NULL){
        log_fatal("ES_mat allocation faild! NULL POINTER!!!\n");
        exit(EXIT_FAILURE);
    }
    mat -> num_cols = num_cols;
    mat -> num_rows = num_rows;
    mat -> is_square = (num_cols == num_rows) ? 1 : 0;

    mat -> data = (double**)calloc(mat -> num_rows, sizeof(*mat -> data));
    if(mat -> data == NULL){
        log_fatal("ES_mat data array allocation faild! NULL POINTER!!!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0;i < mat -> num_cols;i++){
        mat -> data[i] = calloc(mat -> num_cols, sizeof(**mat -> data));
        if(mat -> data[i] == NULL){
            log_fatal("ES_mat colunms data array allocation faild! NULL POINTER!!!\n");
            exit(EXIT_FAILURE);
        }
    }

    return mat;
}

ES_mat *ES_mat_sqr(unsigned int size){
    return ES_mat_new(size,size);
}

ES_mat *ES_mat_identity(unsigned int size){
    ES_mat *mat = ES_mat_new(size, size);
    if(mat == NULL){
        return NULL;
    }
    for(int i = 0;i < mat -> num_rows;i++){
        mat -> data[i][i] = 1.0;
    }
    return mat;
}

ES_mat *ES_mat_cp(ES_mat *m){
    ES_mat *r  = ES_mat_new(m -> num_rows, m -> num_cols);
    int i,j;
    for(i = 0; i < r -> num_rows; i++){
        for(j = 0; j < r -> num_cols; j++){
        r -> data[i][j] = m -> data[i][j];
        }
    }
    return r;
}

/*
    Matrix structure Free
*/

void ES_mat_free(ES_mat *mat){
    int i;
    for(i = 0; i < mat -> num_rows; ++i){
        free(mat -> data[i]);
    }
    free(mat -> data);
    free(mat);
    log_trace("Matrix free SUCCESS!");
}

/*
    Matrix Equality
*/

// Checks if two matrices have the same dimesions
int ES_mat_eqdim(ES_mat *m1, ES_mat *m2){
    return (m1->num_cols == m2->num_cols) && (m1->num_rows == m2->num_rows);
}

// Checks if two matrices have the same dimensions, and the elements
// are all equal to each other with a given tolerance;
// For exact equality use tolerance = 0.0
int ES_mat_eq(ES_mat *m1, ES_mat *m2, double tolerance){
    if (!ES_mat_eqdim(m1, m2)){
        return 0;
    }
    int i, j;
    for(i = 0; i < m1 -> num_rows; i++){
        for(j = 0; j < m1 -> num_cols; j++){
        if (fabs(m1 -> data[i][j] - m2 -> data[i][j]) > tolerance){
            return 0;
        }
        }
    }
    return 1;
}

/*
    Print the matrix
*/

void ES_mat_print(ES_mat *matrix){
    ES_mat_printf(matrix, "%lf\t\t");
}

void ES_mat_printf(ES_mat *mat, const char *d_fmt){
    if(mat == NULL){
        log_trace("NULL pointer passed through ES_mat_printf!\n");
        return;
    }
    int i, j;
    fprintf(stdout, "\n");
    for(i = 0; i < mat->num_rows; ++i){
        for(j = 0; j < mat->num_cols; ++j){
        fprintf(stdout, d_fmt, mat->data[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

/*
    Accessing and modifying matrix elements
*/

double ES_mat_get(ES_mat *matrix, unsigned int i, unsigned int j){
    return matrix -> data[i][j];
}

ES_mat *ES_mat_col_get(ES_mat *m, unsigned int col){
    if (col >= m -> num_cols){
        log_error(CANNOT_GET_COLUMN, col, m->num_cols);
        return NULL;
    }
    ES_mat *r = ES_mat_new(m -> num_rows, 1);
    int j;
    for(j = 0; j < r -> num_rows; j++){
        r -> data[j][0] = m -> data[j][col];
    }
    return r;
}

ES_mat *ES_mat_row_get(ES_mat *m, unsigned int row){
    if (row >= m -> num_rows){
        log_error(CANNOT_GET_ROW, row, m->num_rows);
        return NULL;
    }
    ES_mat *r = ES_mat_new(1, m -> num_cols);
    memcpy(r -> data[0], m -> data[row], m -> num_cols * sizeof(*r -> data[0]));
    return r;
}

void ES_mat_set(ES_mat *matrix, unsigned int i, unsigned int j, double value){
    matrix -> data[i][j] = value;
}

// Sets all elements of a matrix to a given value
void ES_mat_all_set(ES_mat *matrix, double value){
    int i, j;
    for(i = 0; i < matrix -> num_rows; i++){
        for(j = 0; j < matrix -> num_cols; j++){
        matrix -> data[i][j] = value;
        }
    }
}

// Sets all elements of the matrix to given value
int ES_mat_diag_set(ES_mat *m, double value){
    if (!m -> is_square){
        log_error(CANNOT_SET_DIAG, value);
        return 0;
    }
    int i;
    for(i = 0; i < m -> num_rows; i++){
        m -> data[i][i] = value;
    }
    return 1;
}

ES_mat *ES_mat_row_mult(ES_mat *m, unsigned int row, double num){
    ES_mat *r = ES_mat_cp(m);
    if (!ES_mat_row_mult_r(r, row, num)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
}

int ES_mat_row_mult_r(ES_mat *m, unsigned int row, double num){
    if (row >= m -> num_rows){
        log_error(CANNOT_ROW_MULTIPLY, row, m->num_rows);
        return 0;
    }
    int i;
    for(i=0; i < m -> num_cols; i++){
        m -> data[row][i] *= num;
    }
    return 1;
}

ES_mat *ES_mat_col_mult(ES_mat *m, unsigned int col, double num){
    ES_mat *r = ES_mat_cp(m);
    if (!ES_mat_col_mult_r(r, col, num)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
}

int ES_mat_col_mult_r(ES_mat *m, unsigned int col, double num){
    if (col>=m->num_cols){
        log_error(CANNOT_COL_MULTIPLY, col, m -> num_cols);
        return 0;
    }
    int i;
    for(i = 0; i < m -> num_rows; i++){
        m -> data[i][col] *= num;
    }
    return 1;
}

ES_mat *ES_mat_row_addrow(ES_mat *m, unsigned int where, unsigned int row, double multiplier){
    ES_mat *r = ES_mat_cp(m);
    if (!ES_mat_row_addrow_r(m, where, row, multiplier)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
}

int ES_mat_row_addrow_r(ES_mat *m, unsigned int where, unsigned int row, double multiplier){

    if (where >= m -> num_rows || row >= m -> num_rows){
        log_error(CANNOT_ADD_TO_ROW, multiplier, row, where, m->num_rows);
        return 0;
    }
    int i = 0;
    for(i = 0; i < m -> num_cols; i++){
        m -> data[where][i] += multiplier * m -> data[row][i];
    }
    return 1;
}

ES_mat *ES_mat_smult(ES_mat *m, double num){
    ES_mat *r = ES_mat_cp(m);
    ES_mat_smult_r(r, num);
    return r;
}

int ES_mat_smult_r(ES_mat *m, double num){
    int i, j;
    for(i = 0; i < m -> num_rows; i++){
        for(j = 0; j < m -> num_cols; j++){
        m -> data[i][j] *= num;
        }
    }
    return 1;
}

/*
    Modifying the matrix structure
*/

ES_mat *ES_mat_col_rem(ES_mat *m, unsigned int column){
    if(column >= m -> num_cols){
        log_error(CANNOT_REMOVE_COLUMN, column, m->num_cols);
        return NULL;
    }
    ES_mat *r = ES_mat_new(m -> num_rows, m -> num_cols - 1);
    int i, j, k;
    for(i = 0; i < m -> num_rows; i++){
        for(j = 0, k=0; j < m -> num_cols; j++){
            if (column != j){
                r -> data[i][k++] = m -> data[i][j];
            }
        }
    }
    return r;
}

ES_mat *ES_mat_row_rem(ES_mat *m, unsigned int row){
    if (row >= m->num_rows){
        log_error(CANNOT_REMOVE_ROW, row, m->num_rows);
        return NULL;
    }
    ES_mat *r = ES_mat_new(m->num_rows-1, m->num_cols);
    int i, j, k;
    for(i = 0, k = 0; i < m -> num_rows; i++){
        if (row != i){
            for(j = 0; j < m -> num_cols; j++){
                r -> data[k][j] = m -> data[i][j];
            }
            k++;
        }
    }
    return r;
}

ES_mat *ES_mat_row_swap(ES_mat *m, unsigned int row1, unsigned int row2){
    ES_mat *r = ES_mat_cp(m);
    if (!ES_mat_row_swap_r(r, row1, row2)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
}

int ES_mat_row_swap_r(ES_mat *m, unsigned int row1, unsigned int row2){
    if (row1 >= m -> num_rows || row2 >= m -> num_rows){
        log_error(CANNOT_SWAP_ROWS, row1, row2, m -> num_rows);
        return 0;
    }
    double *tmp = m -> data[row2];
    m -> data[row2] = m -> data[row1];
    m -> data[row1] = tmp;
    return 1;
}

ES_mat *ES_mat_col_swap(ES_mat *m, unsigned int col1, unsigned int col2){
    ES_mat *r = ES_mat_cp(m);
    if (!ES_mat_col_swap_r(r, col1, col2)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
}

int ES_mat_col_swap_r(ES_mat *m, unsigned int col1, unsigned int col2){
    if (col1 >= m->num_cols || col2 >= m->num_cols){
        log_error(CANNOT_SWAP_ROWS, col1, col2, m->num_cols);
        return 0;
    }
    double tmp;
    int j;
    for(j = 0; j < m -> num_rows; j++){
        tmp = m -> data[j][col1];
        m -> data[j][col1] = m -> data[j][col2];
        m -> data[j][col2] = tmp;
    }
    return 1;
}

ES_mat *ES_mat_cath(unsigned int mnum, ES_mat **marr){
    if (0 == mnum){
        return NULL;
    }
    if (1 == mnum){
        // We just return the one matrix supplied as the first param
        // no need for additional logic
        return ES_mat_cp(marr[0]);
    }
    // We calculate the total number of columns to know how to allocate memory
    // for the resulting matrix
    int i, j, k, offset;
    unsigned int lrow, ncols;
    lrow = marr[0] -> num_rows;
    ncols = marr[0] -> num_cols;
    for(k = 1; k < mnum; k++){
        if (NULL == marr[k]){
        log_error(INCONSITENT_ARRAY, k, mnum);
        return NULL;
        }
        if (lrow != marr[k] -> num_rows){
        log_error(CANNOT_CONCATENATE_H, lrow, marr[k] -> num_rows);
        return NULL;
        }
        ncols += marr[k] -> num_cols;
    }
    // At this point we know how the resulting matrix looks like,
    // we allocate memory for it accordingly
    ES_mat *r = ES_mat_new(lrow, ncols);
    for(i = 0; i < r -> num_rows; i++){
        k = 0;
        offset = 0;
        for(j = 0; j < r -> num_cols; j++){
            // If the column index of marr[k] overflows
            if (j - offset == marr[k] -> num_cols){
                offset += marr[k] -> num_cols;
                // We jump to the next matrix in the array
                k++;
            }
            r -> data[i][j] = marr[k] -> data[i][j - offset];
        }
    }
    return r;
}

// Concatenates a variable number of matrices into one.
// The concentation is done vertically this means the matrices need to have
// the same number of columns, while the number of rows is allowed to
// be variable
ES_mat *ES_mat_catv(unsigned int mnum, ES_mat **marr){
    if (0 == mnum){
        return NULL;
    }
    if (1 == mnum){
        return ES_mat_cp(marr[0]);
    }
    // We check to see if the matrices have the same number of columns
    int lcol, i, j, k, offset;
    unsigned int numrows;
    ES_mat *r;
    lcol = marr[0] -> num_cols;
    numrows = 0;
    for(i = 0; i < mnum; i++){
        if (NULL == marr[i]){
        log_error(INCONSITENT_ARRAY, i, mnum);
        return NULL;
        }
        if (lcol != marr[i] -> num_cols){
        log_error(CANNOT_CONCATENATE_V,lcol,marr[i]->num_cols);
        return NULL;
        }
        // In the same time we calculate the resulting matrix number of rows
        numrows += marr[i] -> num_rows;
    }
    // At this point we know the dimensions of the resulting Matrix
    r = ES_mat_new(numrows, lcol);
    // We start copying the values one by one
    for(j = 0; j < r->num_cols; j++){
        offset = 0;
        k = 0;
        for(i = 0; i < r -> num_rows; i++){
            if (i - offset == marr[k] -> num_rows){
                offset += marr[k] -> num_rows;
                k++;
            }
            r -> data[i][j] = marr[k] -> data[i - offset][j];
        }
    }
    ES_mat_print(r);
    return r;
}

/*
    Matrix operations
*/
ES_mat *ES_mat_add(ES_mat *m1, ES_mat *m2){
    ES_mat *r = ES_mat_cp(m1);
    if (!ES_mat_add_r(r, m2)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
}

int ES_mat_add_r(ES_mat *m1, ES_mat *m2){
    if (!ES_mat_eqdim(m1, m2)){
        log_error(CANNOT_ADD);
        return 0;
    }
    int i, j;
    for(i = 0; i < m1->num_rows; i++){
        for(j = 0; j < m1->num_cols; j++){
            m1->data[i][j] += m2->data[i][j];
        }
    }
    return 1;
}

ES_mat *ES_mat_sub(ES_mat *m1, ES_mat *m2){
    ES_mat *r = ES_mat_cp(m2);
    if (!ES_mat_sub_r(r, m2)){
        ES_mat_free(r);
        return NULL;
    }
    return r;
    }

int ES_mat_sub_r(ES_mat *m1, ES_mat *m2){
    if (!ES_mat_eqdim(m1, m2)){
        log_error(CANNOT_SUBTRACT);
        return 0;
    }
    int i, j;
    for(i = 0; i < m1->num_rows; i++){
        for(j = 0; j < m1->num_cols; j++){
            m1->data[i][j] -= m2->data[i][j];
        }
    }
    return 1;
}

ES_mat *ES_mat_dot(ES_mat *m1, ES_mat *m2){
    if (!(m1->num_cols == m2->num_rows)){
        log_error(CANNOT_MULITPLY);
        return NULL;
    }
    int i, j, k;
    ES_mat *r = ES_mat_new(m1->num_rows, m2->num_cols);
    for(i = 0; i < r->num_rows; i++){
        for(j = 0; j < r->num_cols; j++){
            for(k = 0; k < m1->num_cols; k++){
                r->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
    return r;
}

ES_mat *ES_mat_transp(ES_mat *m){
    int i, j;
    ES_mat *r = ES_mat_new(m->num_cols, m->num_rows);
    for(i = 0; i < r->num_rows; i++){
        for(j = 0; j < r->num_cols; j++){
        r->data[i][j] = m->data[j][i];
        }
    }
    return r;
}

double ES_mat_trace(ES_mat* m){
    if (!m->is_square){
        log_error(CANNOT_TRACE);
    }
    int i;
    double trace = 0.0;
    for(i = 0; i < m->num_rows; i++){
        trace += m->data[i][i];
    }
    return trace;
}

// *****************************************************************************
//
// Row Echelon
//
// *****************************************************************************

// Finds the first non-zero element on the col column, under the row row.
// This is used to determine the pivot in gauss Elimination
// If not pivot is found, returns -1
int _ES_mat_pivotidx(ES_mat *m, unsigned int col, unsigned int row){
    // No validations are made, this is an API Method
    int i;
    for(i = row; i < m->num_rows; i++){
        if (fabs(m->data[i][col]) > ES_MIN_COEF){
            return i;
        }
    }
    return -1;
}

// Find the max element from the column "col" under the row "row"
// This is needed to pivot in Gauss-Jordan elimination
// If pivot is not found, return -1
int _ES_mat_pivotmaxidx(ES_mat *m, unsigned int col, unsigned int row){
    int i, maxi;
    double micol;
    double max = fabs(m->data[row][col]);
    maxi = row;
    for(i = row; i < m->num_rows; i++){
        micol = fabs(m->data[i][col]);
        if (micol>max){
            max = micol;
            maxi = i;
        }
    }
    return (max < ES_MIN_COEF) ? -1 : maxi;
}

// Retrieves the matrix in Row Echelon form using Gauss Elimination
ES_mat *ES_mat_ref(ES_mat *m){
    ES_mat *r = ES_mat_cp(m);
    int i, j, k, pivot;
    j = 0, i = 0;
    while(j < r->num_cols && i < r->num_cols){
        // Find the pivot - the first non-zero entry in the first column of the matrix
        pivot = _ES_mat_pivotidx(r, j, i);
        if (pivot<0){
            // All elements on the column are zeros
            // We move to the next column without doing anything
            j++;
            continue;
        }
        // We interchange rows moving the pivot to the first row that doesn't have
        // already a pivot in place
        if (pivot!=i){
            ES_mat_row_swap_r(r, i, pivot);
        }
        // Multiply each element in the pivot row by the inverse of the pivot
        ES_mat_row_mult_r(r, i, 1/r->data[i][j]);
        // We add multiplies of the pivot so every element on the column equals 0
        for(k = i+1; k < r->num_rows; k++){
            if (fabs(r->data[k][j]) > ES_MIN_COEF){
                ES_mat_row_addrow_r(r, k, i, -(r->data[k][j]));
            } 
        }
        i++;
        j++;
    }
    return r;
}

// Retrieves the matrix in Reduced Row Echelon using Guass-Jordan Elimination
ES_mat *ES_mat_rref(ES_mat *m){
    ES_mat* r = ES_mat_cp(m);
    int i,j,k,pivot;
    i = 0;
    j = 0;
    while(j < r->num_cols && i < r->num_rows){
        // We find the pivot, the maximum row id (fabs) in the column
        pivot = _ES_mat_pivotmaxidx(r, j, i);
        if (pivot<0){
            // No pivot, we change columns
            j++;
            continue;
        }
        // We interchange rows to out the pivot row into the 
        // desired position
        if (pivot!=i){
            ES_mat_row_swap_r(r, i, pivot);
        }
        // We create 1 in the pivot position
        ES_mat_row_mult_r(r, i, 1/r->data[i][j]);
        // We put zeros on the colum with the pivot
        for(k = 0; k < r->num_rows; k++){
            if (!(k==i)){
                ES_mat_row_addrow_r(r, k, i, -(r->data[k][j]));
            }
        }
        i++;
        j++;
    }
    return r;
}

// *****************************************************************************
//
// LUP Decomposition
//
// *****************************************************************************

// Finds the maxid on the column (starting from k -> num_rows)
// This method is used for pivoting in LUP decomposition
int _ES_mat_absmaxr(ES_mat *m, unsigned int k){
    // Find max id on the column;
    int i;
    double max = m->data[k][k];
    int maxIdx = k;
    for(i = k+1; i < m->num_rows; i++){
        if (fabs(m->data[i][k]) > max){
            max = fabs(m->data[i][k]);
            maxIdx = i;
        }
    }
    return maxIdx;
}

// Allocates memory for a new ES_mat_lup structure
ES_mat_lup *ES_mat_lup_new(ES_mat *L, ES_mat *U, ES_mat *P, unsigned int num_permutations){
    ES_mat_lup *r = malloc(sizeof(*r));
    if(r == NULL){
            log_fatal("ES_mat data array allocation faild! NULL POINTER!!!\n");
            exit(EXIT_FAILURE);
    }
    r->L = L;
    r->U = U;
    r->P = P;
    r->num_permutations = num_permutations;
    return r;
}
void ES_mat_lup_free(ES_mat_lup* lu){
    ES_mat_free(lu->P);
    ES_mat_free(lu->L);
    ES_mat_free(lu->U);
    free(lu);
}

void ES_mat_lup_print(ES_mat_lup *lu){
    ES_mat_print(lu->L);
    ES_mat_print(lu->U);
    ES_mat_print(lu->P);
}

void ES_mat_lup_printf(ES_mat_lup *lu, const char *fmt){
    ES_mat_printf(lu->L, fmt);
    ES_mat_printf(lu->U, fmt);
    ES_mat_printf(lu->P, fmt);
}

ES_mat_lup *ES_mat_lup_solve(ES_mat *m){
    if (!m->is_square){
        log_error(CANNOT_LU_MATRIX_SQUARE, m->num_rows, m-> num_cols);
        return NULL;
    }
    ES_mat *L = ES_mat_new(m->num_rows, m->num_rows);
    ES_mat *U = ES_mat_cp(m);
    ES_mat *P = ES_mat_identity(m->num_rows);

    int j,i, pivot;
    unsigned int num_permutations = 0;
    double mult;

    for(j = 0; j < U->num_cols; j++){
        // Retrieves the row with the biggest element for column (j)
        pivot = _ES_mat_absmaxr(U, j);
        if (fabs(U->data[pivot][j]) < ES_MIN_COEF){
            log_error(CANNOT_LU_MATRIX_DEGENERATE);
            return NULL;
        }
        if (pivot!=j){
            // Pivots LU and P accordingly to the rule
            ES_mat_row_swap_r(U, j, pivot);
            ES_mat_row_swap_r(L, j, pivot);
            ES_mat_row_swap_r(P, j, pivot);
            // Keep the number of permutations to easily calculate the
            // determinant sign afterwards
            num_permutations++;
        }
        for(i = j+1; i < U->num_rows; i++){
            mult = U->data[i][j] / U->data[j][j];
            // Building the U upper rows
            ES_mat_row_addrow_r(U, i, j, -mult);
            // Store the multiplier in L
            L->data[i][j] = mult;
        }
    }
    ES_mat_diag_set(L, 1.0);

    return ES_mat_lup_new(L, U, P, num_permutations);
}

// After the LU(P) factorisation the determinant can be easily calculated
// by multiplying the main diagonal of matrix U with the sign.
// the sign is -1 if the number of permutations is odd
// the sign is +1 if the number of permutations is even
double ES_mat_det(ES_mat_lup* lup){
    int k;
    int sign = (lup->num_permutations%2 == 0) ? 1 : -1;
    ES_mat *U = lup->U;
    double product = 1.0;
    for(k = 0; k < U->num_rows; k++){
        product *= U->data[k][k];
    }
    return product * sign;
}

// Returns LU matrix from a LUP structure
ES_mat *ES_mat_lu_get(ES_mat_lup* lup){
    ES_mat *r = ES_mat_cp(lup->U);
    // Copy L (without first diagonal in result)
    int i, j;
    for(i = 1; i < lup->L->num_rows; i++){
        for(j = 0; j < i; j++){
            r->data[i][j] = lup->L->data[i][j];
        }
    }
    return r;
}

// *****************************************************************************
//
// Solving linear systems of equations
//
// *****************************************************************************

// Forward substitution algorithm
// Solves the linear system L * x = b
//
// L is lower triangular matrix of size NxN
// B is column matrix of size Nx1
// x is the solution column matrix of size Nx1
//
// Note: In case L is not a lower triangular matrix, the algorithm will try to
// select only the lower triangular part of the matrix L and solve the system
// with it.
//
// Note: In case any of the diagonal elements (L[i][i]) are 0 the system cannot
// be solved
//
// Note: This function is usually used with an L matrix from a LU decomposition
ES_mat *ES_ls_solvefwd(ES_mat *L, ES_mat *b){
    ES_mat* x = ES_mat_new(L->num_cols, 1);
    int i,j;
    double tmp;
    for(i = 0; i < L->num_cols; i++){
        tmp = b->data[i][0];
        for(j = 0; j < i ; j++){
            tmp -= L->data[i][j] * x->data[j][0];
        }
        x->data[i][0] = tmp / L->data[i][i];
    }
    return x;
    }


// Back substition algorithm
// Solves the linear system U *x = b
//
// U is an upper triangular matrix of size NxN
// B is a column matrix of size Nx1
// x is the solution column matrix of size Nx1
//
// Note in case U is not an upper triangular matrix, the algorithm will try to
// select only the upper triangular part of the matrix U and solve the system
// with it
//
// Note: In case any of the diagonal elements (U[i][i]) are 0 the system cannot
// be solved
ES_mat *ES_ls_solvebck(ES_mat *U, ES_mat *b){
    ES_mat *x = ES_mat_new(U->num_cols, 1);
    int i = U->num_cols, j;
    double tmp;
    while(i-- > 0){
        tmp = b->data[i][0];
        for(j = i; j < U->num_cols; j++){
            tmp -= U->data[i][j] * x->data[j][0];
        }
        x->data[i][0] = tmp / U->data[i][i];
    }
    return x;
}

// A[n][n] is a square matrix
// m contains matrices L, U, P for A[n][n] so that P*A = L*U
//
// The linear system is:
// A*x=b  =>  P*A*x = P*b  =>  L*U*x = P*b  =>
// (where b is a matrix[n][1], and x is a matrix[n][1])
//
// if y = U*x , we solve two systems:
//    L * y = P b (forward substition)
//    U * x = y (backward substition)
//
// We obtain and return x
ES_mat *ES_ls_solve(ES_mat_lup *lu, ES_mat* b){
    if (lu->U->num_rows != b->num_rows || b->num_cols != 1){
        log_error(CANNOT_SOLVE_LIN_SYS_INVALID_B,
        b->num_rows,
        b->num_cols,
        lu->U->num_rows,
        1);
        return NULL;
    }
    ES_mat *Pb = ES_mat_dot(lu->P, b);

    // We solve L*y = P*b using forward substition
    ES_mat *y = ES_ls_solvefwd(lu->L, Pb);

    // We solve U*x=y
    ES_mat *x = ES_ls_solvebck(lu->U, y);

    ES_mat_free(y);
    ES_mat_free(Pb);
    return x;
}

// Calculates the inverse of a matrix
ES_mat *ES_mat_inv(ES_mat_lup *lup){
    unsigned n = lup->L->num_cols;
    ES_mat *r = ES_mat_sqr(n);
    ES_mat *I = ES_mat_identity(lup->U->num_rows);
    ES_mat *invx;
    ES_mat *Ix;
    int i,j;
    for(j =0; j < n; j++){
        Ix = ES_mat_col_get(I, j);
        invx = ES_ls_solve(lup, Ix);
        for(i = 0; i < invx->num_rows; i++){
            r->data[i][j] = invx->data[i][0];
        }
        ES_mat_free(invx);
        ES_mat_free(Ix);
    }
    ES_mat_free(I);
    return r;
}