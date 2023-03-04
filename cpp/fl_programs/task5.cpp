#include <iostream>
#include <cmath>

// Задача 5.

int main() {
    setlocale(LC_ALL, "Russian");
    int size, sum = 0, count = 0;
    std::cout << "Введите количество строк и столбцов квадратной матрицы: "; std::cin >> size;
    int matrix[size][size];
    std::cout << "Матрица, заполненная случайными числами от -100 до 100:" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand()%101 * pow(-1, rand()%2);
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = i+1; j < size; ++j) {
            if (matrix[i][j] > 0) {
                sum += matrix[i][j];
                count++;
            }
        }
    }
    std::cout << "Количество положительных элементов над главной диагональю: " << count << std::endl
              << "Сумма положительных элементов над главной диагональю: " << sum << std::endl; 
    return 0;
}