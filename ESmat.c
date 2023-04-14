#include <stdio.h>
#include <stdlib.h>
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

/*
    Print the matrix
*/

void ES_mat_print(ES_mat *matrix) {
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
        for(j = 0; j < mat->num_cols; ++j) {
        fprintf(stdout, d_fmt, mat->data[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
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