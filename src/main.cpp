#include <iostream>
#include "matrix.h"
int main() {
    try {
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(2, 2);

        A.data[0][0] = 1; A.data[0][1] = 2;
        A.data[1][0] = 3; A.data[1][1] = 4;
        B.data[0][0] = 5; B.data[0][1] = 6;
        B.data[1][0] = 7; B.data[1][1] = 8;
        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);

        std::cout << "\nMatrix B:" << std::endl;
        print_matrix(B);

        Matrix C = matrix_add(A, B);
        std::cout << "\nA + B:" << std::endl;
        print_matrix(C);

        Matrix D = matrix_multiply(A, B);
        std::cout << "\nA * B:" << std::endl;
        print_matrix(D);

        Matrix E = matrix_transpose(A);
        std::cout << "\nTranspose of A:" << std::endl;
        print_matrix(E);

        Matrix F = matrix_vstack(A, B);
        std::cout << "\nVertical joining of matrices A and B:" << std::endl;
        print_matrix(F);

        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
        free_matrix(D);
        free_matrix(E);
        free_matrix(F);

        std::cout << "\nAll operations completed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
