#include "matrix.h"
#include <stdio.h>


#define M_AT(m,r,c) ( m->data[ r * m->cols + c] )

int main(void) {

    // create two matrices
    Matrix *A = matrix_create(2,3);
    Matrix *B = matrix_create(2,3);
    
    // fill them with data
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            M_AT(A,i,j) = i+j;
            M_AT(B,i,j) = 6-i;
        }
    }

    // print them
    printf("A:\n");
    matrix_print(A);
    printf("B:\n");
    matrix_print(B);

    // add the two matrix
    Matrix *C = matrix_add(A,B);
    printf("C=A+B:\n");
    matrix_print(C);

    // multiply by scalar
    Matrix *D = matrix_mul_scalar(A,2);
    printf("2*A\n");
    matrix_print(D);

    // transpose the matrix
    Matrix *E = matrix_transpose(B);
    printf("E (transpose of B)\n");
    matrix_print(E);

    // multiply two matrices
    Matrix *F = matrix_mul(A, E);
    printf("A*E\n");
    matrix_print(F);

    
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
    matrix_free(E);
    matrix_free(F);

    return 0;
}
