#include "my_c_matrix.h"

/*--------------main functions--------------*/
matrix_t my_create_matrix(int rows, int columns) {
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (rows <= 0 || columns <= 0) {
    C.matrix_type = INCORRECT_MATRIX;
    C.matrix = NULL;
  } else {
    int flag = SUCCESS;
    C.matrix = (double **)calloc(rows, sizeof(double *));
    if (C.matrix == NULL) {
      flag = FAILURE;  // if the program can't take memory to creat array
    } else {
      for (int i = 0; i < rows; i++) {
        *(C.matrix + i) = (double *)calloc(columns, sizeof(double));
        if (*(C.matrix + i) == NULL) {
          flag = FAILURE;  // if the program can't take memory to creat array
          break;
        }
      }
    }
    if (flag) {
      C.matrix_type = ZERO_MATRIX;
      C.rows = rows;
      C.columns = columns;
    } else {
      C.rows = 0;
      C.columns = 0;
      C.matrix_type = INCORRECT_MATRIX;
    }
  }
  return C;
}

void my_remove_matrix(matrix_t *A) {
  if ((A->rows > 0) && (A->columns > 0)) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    }
  }
  if (A->matrix != NULL) free(A->matrix);
  if ((A->rows > 0) && (A->columns > 0)) {
    A->rows = 0;
    A->columns = 0;
  }
  (*A).matrix_type = INCORRECT_MATRIX;
}

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  int flag_eq = my_check_eq_size(A, B);
  int flag_incor_a = my_check_incorrect(A);
  int flag_incor_b = my_check_incorrect(B);
  if (flag_eq && flag_incor_a && flag_incor_b) {
    for (int i = 0; i < (*A).rows; i++) {
      for (int j = 0; j < (*A).columns; j++) {
        if (fabs((*A).matrix[i][j] - (*B).matrix[i][j]) >= EPS) {
          result = FAILURE;
          break;
        }
      }
      if (!result) {
        break;
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

matrix_t my_sum_matrix(matrix_t *A, matrix_t *B) {
  int flag_eq = my_check_eq_size(A, B);
  int flag_incor_a = my_check_incorrect(A);
  int flag_incor_b = my_check_incorrect(B);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (flag_eq && flag_incor_a && flag_incor_b) {
    C = my_create_matrix((*A).rows, (*A).columns);
    for (int i = 0; i < (*A).rows; i++) {
      for (int j = 0; j < (*A).columns; j++) {
        double result_sum = (*A).matrix[i][j] + (*B).matrix[i][j];
        if (result_sum >= -EPS && result_sum < 0) {
          result_sum = 0.0;
        }
        C.matrix[i][j] = result_sum;
      }
    }
    C.matrix_type = my_get_matrix_type(&C);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

matrix_t my_sub_matrix(matrix_t *A, matrix_t *B) {
  int flag_eq = my_check_eq_size(A, B);
  int flag_incor_a = my_check_incorrect(A);
  int flag_incor_b = my_check_incorrect(B);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (flag_eq && flag_incor_a && flag_incor_b) {
    C = my_create_matrix((*A).rows, (*A).columns);
    for (int i = 0; i < (*A).rows; i++) {
      for (int j = 0; j < (*A).columns; j++) {
        double result_sub = (*A).matrix[i][j] - (*B).matrix[i][j];
        if (result_sub >= -EPS && result_sub < 0) {
          result_sub = 0.0;
        }
        C.matrix[i][j] = result_sub;
      }
    }
    C.matrix_type = my_get_matrix_type(&C);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

matrix_t my_mult_number(matrix_t *A, double number) {
  int flag_incor_a = my_check_incorrect(A);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (flag_incor_a) {
    C = my_create_matrix((*A).rows, (*A).columns);
    for (int i = 0; i < (*A).rows; i++) {
      for (int j = 0; j < (*A).columns; j++) {
        double result_num = (*A).matrix[i][j] * number;
        if (result_num >= -EPS && result_num < 0) {
          result_num = 0.0;
        }
        C.matrix[i][j] = result_num;
      }
    }
    C.matrix_type = my_get_matrix_type(&C);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

matrix_t my_mult_matrix(matrix_t *A, matrix_t *B) {
  int flag_incor_a = my_check_incorrect(A);
  int flag_incor_b = my_check_incorrect(B);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (flag_incor_a && flag_incor_b && ((*A).columns == (*B).rows)) {
    C = my_create_matrix((*A).rows, (*B).columns);
    for (int i = 0; i < (*A).rows; i++) {
      for (int j = 0; j < (*B).columns; j++) {
        double result_mult = 0.0;
        for (int y = 0; y < (*B).rows; y++) {
          result_mult += (*A).matrix[i][y] * (*B).matrix[y][j];
        }
        if (result_mult >= -EPS && result_mult < 0) {
          result_mult = 0.0;
        }
        C.matrix[i][j] = result_mult;
      }
    }
    C.matrix_type = my_get_matrix_type(&C);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

matrix_t my_transpose(matrix_t *A) {
  int flag_incor_a = my_check_incorrect(A);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (flag_incor_a) {
    C = my_create_matrix((*A).columns, (*A).rows);
    for (int i = 0; i < (*A).rows; i++) {
      for (int j = 0; j < (*A).columns; j++) {
        C.matrix[j][i] = (*A).matrix[i][j];
      }
    }
    C.matrix_type = my_get_matrix_type(&C);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

double my_determinant(matrix_t *A) {
  double determinant = 0.0;
  int flag_incor_a = my_check_incorrect(A);
  if (flag_incor_a && (*A).rows == (*A).columns) {
    if ((*A).rows == 1) {
      determinant = (*A).matrix[0][0];
    } else if ((*A).rows == 2) {
      determinant = ((*A).matrix[0][0] * (*A).matrix[1][1]) -
                    ((*A).matrix[0][1] * (*A).matrix[1][0]);
    } else {
      int i = 0;
      for (int j = 0; j < (*A).columns; j++) {
        matrix_t m = my_create_matrix((*A).rows - 1, (*A).columns - 1);
        my_get_minor_matrix(&m, A, i, j);
        determinant +=
            (*A).matrix[i][j] * pow(-1, i + j + 2) * my_determinant(&m);
        my_remove_matrix(&m);
      }
    }
  } else {
    determinant = NAN;
  }
  return determinant;
}

matrix_t my_calc_complements(matrix_t *A) {
  int flag_incor_a = my_check_incorrect(A);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  if (flag_incor_a && (*A).rows == (*A).columns) {
    C = my_create_matrix((*A).rows, (*A).columns);
    if ((*A).rows == 1) {
      C.matrix[0][0] = pow(-1, 0 + 0 + 2) * my_determinant(A);
    } else {
      for (int i = 0; i < (*A).rows; i++) {
        for (int j = 0; j < (*A).columns; j++) {
          matrix_t m = my_create_matrix((*A).rows - 1, (*A).columns - 1);
          my_get_minor_matrix(&m, A, i, j);
          C.matrix[i][j] = pow(-1, i + j + 2) * my_determinant(&m);
          my_remove_matrix(&m);
        }
      }
    }
    C.matrix_type = my_get_matrix_type(&C);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

matrix_t my_inverse_matrix(matrix_t *A) {
  int flag_incor_a = my_check_incorrect(A);
  matrix_t C = {NULL, 0, 0, CORRECT_MATRIX};
  double determinant = my_determinant(A);
  if (flag_incor_a && (*A).rows == (*A).columns && determinant != 0.0) {
    matrix_t transpose = my_transpose(A);
    matrix_t complements = my_calc_complements(&transpose);
    double number = (1 / determinant);
    C = my_mult_number(&complements, number);
    C.matrix_type = my_get_matrix_type(&C);
    my_remove_matrix(&complements);
    my_remove_matrix(&transpose);
  } else {
    C.matrix_type = INCORRECT_MATRIX;
  }
  return C;
}

/*------------end main functions------------*/

/*----------helper functions----------*/

int my_check_eq_size(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if ((*A).rows == (*B).rows && (*A).columns == (*B).columns) {
    result = SUCCESS;
  }
  return result;
}

int my_check_incorrect(matrix_t *src) {
  int result = SUCCESS;
  if ((*src).matrix_type == INCORRECT_MATRIX) {
    result = FAILURE;
  }
  return result;
}

int my_get_matrix_type(matrix_t *src) {
  int type = CORRECT_MATRIX;
  if ((*src).matrix_type == INCORRECT_MATRIX) {
    type = INCORRECT_MATRIX;
  } else if (my_check_zero_matrix(src)) {
    type = ZERO_MATRIX;
  } else if (my_check_identity_matrix(src)) {
    type = IDENTITY_MATRIX;
  }
  return type;
}

int my_check_zero_matrix(matrix_t *src) {
  int result = SUCCESS;
  for (int i = 0; i < (*src).rows; i++) {
    for (int j = 0; j < (*src).columns; j++) {
      if (fabs((*src).matrix[i][j]) >= EPS) {
        result = FAILURE;
        break;
      }
    }
    if (result == FAILURE) {
      break;
    }
  }
  return result;
}

int my_check_identity_matrix(matrix_t *src) {
  int result = SUCCESS;
  if ((*src).rows == (*src).columns) {
    for (int i = 0; i < (*src).rows; i++) {
      for (int j = 0; j < (*src).columns; j++) {
        if (i == j && !my_eq_one((*src).matrix[i][j])) {
          result = FAILURE;
          break;
        } else if (i != j && fabs((*src).matrix[i][j]) >= EPS) {
          result = FAILURE;
          break;
        }
      }
      if (result == FAILURE) {
        break;
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

int my_eq_one(double value) {
  int result = SUCCESS;
  if (fabs(value - 1.0) >= EPS) {
    result = FAILURE;
  }
  return result;
}

void my_get_minor_matrix(matrix_t *C, matrix_t *A, int row, int column) {
  int x = 0;
  int y = 0;
  for (int i = 0; i < (*A).rows; i++) {
    for (int j = 0; j < (*A).columns; j++) {
      if (i != row && j != column) {
        (*C).matrix[x][y] = (*A).matrix[i][j];
        y += 1;
      }
    }
    if (y == (*C).columns) {
      x += 1;
      y = 0;
    }
  }
  (*C).matrix_type = my_get_matrix_type(C);
}
