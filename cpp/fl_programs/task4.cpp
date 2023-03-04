#include <iostream>

// Задача 4.

int main() {
    setlocale(LC_ALL, "Russian");
    int N;
    double result;
    std::cout << "Введите число N: "; std::cin >> N;
    if (N <= 0) {
        std::cout << "Исходные данные не верны!" << std::endl;
        return 0;
    } 
    for (int n = 1; n <= N; ++n) {
        result += (2.0*n) / (2*n + 1);
    }
    std::cout << "Значение выражения: " << result << std::endl;
    return 0;
}