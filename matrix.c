#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* Macro for translating the 2D coordinates (row,cols) into a single 1D array index */
#define M_AT(m,r,c) ( m->data[ r * m->cols + c] )


Matrix* matrix_create(size_t rows, size_t cols) {
	// check for invalid dimensions
    if (rows == 0 || cols == 0) return NULL;
    
    // allocate the struct itself
	Matrix *m = malloc(sizeof(Matrix)); 
	if (m == NULL) return NULL; // allocation failed
    
	m->rows = rows;
	m->cols = cols;

    size_t dim = rows * cols;
    // allocate the data
    m->data = malloc(dim * sizeof(double));
    if (m->data == NULL) {
        free(m);
        return NULL;
    }

    // initialize the data
    for (size_t i = 0; i < dim; i++) m->data[i] = 0.0; 

    return m;
}

void matrix_init_rand(Matrix *m, double min, double max) {
    if (m == NULL || m->data == NULL) return;
    if (min > max) {
        double tmp = min;
        min = max;
        max = tmp;
    }

    size_t dim = m->rows * m->cols;
    for (size_t i = 0; i < dim; i++) {
        m->data[i] = (double)rand() / RAND_MAX * (max - min) + min;
    }
}

void matrix_free(Matrix *m) {
    if (m != NULL) {
        free(m->data);
        free(m);
    }
}

void matrix_print(const Matrix *m) {
    if (m == NULL || m->data == NULL) {
        printf("error print [invalid matrix]\n");
        return;
    }
    printf("Matrix [%zux%zu]:\n", m->rows, m->cols);
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            printf("%8.2f", M_AT(m,i,j));
        }
        printf("\n");
    }
    printf("\n");
}

Matrix* matrix_clone(const Matrix *m) {
    if (m == NULL || m->data == NULL) return NULL;

    Matrix *clone = matrix_create(m->rows, m->cols);
    if (clone == NULL) return NULL;

    size_t dim = m->rows * m->cols;
    for (size_t i = 0; i < dim; i++) clone->data[i] = m->data[i]; 

    return clone;
}

Matrix* matrix_identity(size_t size) {
    Matrix *m = matrix_create(size, size);
    if (m == NULL) return NULL;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            M_AT(m,i,j) = (i == j) ? 1 : 0;
        }
    }
    return m;
}

Matrix* matrix_add(const Matrix *a, const Matrix *b) {
    if ( a == NULL || b == NULL || a->rows != b->rows || a->cols != b->cols) {
        return NULL;
    }
    Matrix *c = matrix_create(a->rows, a->cols);
    if (c == NULL) return NULL;

    size_t dim = c->rows * c->cols;
    for (size_t i = 0; i < dim; i++) {
        c->data[i] = a->data[i] + b->data[i];
    }
    return c;
}


Matrix* matrix_subtract(const Matrix *a, const Matrix *b) {
    if ( a == NULL || b == NULL || a->rows != b->rows || a->cols != b->cols) {
        return NULL;
    }
    Matrix *c = matrix_create(a->rows, a->cols);
    if (c == NULL) return NULL;

    size_t dim = c->rows * c->cols;
    for (size_t i = 0; i < dim; i++) {
        c->data[i] = a->data[i] - b->data[i];
    }
    return c;
}

/* Multliplies a matrix by a scalar value */
Matrix* matrix_mul_scalar(const Matrix *a, double s) {
    if ( a == NULL ) return NULL;
  
    Matrix *r = matrix_create(a->rows, a->cols);
    if (r == NULL) return NULL;

    size_t dim = r->rows * r->cols;
    for (size_t i = 0; i < dim; i++) {
        r->data[i] = a->data[i] * s;
    }
    return r;
}

/* Multuplies two matrix */
Matrix* matrix_mul(const Matrix *a, const Matrix *b) {
    if ( a == NULL || b == NULL || a->cols != b->rows ) {
        return NULL;
    }
    Matrix *r = matrix_create(a->rows,b->cols);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < a->cols; k++) {
                sum += M_AT(a,i,k) * M_AT(b,k,j);
            }
            M_AT(r,i,j) = sum;
        }
    }
    return r;
}

/* Transposes a matrix */
Matrix* matrix_transpose(const Matrix *a) {
    if ( a == NULL) return NULL;

    Matrix *r = matrix_create(a->cols, a->rows);
    if (r == NULL) return NULL;

    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < a->cols; j++) {
            M_AT(r,j,i) = M_AT(a,i,j);
        }
    }
    return r;
}