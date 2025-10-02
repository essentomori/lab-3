#include <iostream>
#include "matrix.h"
int main() {
    try {
        Matrix A = create_game_board(5, 5, 0);

        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);
/*
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

*/
        free_matrix(A);
        /*
        free_matrix(B);
        free_matrix(C);
        free_matrix(D);
        free_matrix(E);

        std::cout << "\nAll operations completed successfully!" << std::endl;
*/
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
