#include <gtest/gtest.h>
#include "matrix.h"
TEST(MatrixTest, CreateAndFree) {
    Matrix m = create_matrix(2, 2);
    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 2);
    EXPECT_NE(m.data, nullptr);
    free_matrix(m);
}
TEST(MatrixTest, InvalidSize) {
    EXPECT_THROW(create_matrix(-1, 2), std::invalid_argument);
}
TEST(MatrixTest, MatrixAddition) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    Matrix C = matrix_add(A, B);
    EXPECT_EQ(C.data[0][0], 6);
    EXPECT_EQ(C.data[0][1], 8);
    EXPECT_EQ(C.data[1][0], 10);
    EXPECT_EQ(C.data[1][1], 12);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}
TEST(MatrixTest, MatrixMultiplication) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    Matrix C = matrix_multiply(A, B);
    EXPECT_EQ(C.data[0][0], 19);
    EXPECT_EQ(C.data[0][1], 22);
    EXPECT_EQ(C.data[1][0], 43);
    EXPECT_EQ(C.data[1][1], 50);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}
TEST(MatrixVStackTest, BasicVerticalStack) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(3, 3);

    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    B.data[0][0] = 7; B.data[0][1] = 8; B.data[0][2] = 9;
    B.data[1][0] = 10; B.data[1][1] = 11; B.data[1][2] = 12;
    B.data[2][0] = 13; B.data[2][1] = 14; B.data[2][2] = 15;

    Matrix result = matrix_vstack(A, B);

    EXPECT_EQ(result.rows, 5);
    EXPECT_EQ(result.cols, 3);
    EXPECT_NE(result.data, nullptr);

    EXPECT_EQ(result.data[0][0], 1); EXPECT_EQ(result.data[0][1], 2); EXPECT_EQ(result.data[0][2], 3);
    EXPECT_EQ(result.data[1][0], 4); EXPECT_EQ(result.data[1][1], 5); EXPECT_EQ(result.data[1][2], 6);
    EXPECT_EQ(result.data[2][0], 7); EXPECT_EQ(result.data[2][1], 8); EXPECT_EQ(result.data[2][2], 9);
    EXPECT_EQ(result.data[3][0], 10); EXPECT_EQ(result.data[3][1], 11); EXPECT_EQ(result.data[3][2], 12);
    EXPECT_EQ(result.data[4][0], 13); EXPECT_EQ(result.data[4][1], 14); EXPECT_EQ(result.data[4][2], 15);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

TEST(MatrixVStackTest, IncompatibleColumns) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 4);

    EXPECT_THROW(matrix_vstack(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixVStackTest, SingleRowMatrices) {
    Matrix A = create_matrix(1, 2);
    Matrix B = create_matrix(1, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    B.data[0][0] = 3; B.data[0][1] = 4;

    Matrix result = matrix_vstack(A, B);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 2);
    EXPECT_NE(result.data, nullptr);

    EXPECT_EQ(result.data[0][0], 1); EXPECT_EQ(result.data[0][1], 2);
    EXPECT_EQ(result.data[1][0], 3); EXPECT_EQ(result.data[1][1], 4);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

TEST(MatrixVStackTest, LargeMatrices) {
    const int rows_A = 100;
    const int rows_B = 200;
    const int cols = 50;

    Matrix A = create_matrix(rows_A, cols);
    Matrix B = create_matrix(rows_B, cols);

    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols; j++) {
            A.data[i][j] = i + j;
        }
    }

    for (int i = 0; i < rows_B; i++) {
        for (int j = 0; j < cols; j++) {
            B.data[i][j] = (i + j) * 2;
        }
    }

    Matrix result = matrix_vstack(A, B);

    EXPECT_EQ(result.rows, rows_A + rows_B);
    EXPECT_EQ(result.cols, cols);
    EXPECT_NE(result.data, nullptr);

    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols; j++) {
            EXPECT_EQ(result.data[i][j], i + j);
        }
    }

    for (int i = 0; i < rows_B; i++) {
        for (int j = 0; j < cols; j++) {
            EXPECT_EQ(result.data[rows_A + i][j], (i + j) * 2);
        }
    }

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

TEST(MatrixVStackTest, NegativeValues) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = -1; A.data[0][1] = -2;
    A.data[1][0] = -3; A.data[1][1] = -4;

    B.data[0][0] = -5; B.data[0][1] = -6;
    B.data[1][0] = -7; B.data[1][1] = -8;

    Matrix result = matrix_vstack(A, B);

    EXPECT_EQ(result.rows, 4);
    EXPECT_EQ(result.cols, 2);
    EXPECT_NE(result.data, nullptr);

    EXPECT_EQ(result.data[0][0], -1); EXPECT_EQ(result.data[0][1], -2);
    EXPECT_EQ(result.data[1][0], -3); EXPECT_EQ(result.data[1][1], -4);
    EXPECT_EQ(result.data[2][0], -5); EXPECT_EQ(result.data[2][1], -6);
    EXPECT_EQ(result.data[3][0], -7); EXPECT_EQ(result.data[3][1], -8);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

TEST(MatrixVStackTest, SameMatrixStack) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    Matrix result = matrix_vstack(A, A);

    EXPECT_EQ(result.rows, 4);
    EXPECT_EQ(result.cols, 2);
    EXPECT_NE(result.data, nullptr);

    EXPECT_EQ(result.data[0][0], 1); EXPECT_EQ(result.data[0][1], 2);
    EXPECT_EQ(result.data[1][0], 3); EXPECT_EQ(result.data[1][1], 4);
    EXPECT_EQ(result.data[2][0], 1); EXPECT_EQ(result.data[2][1], 2);
    EXPECT_EQ(result.data[3][0], 3); EXPECT_EQ(result.data[3][1], 4);

    free_matrix(A);
    free_matrix(result);
}
