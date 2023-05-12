#include <iostream>

// Задача 2.

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b, c;
    std::cout << "Введите градусную меру угла a: "; std::cin >> a;
    std::cout << "Введите градусную меру угла b: "; std::cin >> b;
    c = 180 - a - b;
    if (a <= 0 || b <= 0 || a + b >= 180) {
        std::cout << "Треугольник не существует." << std::endl;
    } else if (c == 90 || a == 90 || b == 90) {
        std::cout << "Треугольник существует и является прямоугольным" << std::endl;
    } else {
        std::cout << "Треугольник существует и HE является прямоугольным" << std::endl;
    }
    return 0;
}