#include <iostream>

// Задача 3.

int main() {
    setlocale(LC_ALL, "Russian");
    int N, mod;
    std::cout << "Введите число N: "; std::cin >> N;
    do {
        mod = N % 10;
        N = N / 10;
        if (mod % 2) {
            std::cout << "Цифра входит в запись числа." << std::endl;
            return 0;
        } else {
            continue;
        }
    } while (N);
    std::cout << "Цифра НЕ входит в запись числа." << std::endl;
    return 0;
}