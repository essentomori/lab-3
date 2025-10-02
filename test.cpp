#include <iostream>
#include <iomanip>

using namespace std;

// Псевдоним для типа матрицы (указатель на указатель)
using Matrix = int**;

// 1. Создание игрового поля
Matrix create_game_board(int rows, int cols, int default_value) {
    // Выделяем память для строк
    Matrix matrix = new int*[rows];

    // Для каждой строки выделяем память для столбцов и инициализируем значениями
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = default_value;
        }
    }
    return matrix;
}

// 2. Освобождение памяти
void free_game_board(Matrix matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// 3. Вывод поля
void print_board(Matrix m, int rows, int cols) {
    cout << "\nИгровое поле:" << endl;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            cout << setw(3) << m[row][col] << " ";
        }
        cout << endl;
    }
}

// 4. Размещение элемента
void place_element(Matrix m, int row, int col, int value, int max_rows, int max_cols) {
    if (row >= 0 && row < max_rows && col >= 0 && col < max_cols) {
        m[row][col] = value;
    }
}

// Тестирование
int main() {
    const int ROWS = 5;
    const int COLS = 5;

    // Создаем поле 5x5
    Matrix board = create_game_board(ROWS, COLS, 0);

    // Размещаем элементы как в примере
    place_element(board, 1, 1, 1, ROWS, COLS);
    place_element(board, 1, 2, 1, ROWS, COLS);
    place_element(board, 1, 3, 1, ROWS, COLS);
    place_element(board, 3, 2, -1, ROWS, COLS);

    // Выводим результат
    print_board(board, ROWS, COLS);

    // Освобождаем память
    free_game_board(board, ROWS);

    return 0;
}
