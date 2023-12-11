#include <check.h>

#include "my_c_matrix.h"
void fill_matrix(matrix_t *, double, double);
void test_create_matrix(int, int);
void test_create_incorrect_matrix(int, int);
void test_eq_matrix(int rows, int columns, double start, double step);

void fill_matrix(matrix_t *m, double start, double step) {
  double data = start;
  for (int i = 0; i < (*m).rows; i++) {
    for (int j = 0; j < (*m).columns; j++) {
      (*m).matrix[i][j] = data;
      data += step;
    }
  }
  (*m).matrix_type = CORRECT_MATRIX;
  if (start == 0. && step == 0.) {
    (*m).matrix_type = ZERO_MATRIX;
  }
  if (start == 1. && step == 0. && (*m).rows == 1 && (*m).columns == 1) {
    (*m).matrix_type = IDENTITY_MATRIX;
  }
}

void test_create_matrix(int rows, int columns) {
  matrix_t m = my_create_matrix(rows, columns);
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, columns);
  ck_assert_int_eq(m.matrix_type, ZERO_MATRIX);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(m.matrix[i][j], 0);
    }
  }
  my_remove_matrix(&m);
}

void test_create_incorrect_matrix(int rows, int columns) {
  matrix_t m = my_create_matrix(rows, columns);
  ck_assert_int_eq(m.matrix_type, INCORRECT_MATRIX);
  my_remove_matrix(&m);
}

void test_eq_matrix(int rows, int columns, double start, double step) {
  matrix_t a = my_create_matrix(rows, columns);
  matrix_t b = my_create_matrix(rows, columns);
  fill_matrix(&a, start, step);
  fill_matrix(&b, start, step);
  ck_assert_int_eq(my_eq_matrix(&a, &b), SUCCESS);
  my_remove_matrix(&a);
  my_remove_matrix(&b);
}

START_TEST(test_my_create_matrix) {
  test_create_matrix(10, 10);
  test_create_matrix(100, 10);
  test_create_matrix(10, 1000);
  test_create_matrix(1000, 1);
  printf("Tests my_create_matrix is done.\n");
}
END_TEST

START_TEST(test_my_create_incorrect_matrix) {
  test_create_incorrect_matrix(-1, 1);
  test_create_incorrect_matrix(0, 0);
  test_create_incorrect_matrix(8, -100);
  test_create_incorrect_matrix(1, 0);
  printf("Tests create \"incorrect matrix\" is done.\n");
}
END_TEST

START_TEST(test_my_eq_matrix_1) {
  test_eq_matrix(1, 1, 0, 0);
  test_eq_matrix(4, 3, 9.25, 1.05);
  printf("Tests my_eq_matrix_1 is done.\n");
}
END_TEST

START_TEST(test_my_eq_matrix_2) {
  matrix_t A = my_create_matrix(4, 4);
  matrix_t B = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 8.25, 1.05);
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  printf("Tests my_eq_matrix_2 is done.\n");
}
END_TEST

START_TEST(test_my_eq_matrix_3) {
  matrix_t A = my_create_matrix(4, 4);
  matrix_t B = my_create_matrix(4, 4);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 8.25, 1.05);
  B.matrix_type = INCORRECT_MATRIX;
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  printf("Tests my_eq_matrix_3 is done.\n");
}
END_TEST

START_TEST(test_my_sum_matrix_1) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t B = my_create_matrix(3, 3);
  matrix_t R = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 8.25, 1.05);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  matrix_t C = my_sum_matrix(&A, &B);
  ck_assert_int_eq(my_eq_matrix(&C, &R), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&R);
  my_remove_matrix(&C);
  printf("Tests my_sum_matrix_1 is done.\n");
}
END_TEST

START_TEST(test_my_sum_matrix_2) {
  matrix_t A = my_create_matrix(2, 2);
  matrix_t B = my_create_matrix(4, 4);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 8.25, 1.05);
  matrix_t C = my_sum_matrix(&A, &B);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  printf("Tests my_sum_matrix_2 is done.\n");
}
END_TEST

START_TEST(test_my_sub_matrix_1) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t B = my_create_matrix(3, 3);
  matrix_t R = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 4.25, 1.05);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  matrix_t C = my_sub_matrix(&A, &B);
  ck_assert_int_eq(my_eq_matrix(&C, &R), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&R);
  my_remove_matrix(&C);
  printf("Tests my_sub_matrix_1 is done.\n");
}
END_TEST

START_TEST(test_my_mult_number_1) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t R = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  double number = 1.5674;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  matrix_t C = my_mult_number(&A, number);
  ck_assert_int_eq(my_eq_matrix(&C, &R), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&R);
  my_remove_matrix(&C);
  printf("Tests my_mult_number_1 is done.\n");
}
END_TEST

START_TEST(test_my_mult_number_2) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t R = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  double number = 0.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  R.matrix_type = ZERO_MATRIX;
  matrix_t C = my_mult_number(&A, number);
  ck_assert_int_eq(my_eq_matrix(&C, &R), SUCCESS);
  ck_assert_int_eq(C.matrix_type, R.matrix_type);
  my_remove_matrix(&A);
  my_remove_matrix(&R);
  my_remove_matrix(&C);
  printf("Tests my_mult_number_2 is done.\n");
}
END_TEST

START_TEST(test_my_mult_matrix_1) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t B = my_create_matrix(3, 3);
  matrix_t R = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 4.25, 1.05);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int y = 0; y < B.rows; y++) {
        R.matrix[i][j] += A.matrix[i][y] * B.matrix[y][j];
      }
    }
  }
  R.matrix_type = CORRECT_MATRIX;
  matrix_t C = my_mult_matrix(&A, &B);
  ck_assert_int_eq(my_eq_matrix(&C, &R), SUCCESS);
  ck_assert_uint_eq(R.matrix_type, C.matrix_type);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&R);
  my_remove_matrix(&C);
  printf("Tests my_mult_matrix_1 is done.\n");
}
END_TEST

START_TEST(test_my_mult_matrix_2) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t B = my_create_matrix(3, 3);
  matrix_t R = my_create_matrix(3, 3);
  fill_matrix(&A, 8.25, 1.05);
  fill_matrix(&B, 0, 0);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int y = 0; y < B.rows; y++) {
        R.matrix[i][j] += A.matrix[i][y] * B.matrix[y][j];
      }
    }
  }
  matrix_t C = my_mult_matrix(&A, &B);
  ck_assert_int_eq(my_eq_matrix(&C, &R), SUCCESS);
  ck_assert_uint_eq(R.matrix_type, C.matrix_type);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&R);
  my_remove_matrix(&C);
  printf("Tests my_mult_matrix_2 is done.\n");
}
END_TEST

START_TEST(test_my_transpose_1) {
  matrix_t A = my_create_matrix(2, 4);
  matrix_t B = my_create_matrix(4, 2);
  const double arr1[] = {3, 4, 6, 0, 1, 0.05, 2, 100};
  const double arr2[] = {3, 1, 4, 0.05, 6, 2, 0, 100};
  int y = 0;
  A.matrix_type = 0;
  B.matrix_type = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = arr1[y];
      y++;
    }
  }
  y = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      B.matrix[i][j] = arr2[y];
      y++;
    }
  }
  matrix_t C = my_transpose(&A);
  ck_assert_int_eq(my_eq_matrix(&B, &C), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  printf("Tests my_transpose_1 is done.\n");
}
END_TEST

START_TEST(test_my_determinant_1) {
  matrix_t A = my_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  double result = 0.0;
  double determinant = my_determinant(&A);
  ck_assert_ldouble_eq(result, determinant);
  my_remove_matrix(&A);
  printf("Tests my_determinant_1 is done.\n");
}
END_TEST

START_TEST(test_my_determinant_2) {
  matrix_t A = my_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 8;
  double result = 3.0;
  double determinant = my_determinant(&A);
  ck_assert_ldouble_eq(result, determinant);
  my_remove_matrix(&A);
  printf("Tests my_determinant_2 is done.\n");
}
END_TEST

START_TEST(test_my_determinant_3) {
  matrix_t A = my_create_matrix(2, 3);
  fill_matrix(&A, 3, 1);
  ck_assert_double_nan(my_determinant(&A));
  my_remove_matrix(&A);
  printf("Tests my_determinant_3 is done.\n");
}
END_TEST

START_TEST(test_my_calc_complements_1) {
  matrix_t A = my_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix_type = CORRECT_MATRIX;
  matrix_t B = my_create_matrix(3, 3);
  B.matrix[0][0] = 0;
  B.matrix[0][1] = 10;
  B.matrix[0][2] = -20;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = -14;
  B.matrix[1][2] = 8;
  B.matrix[2][0] = -8;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = 4;
  B.matrix_type = CORRECT_MATRIX;
  matrix_t C = my_calc_complements(&A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(B.matrix[i][j], C.matrix[i][j]);
    }
  }
  ck_assert_int_eq(B.matrix_type, C.matrix_type);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  printf("Tests my_calc_complements_1 is done.\n");
}

START_TEST(test_my_calc_complements_2) {
  matrix_t A = my_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  A.matrix_type = CORRECT_MATRIX;
  matrix_t B = my_create_matrix(3, 3);
  B.matrix[0][0] = -48;
  B.matrix[0][1] = 6;
  B.matrix[0][2] = 32;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = -12;
  B.matrix[1][2] = 6;
  B.matrix[2][0] = 12;
  B.matrix[2][1] = 6;
  B.matrix[2][2] = -8;
  B.matrix_type = CORRECT_MATRIX;
  matrix_t C = my_calc_complements(&A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(B.matrix[i][j], C.matrix[i][j]);
    }
  }
  ck_assert_int_eq(B.matrix_type, C.matrix_type);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  printf("Tests my_calc_complements_2 is done.\n");
}

START_TEST(test_my_inverse_matrix_1) {
  matrix_t A = my_create_matrix(3, 3);
  matrix_t B = my_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  A.matrix_type = CORRECT_MATRIX;
  B.matrix[0][0] = -0.8;
  B.matrix[0][1] = 0.1;
  B.matrix[0][2] = 0.2;
  B.matrix[1][0] = 0.1;
  B.matrix[1][1] = -0.2;
  B.matrix[1][2] = 0.1;
  B.matrix[2][0] = 0.53333333;
  B.matrix[2][1] = 0.1;
  B.matrix[2][2] = -0.133333333;
  B.matrix_type = CORRECT_MATRIX;
  matrix_t C = my_inverse_matrix(&A);
  ck_assert_int_eq(my_eq_matrix(&B, &C), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&C);
  printf("Tests my_inverse_matrix_1 is done.\n");
}
END_TEST

START_TEST(test_my_inverse_matrix_2) {
  matrix_t A = my_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  A.matrix_type = CORRECT_MATRIX;
  matrix_t C = my_inverse_matrix(&A);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  my_remove_matrix(&A);
  my_remove_matrix(&C);
  printf("Tests my_inverse_matrix_2 is done.\n");
}
END_TEST

Suite *my_suite(void) {
  Suite *suite = suite_create("Matrix");
  TCase *tcase_core = tcase_create("Equelity");

  tcase_add_test(tcase_core, test_my_create_matrix);
  tcase_add_test(tcase_core, test_my_create_incorrect_matrix);
  tcase_add_test(tcase_core, test_my_eq_matrix_1);
  tcase_add_test(tcase_core, test_my_eq_matrix_2);
  tcase_add_test(tcase_core, test_my_eq_matrix_3);
  tcase_add_test(tcase_core, test_my_sum_matrix_1);
  tcase_add_test(tcase_core, test_my_sum_matrix_2);
  tcase_add_test(tcase_core, test_my_sub_matrix_1);
  tcase_add_test(tcase_core, test_my_mult_number_1);
  tcase_add_test(tcase_core, test_my_mult_number_2);
  tcase_add_test(tcase_core, test_my_mult_matrix_1);
  tcase_add_test(tcase_core, test_my_mult_matrix_2);
  tcase_add_test(tcase_core, test_my_transpose_1);
  tcase_add_test(tcase_core, test_my_determinant_1);
  tcase_add_test(tcase_core, test_my_determinant_2);
  tcase_add_test(tcase_core, test_my_determinant_3);
  tcase_add_test(tcase_core, test_my_calc_complements_1);
  tcase_add_test(tcase_core, test_my_calc_complements_2);
  tcase_add_test(tcase_core, test_my_inverse_matrix_1);
  tcase_add_test(tcase_core, test_my_inverse_matrix_2);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = my_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
