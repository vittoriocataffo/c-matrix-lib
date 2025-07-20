/*Test program for matrix library-85e5e32c8188  *******/

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Macro for translating the 2D coordinates (row,cols) into a single 1D array index */
#define M_AT(m,r,c) ( m->data[ r * m->cols + c] )

int main(void) {

    srand(time(NULL)); // seed the random number generator

    // create two matrices
    Matrix *A = matrix_create(3,4);
    if (A == NULL) {printf("matrix_create failed\n"); return 1;} // return 1;
    printf("A before random initialization:\n");
    matrix_print(A);

    matrix_init_rand(A, -10.0, 10.0);
    printf("A after random initialization:\n");
    matrix_print(A);

    Matrix *B = matrix_clone(A);
    if (B == NULL) {printf("matrix_create failed\n"); return 1;} // return 1;
    printf("B (copy of A):\n");
    matrix_print(B);

    // add the two matrix
    Matrix *C = matrix_add(A,B);
    if (C == NULL) {printf("matrix_add failed\n"); return 1;}
    printf("C = A + B:\n");
    matrix_print(C);

    // multiply by scalar
    Matrix *D = matrix_mul_scalar(A,10.0);
    if (D == NULL) {printf("matrix_mul_scalar failed\n"); return 1;}
    printf("D = 10 * A:\n");
    matrix_print(D);

    // transpose the matrix
    Matrix *E = matrix_transpose(D);
    if (E == NULL) {printf("matrix_transpose failed\n"); return 1;}
    printf("E (transpose of D)\n");
    matrix_print(E);

    // multiply two matrices
    Matrix *F = matrix_mul(A, E);
    if (F == NULL) {printf("matrix_mul failed\n"); return 1;}
    printf("F = A * E:\n");
    matrix_print(F);

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
    matrix_free(E);
    matrix_free(F);

    return 0;
}
