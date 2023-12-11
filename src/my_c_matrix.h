#ifndef SRC_MY_C_MATRIX_H_
#define SRC_MY_C_MATRIX_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

typedef enum {
  CORRECT_MATRIX = 0,
  INCORRECT_MATRIX = 1,
  IDENTITY_MATRIX = 2,
  ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
  matrix_type_t matrix_type;
} matrix_t;

/*--------------functions--------------*/
// create matrix
matrix_t my_create_matrix(int rows, int columns);
// remove matrix
void my_remove_matrix(matrix_t *A);
// matrix comparison
int my_eq_matrix(matrix_t *A, matrix_t *B);
// matrix addition
matrix_t my_sum_matrix(matrix_t *A, matrix_t *B);
// matrix subtraction
matrix_t my_sub_matrix(matrix_t *A, matrix_t *B);
// multiplying a matrix by a number
matrix_t my_mult_number(matrix_t *A, double number);
// matrix multiplication
matrix_t my_mult_matrix(matrix_t *A, matrix_t *B);
// transposed matrix
matrix_t my_transpose(matrix_t *A);
// matrix determinant
double my_determinant(matrix_t *A);
// minor and algebraic complement of the matrix
matrix_t my_calc_complements(matrix_t *A);
// inverse matrix
matrix_t my_inverse_matrix(matrix_t *A);

/*----------helper functions----------*/
// check if rows == columns in matrix
int my_check_eq_size(matrix_t *, matrix_t *);
// check if matrix_type == INCORRECT_MATRIX
int my_check_incorrect(matrix_t *);
// to get the type of matrix and return it
int my_get_matrix_type(matrix_t *);
int my_check_zero_matrix(matrix_t *);
int my_check_identity_matrix(matrix_t *);
// check value == 1
int my_eq_one(double);
// get minor matrix
void my_get_minor_matrix(matrix_t *, matrix_t *, int, int);

#endif  //  SRC_MY_C_MATRIX_H_
