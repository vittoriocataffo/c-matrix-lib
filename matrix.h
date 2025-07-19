/* Simple library for basic matrix operations */

#ifndef MATRIX_H
#define MATRIX_H

/* This is the structure representing the 2D matrix. The matrix data is stored in a single, contigous block of memory */
typedef struct {
	int rows;	// number of rows
	int cols;	// number of columns
	double *data;	// Pointer to the data (rows * cols elements)
} Matrix;

/* Returns the pointer to the newly created matrix of the specified dimensions */
Matrix* matrix_create(int rows, int cols);

/* Frees the memory associated with a matrix */
void matrix_free(Matrix *m);

/* Prints the matrix */
void matrix_print(const Matrix *m);

/* Creates a copy of a matrix */
Matrix* matrix_clone(const Matrix *m);

/* Creates an identity matrix of a given size */
Matrix* matrix_identity(int size);

/* Adds two matrices */
Matrix* matrix_add(const Matrix *a, const Matrix *b);

/* Subtracts two matrices */
Matrix* matrix_subtract(const Matrix *a, const Matrix *b);

/* Multliplies a matrix by a scalar value */
Matrix* matrix_mul_scalar(const Matrix *a, double s);

/* Multuplies two matrix */
Matrix* matrix_mul(const Matrix *a, const Matrix *b);

/* Transposes a matrix */
Matrix* matrix_transpose(const Matrix *a);

#endif
