#include <iostream>
#include <conio.h>

#include "vector.hpp"
#include "matrix.hpp"

int main() {
    // выделяем память
    double **arr1 = new double* [3],
           **arr2 = new double* [3],
           **arr3 = new double* [3],
             arr4[3];
    for (char i = 0 ; i < 3; ++i) {
        arr1[i] = new double [3];
        arr2[i] = new double [3];
        arr3[i] = new double [3];
    }

    // заполняем рандомными элементами
    for (char i = 0; i < 3; ++i) {
        arr4[i] = rand()%30;
        for (char j = 0; j < 3; ++j) {
            arr1[i][j] = rand()%93;
            arr2[i][j] = rand()%59;
            arr3[i][j] = rand()%23;
        }
    }

    // собираем в матрицы и вектор
    Matrix m1(3, 3, arr1),
           m2(3, 3, arr2),
           m3(3, arr3);
    Vector v1(3, arr4);

    // печатаем матрицы
    m1.print();
    std::cout << std::endl;
    m2.print();
    std::cout << std::endl;
    m3.print();
    std::cout << std::endl;
    std::cout << v1 << std::endl;

    // работаем
    Matrix m4 = m1 + m2;
    std::cout << "\nM1 + M2 =\n";
    m4.print();

    Matrix m5 = m1 - m2;
    std::cout << "\nM1 - M2 =\n";
    m5.print();

    Matrix m6 = -m2;
    std::cout << "\n-M2 =\n";
    m6.print();

    Matrix m7 = m1 * m3;
    std::cout << "\nM1 * M3 =\n";
    m7.print();

    Vector v2(m2 * v1);
    std::cout << "\nM2 * V1 = " << v2 << '\n';

    Matrix m8 = m3 * 9;
    std::cout << "\nM3 * 9 =\n";
    m8.print();

    Matrix m9 = m1;
    std::cout << "\nAssigning M1 to M9\n";
    m9.print();

    // чистим память
    for (char i = 0; i < 3; ++i) {
        delete [] arr1[i];
        delete [] arr2[i];
        delete [] arr3[i];
    }
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;

    std::cout << "\nPress any key to exit...\n";
    _getch();
    return 0;
}